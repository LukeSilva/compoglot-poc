#include "en/en.h"
#include "de/de.h"
#include "eo/eo.h"
#include "Language.h"
#include "parser/Parser.h"
#include "cmdparse.h"
#include "fileparse.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <memory>

std::shared_ptr<Language> getLanguageFromStringID(std::string ID)
{
	if (ID.compare("en")==0)
		return std::shared_ptr<Language>(new en());
	else if (ID.compare("de")==0)
		return std::shared_ptr<Language>(new de());
	else if (ID.compare("eo")==0)
		return std::shared_ptr<Language>(new eo());
	else
	{
		throw std::runtime_error(std::string("Unknown language ID ") + ID);
	}
	return std::shared_ptr<Language>(new Language());
}


int main(int argc, char *argv[])
{
	if (argc<3){
		std::cerr << "Usage: " << argv[0] << " <mode> <language>" << std::endl;
		return -1;
	}
	if (std::string(argv[1]).compare("cmd")==0)
	{
		return cmdParse(argc,argv);
	} 
	else if (std::string(argv[1]).compare("file")==0)
	{
		return fileParse(argc,argv);
	}
	else
	{
		std::cerr << "Unknown mode " << argv[1] << std::endl;
		std::cerr << "Usage: " << argv[0] << " <mode> <language>" << std::endl;
		return -1;
	}
	return 0;
}
