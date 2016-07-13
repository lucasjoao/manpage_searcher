#include <iostream>
#include "Sistema.hpp"

int main(int argc, char **argv) {
	system("clear");
	if (argc == 1) {
		std::cout << "Execução incorreta do programa! Por favor, informe "
				  << "quais serão os arquivos manpages utilizados.\n";
		return 1;
	} else {
		std::cout << "Gerando arquivos necessários para busca! Aguarde...\n\n";
	}

	Sistema sis = Sistema(argc, argv);
	sis.cria_registros();
	sis.cria_manpage_dat();
	sis.cria_indices();
	sis.cria_arv_tmp();
	sis.cria_ind_primario_dat();

	bool controle = true;
	while (controle) {
		std::cout << "Digite o número da opção que você deseja realizar: \n"
				  << "1 - busca por chave primária\n"
				  << "2 - busca por chave secundária\n"
				  << "3 - busca conjuntiva por chave secundária\n"
				  << "0 - sair\n"
				  << "> ";

		int opcao;
		std::cin >> opcao;

		if (std::cin.fail())
			opcao = 42;

		std::string comando;
		std::string resultado;
		switch(opcao) {
			case 1:
				system("clear");
				std::cout << "Insira o nome do comando para buscar a manpage:"
						  << "\n> ";
				std::cin >> comando;

				std::cout << std::endl << sis.busca_prim(comando) << "\n\n";
				break;
			case 2:
				std::cout << "Não foi implementado.\n" << ":(\n";
				break;
			case 3:
				system("clear");
				std::cout << "Não foi implementado.\n" << ":(\n";
				break;
			case 42:
				std::cout << "\nSem zoeiras, por favor!\n";
			case 0:
				controle = false;
				break;
			default:
				system("clear");
				std::cout << "\nAparentemente é uma opção inválida!\n\n";
		}
	}

	return 0;
}
