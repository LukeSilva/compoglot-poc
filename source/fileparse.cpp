#include "Language.h"
#include "parser/Parser.h"
#include "parser/ParseException.h"
#include "settings.h"
#include <string>
#include <fstream>
#include <iostream>
int fileParse(int argc,char* argv[]){
	if (argc!=5)
	{
		std::cout << "Usage: " << argv[0] << " " << argv[1] <<" <language> <input-file> <output-file>" << std::endl;
		return -1;
	}

	std::ifstream rFile(argv[3]);
	std::ofstream wFile(argv[4]);
	if (!rFile.is_open())
	{
		std::cout << "Could not open input file" << std::endl;
		return -1;
	}
	if (!wFile.is_open())
	{
		std::cout << "Could not open output file" << std::endl;
		return -1;
	}

	char c = 0;
	while (rFile.get(c))
	{
		if (c!= '$')
			wFile.put(c);
		else
		{
			if (rFile.get(c) && c == '<')
				if (rFile.get(c) && c == 'L')
					if (rFile.get(c) && c == 'A')
						if (rFile.get(c) && c == 'N')
							if (rFile.get(c) && c == 'G')
							{
								std::string input;
								while (rFile.get(c) && c != '>')
								{
									input += c;
								}
								Parser parser;
								std::string output;

								try{
									output = parser.parse(argv[2],input);
								}
								catch(ParseException& e){
									std::cerr << e;
									return -1;
								}
								wFile << output;
							}else wFile << "$<LAN" << c;
						else wFile << "$<LA" << c;
					else wFile << "$<L" << c;
				else wFile << "$<" << c;
			else wFile << "$" << c;
		}
	}
 return 0;
}
