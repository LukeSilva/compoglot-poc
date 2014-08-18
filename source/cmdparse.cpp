#include "Language.h"
#include "parser/parser.h"
#include "settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cmdParse(int argc,char* argv[]){
 if (argc!=4)
 {
  printf("Usage: %s %s <language> <string-to-parse>\n",argv[0],argv[1]);
  return -1;
 }
 Parser parser;
 printf("%s\n",parser.parse(argv[2],argv[3]));
 return 0;
}
