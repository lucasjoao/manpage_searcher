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

	return 0;
}