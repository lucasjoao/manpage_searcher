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
			// std::ofstream ofs ("manpage.dat", std::ofstream::out);

			// std::ifstream ifs (_argv[1], std::ifstream::in);
			// ifs.seekg (0, ifs.end);
		 //    int length = ifs.tellg();
		 //    ifs.seekg (0, ifs.beg);
			// char *buffer = new char[length];
			// ifs.read(buffer, length);
			// for (int i = 0; i < length; i++)
			// 	std::cout << buffer[i];

			// ofs << _argv[1] << "\n" << length;

			// ofs.close();
		}

	private:
		int _argc;
		std::vector<std::string> _argv;
		std::vector<Registro*> _regs;
		bool _dir;
};
#endif