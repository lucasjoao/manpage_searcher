#ifndef SISTEMA_HPP
#define SISTEMA_HPP

class Sistema {
	public:
		Sistema() {}

		Sistema(int argc, char *argv[]) : _argc(argc) {
			for (int i = 1; i < _argc; i++)
				_argv[i] = argv[i];
		}

		~Sistema() {}
	private:
		int _argc;
		char *_argv[];
};
#endif