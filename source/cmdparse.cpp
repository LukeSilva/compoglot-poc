#include "Language.h"
#include "parser/Parser.h"
#include "settings.h"
#include <iostream>
int cmdParse(int argc,char* argv[]){
 if (argc!=4)
 {
  std::cout << "Usage:" << argv[0] << " " << argv[1] << " <language> <string-to-parse>" << std::endl;;
  return -1;
 }
 Parser parser;
 std::cout << parser.parse(std::string(argv[2]),std::string(argv[3]));
 std::cout << std::endl;
 return 0;
}
