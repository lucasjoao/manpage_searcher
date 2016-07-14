#ifndef REGISTRO_HPP
#define REGISTRO_HPP

class Registro {
	public:
		Registro() {}

		Registro(int indice, std::string comando, std::string descricao)
				: _indice(indice), _comando(comando), _descricao(descricao) {}

		~Registro() {}

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