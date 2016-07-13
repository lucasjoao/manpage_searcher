#ifndef INDICE_HPP
#define INDICE_HPP

#include <string>

class Indice {
	public:
		Indice() {}

		Indice(int indice, std::string comando)
				: _indice(indice), _comando(comando) {}

		~Indice() {}

		int get_indice() {
			return _indice;
		}

		std::string get_comando() {
			return _comando;
		}

	private:
		int _indice;
		std::string _comando;
};
#endif