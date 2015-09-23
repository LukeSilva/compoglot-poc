#include "en/en.h"
#include "Language.h"
#include "parser/parser.h"
#include "cmdparse.h"
#include "fileparse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

Language* getLanguageFromStringID(std::string ID)
{
	Language* ret;
	if (ID.compare("en")==0)
		ret = new en;
	else
	{
		std::cerr << "Unknown Language: \"" << ID << "\"" << std::endl;
		exit(-1);
	}
	return ret;
}

Language* getLanguageFromStringId(char* Id){
	return getLanguageFromStringID(std::string(Id));
}


int main(int argc, char *argv[])
{
	if (argc<3){
		printf("Usage: %s <mode> <language>\n",argv[0]);
		std::cerr << "Usage: " << argv[0] << "<mode> <language>" << std::endl;
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
		std::cerr << "Usage: " << argv[0] << "<mode> <language>" << std::endl;
		return -1;
	}
	return 0;
}
