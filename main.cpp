#include <iostream>
#include "Sistema.hpp"

int main(int argc, char **argv) {
	if (argc == 1) {
		std::cout << "Execução incorreta do programa! Por favor, informe " <<
					 "quais serão os arquivos manpages utilizados.\n";
		return 1;
	}

	Sistema sis = Sistema(argc, argv);

	sis.cria_registros();
	sis.cria_manpage_dat();

	sis.cria_indices();
	sis.cria_arv_tmp();
	sis.teste_parcial_avl();
	// std::cout << sis.le_manpage_dat() << std::endl;

	// if (sis.tmp())
	// 	std::cout << "menor, funciona\n";
	// else
	// 	std::cout << "estranho\n";

	return 0;
}