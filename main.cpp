#include <iostream>

int main(int argc, char *argv[]) {
	if (argc == 1) {
		std::cout << "Execução incorreta do programa! Por favor, informe " <<
					 "quais serão os arquivos manpages utilizados.\n";
		return 1;
	}

	for (int i = 1; i < argc; i++)
		std::cout << argv[i] << std::endl;

	return 0;
}
