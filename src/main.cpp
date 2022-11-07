#include "../main.hpp"

void	check_argv(int argc)
{
	if (argc != 2)
	{
		std::cout << "Create a class.hpp <class_name> et class.cpp" << std::endl << std::endl;
		std::cout << "./creat_class <class_name>" << std::endl;
		exit(1);
	}
}

void	check_file(std::string &hpp_name, std::string &cpp_name)
{
	if (std::filesystem::exists(hpp_name))
	{
		std::cout << "Please remove: " << hpp_name << " first" << std::endl;
		exit(2);
	}
	if (std::filesystem::exists(cpp_name))
	{
		std::cout << "Please remove: " << cpp_name << " first" << std::endl;
		exit(2);
	}
}

void	inside_hpp(std::ofstream &hpp_file, std::string hpp_name, char *class_name)
{
	std::string	classe = class_name;
	std::string	txt;
	txt =  "#ifndef ";
	std::transform(hpp_name.begin(), hpp_name.end(),hpp_name.begin(), ::toupper);
	hpp_name.replace(hpp_name.find("."), 1, "_");
	//std::cout << hpp_name << std::endl;	
	txt += hpp_name;
	txt += "\n#define ";
	txt += hpp_name;
	txt += "\n\n#include <iostream>\n#include <string>\n\nclass ";
	txt += classe;
	txt = txt + "\n{\n\n\t/*******************/\n\t/*      CANON      */\n\t/*******************/\n\n\tpublic:\n\t" + classe + "();\n\t" + classe + "(" + classe + " const &src);\n\t~";
	txt = txt + classe + "();\n\t" + classe + "\t&operator=(" + classe + " const &src);\n\n\tprivate:\n\n};\n\n#endif";
	hpp_file << txt;
}

void	inside_cpp(std::ofstream &cpp_file, char *class_name)
{
	std::string	classe = class_name;
	std::string	txt;
	txt = "#include \"../header/";
	txt = txt + classe +  ".hpp\"\n\n" + classe + "::" + classe + "()\n{\n\tstd::cout << \"Default constructor call for " + classe + "\" << std::endl;\n}\n\n" + classe + "::" + classe + "(" + classe;
	txt = txt + " const &src)\n{\n\t*this = src;\n\tstd::cout << \"Copy constructor call for " + classe + "\" << std::endl;\n}\n\n";	
	txt = txt + classe + "::~" + classe + "()\n{\n\tstd::cout << \"Default destuctor call for " + classe + "\" << std::endl;\n}\n\n" + classe + "\t&" + classe + "::operator=(" + classe + " const &src)\n{\n\tstd::cout << \"Default assignement call for " + classe + "\" << std::endl;\treturn *this;\n\n}";
	cpp_file << txt;
}

int main (int argc, char **argv)
{
	check_argv(argc);

	std::ofstream	hpp_file;	
	std::ofstream	cpp_file;
	std::string		hpp_name = "header/";
	std::string		hpp;
	std::string		cpp;
	std::string		cpp_name = "src/";

	hpp = argv[1];
	cpp = argv[1];
	hpp += ".hpp";
	cpp += ".cpp";
	cpp_name += cpp;
	hpp_name += hpp;
	check_file(hpp_name, cpp_name);
	std::filesystem::create_directory("header/");
	std::filesystem::create_directory("src/");

	hpp_file.open(hpp_name);
	cpp_file.open(cpp_name);
	if (hpp_file.fail())
	{
		std::perror("error");
		return 2;
	}
	if (cpp_file.fail())
	{
		std::perror("error");
		return 2;
	}

	inside_hpp(hpp_file, hpp, argv[1]);
	inside_cpp(cpp_file, argv[1]);

	hpp_file.close();
	cpp_file.close();
}

