#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <string>

class Registro {
	public:
		Registro() {}

		Registro(int indice, std::string comando, std::string descricao)
				: _indice(indice), _comando(comando), _descricao(descricao) {}

		~Registro() {}

	private:
		int _dat_start;
		int _dat_end;
		int _indice;
		std::string _comando;
		std::string _descricao;
};
#endif