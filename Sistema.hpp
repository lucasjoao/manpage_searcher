#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Registro.hpp"

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

		std::string le_manpage_dat() {
			std::ifstream ifs("manpages.dat", std::ifstream::binary);

			ifs.seekg(_regs[10]->get_dat_start());
			Registro tmp;
			long prov = _regs[10]->get_dat_end() - _regs[10]->get_dat_start();
			ifs.read((char *) &tmp, prov);
			ifs.close();
			return tmp.get_descricao();
		}

		bool tmp() {
			std::string a("daiara");
			std::string b("lucas");

			return a < b ? true : false;
		}

	private:
		int _argc;
		std::vector<std::string> _argv;
		std::vector<Registro*> _regs;
		bool _dir;
};
#endif