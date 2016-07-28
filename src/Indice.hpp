#ifndef INDICE_HPP
#define INDICE_HPP

class Indice {
	public:
		Indice() {}

		Indice(int indice, std::string comando, std::string descricao)
				: _indice(indice), _comando(comando), _descricao(descricao) {}

		~Indice() {}

		int get_indice() {
			return _indice;
		}

		std::string get_comando() {
			return _comando;
		}

		std::string get_descricao() {
			return _descricao;
		}

	private:
		int _indice;
		std::string _comando;
		std::string _descricao;
};
#endif