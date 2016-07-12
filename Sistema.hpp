#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <iostream>
#include <fstream>
#include <string>
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
			comando = comando.substr(0, dot_pos);
			return comando;
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
			long start, end;
			std::ofstream ofs("manpages.dat", std::ofstream::binary);

			for (unsigned int i = 0; i < _regs.size(); i++) {
				start = ofs.tellp();
				ofs.write((char *) _regs[i], sizeof(Registro));
				end = ofs.tellp();

				_regs[i]->set_dat_start(start);
				_regs[i]->set_dat_end(end);
			}

			ofs.close();
		}

		void cria_indices() {
			for (unsigned int i = 0; i < _regs.size(); i++)
				_inds.push_back(new Indice(_regs[i]->get_indice(),
										   _regs[i]->get_comando()));
		}

		void cria_arv_tmp() {
			_avl = new NoAVL<Indice*>(_inds[0]);
			for (unsigned int i = 1; i < _inds.size(); i++)
				_avl = _avl->inserir(_inds[i], _avl);
		}

		void cria_ind_primario_dat() {
			long start, end;

			NoAVL<Indice*> *nulo = new NoAVL<Indice*>(new Indice(-1, "nulo"));
			_avl->nivelOrdem(_avl, nulo);
			std::vector<NoAVL<Indice*>*> tmp = _avl->getElementos();

			std::ofstream ofs("ind_primario.dat", std::ofstream::binary);
			Indice *a;
			for (unsigned int i = 0; i < tmp.size(); i++) {
				a = *(tmp[i]->getDado());
				start = ofs.tellp();
				ofs.write((char *) a, sizeof(Indice));
				end = ofs.tellp();

				if (i < _inds.size())
					_inds[i]->set_tamanho(end - start);
			}

			ofs.close();
		}

		std::string busca_prim(std::string comando) {
			int indice = busca_ind_primario_dat(comando);
			std::cout << indice << std::endl;
			return comando;
		}

		int busca_ind_primario_dat(std::string comando) {
			std::ifstream ifs("ind_primario.dat", std::ifstream::binary);

			// ifs.seekg(_regs[10]->get_dat_start());
			Indice tmp;
			// long prov = _regs[10]->get_dat_end() - _regs[10]->get_dat_start();
			ifs.read((char *) &tmp, _inds[0]->get_tamanho());
			ifs.close();

			std::cout << tmp.get_comando();
			// int i = 0;
			return 1;
			// while (tmp.get_comando() != "nulo"
			// 	   && tmp.get_comando() != comando) {

			// 	if (tmp.get_comando() < comando) {
			// 		ifs.seekg((2*i+1) * _inds[0]->get_tamanho());
			// 		ifs.read((char *) &tmp, _inds[0]->get_tamanho());
			// 	} else {
			// 		ifs.seekg((2*i+2) * _inds[0]->get_tamanho());
			// 		ifs.read((char *) &tmp, _inds[0]->get_tamanho());
			// 	}

			// 	std::cout<<i<<std::endl;i++;
			// }

			// ifs.close();

			// if (tmp.get_comando() == "nulo")
			// 	return -1;
			// else
			// 	return tmp.get_indice();

		}

		void teste_parcial_avl() {
			NoAVL<Indice*> *oh = new NoAVL<Indice*>(new Indice(-1, "nulo"));
			_avl->nivelOrdem(_avl, oh);
			std::vector<NoAVL<Indice*>*> tmp = _avl->getElementos();
			Indice *a;
			for (unsigned int i = 0; i < tmp.size(); i++) {
				a = *(tmp[i]->getDado());
				// std::cout << tmp[i]->getDado()->get_comando() << std::endl;
				std::cout << a->get_comando() << std::endl;

			}
		}

		std::string le_manpage_dat() {
			std::ifstream ifs("manpages.dat", std::ifstream::binary);

			ifs.seekg(_regs[10]->get_dat_start());
			Registro tmp;
			long prov = _regs[10]->get_dat_end() - _regs[10]->get_dat_start();
			ifs.read((char *) &tmp, prov);
			ifs.close();
			return tmp.get_descricao();
		}

		std::string fuck() {
			std::ifstream ifs("ind_primario.dat", std::ifstream::binary);

			// ifs.seekg(_regs[10]->get_dat_start());
			Indice tmp;
			// long prov = _regs[10]->get_dat_end() - _regs[10]->get_dat_start();
			ifs.read((char *) &tmp, _inds[0]->get_tamanho());
			ifs.close();
			return tmp.get_comando();
		}

		std::string& SSS (const char* s) {
		    return *(new std::string(s));
		}

	private:
		int _argc;
		std::vector<std::string> _argv;
		std::vector<Registro*> _regs;
		bool _dir;
		std::vector<Indice*> _inds;
		NoAVL<Indice*> *_avl;
};
#endif