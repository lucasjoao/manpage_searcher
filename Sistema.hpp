#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "Registro.hpp"
#include "NoAVL.hpp"
#include "Indice.hpp"

class Sistema {
	public:
		Sistema() {}

		Sistema(int argc, char **argv) : _argc(argc) {
			for (int i = 0; i < _argc; i++) {
				_argv.push_back(argv[i]);
			}
		}

		~Sistema() {}

		void verifica_argv() {
			_dir = _argv[_argc-1].find_first_of("/", 0) == std::string::npos ?
				false : true;
		}

		std::string trata_argv(std::string comando) {
			verifica_argv();
			if (_dir) {
				std::size_t fsl_pos = comando.find_last_of("/");
				std::size_t end_pos = comando.find_last_of(comando.back());
				comando = comando.substr(fsl_pos+1, end_pos);
			}

			std::size_t dot_pos = comando.find_last_of(".");
			return comando.substr(0, dot_pos);
		}

		void cria_registros() {
			for (int i = 1; i < _argc; i++) {
				std::ifstream ifs (_argv[i], std::ifstream::in);

				ifs.seekg (0, ifs.end);
			    int length = ifs.tellg();
			    ifs.seekg (0, ifs.beg);

				char *buffer = new char[length];
				ifs.read(buffer, length);
				std::string descricao(buffer);

				_regs.push_back(new Registro(i, trata_argv(_argv[i]),
											descricao));

				ifs.close();
				delete buffer;
			}
		}

		void cria_manpage_dat() {
			std::ofstream ofs("manpages.dat");

			for (unsigned int i = 0; i < _regs.size(); i++) {
				ofs << _regs[i]->get_indice();
				ofs << " ";
				ofs << _regs[i]->get_comando();
				ofs << " ";
				ofs << _regs[i]->get_descricao();
				ofs << "\3";
			}

			ofs.close();
		}

		void cria_indices() {
			for (unsigned int i = 0; i < _regs.size(); i++)
				_inds.push_back(new Indice(_regs[i]->get_indice(),
										   _regs[i]->get_comando(),
										   _regs[i]->get_descricao()));
		}

		void cria_arv_tmp() {
			_avl = new NoAVL<std::string>(_inds[0]->get_comando(),
										  _inds[0]->get_descricao());
			for (unsigned int i = 1; i < _inds.size(); i++)
				_avl = _avl->inserir(_inds[i]->get_comando(), _avl,
									 _inds[i]->get_descricao());
		}

		void cria_ind_primario_dat() {
			_avl->nivelOrdem(_avl);
			std::vector<NoAVL<std::string>*> vector_tmp = _avl->getElementos();

			std::ofstream ofs("ind_primario.dat");
			for (unsigned int i = 0; i < vector_tmp.size(); i++) {
				ofs << *vector_tmp[i]->getDado();
				ofs << " ";
				ofs << vector_tmp[i]->getDescricao();
				ofs << "\3";
			}

			ofs.close();
		}

		std::string le_ind_primario_dat(std::string comando) {
			std::ifstream ifs("ind_primario.dat");
			std::string comando_tmp;
			std::string descricao_tmp;
			bool encontrou = false;

			while(!ifs.eof()) {
				ifs >> comando_tmp;

				if(comando.compare(comando_tmp) == 0) {
					encontrou = true;
					getline(ifs, descricao_tmp, '\3');
					break;
				} else {
					ifs.ignore(std::numeric_limits<std::streamsize>::max(),
							   '\3');
				}
			}

			ifs.close();
			if (!encontrou)
				return "Comando não existe na base!";
			return descricao_tmp;
		}

	private:
		int _argc;
		std::vector<std::string> _argv;
		std::vector<Registro*> _regs;
		bool _dir;
		std::vector<Indice*> _inds;
		NoAVL<std::string> *_avl;
};
#endif