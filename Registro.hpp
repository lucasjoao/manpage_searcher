#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <string>

class Registro {
	public:
		Registro() {}

		Registro(int indice, std::string comando, std::string descricao)
				: _indice(indice), _comando(comando), _descricao(descricao) {}

		~Registro() {}

		void set_dat_start(long start) {
			_dat_start = start;
		}

		void set_dat_end(long end) {
			_dat_end = end;
		}

	private:
		int _dat_start;
		int _dat_end;
		int _indice;
		std::string _comando;
		std::string _descricao;
};
#endif