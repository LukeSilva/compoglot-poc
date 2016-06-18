#include "Language.h"
#include "parser/Parser.h"
#include "parser/ParseException.h"
#include "settings.h"
#include <iostream>
int cmdParse(int argc,char* argv[]){
	if (argc!=4)
	{
		std::cout << "Usage:" << argv[0] << " " << argv[1] << " <language> <string-to-parse>" << std::endl;;
		return -1;
	}

	Parser parser;
	try
	{
		std::cout << parser.parse(std::string(argv[2]),std::string(argv[3])) << std::endl;
	}
	catch(ParseException& e)
	{
		std::cerr << e;
		return -1;
	}

	return 0;
}
