#include "en/en.h"
#include "de/de.h"
#include "lt/lt.h"
#include "Language.h"
#include "parser/parser.h"
#include "cmdparse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Language* getLanguageFromStringId(char* Id){
 Language* ret;
 if (!strcmp(Id,"en")){
  ret = new en_en;
 }
 else if (!strcmp(Id,"de")){
  ret = new de;
 }
 else if (!strcmp(Id,"lt")){
  ret = new lt;
 }
 else exit(-1);
 return ret;
}
int main(int argc, char *argv[])
{
 if (argc<3){
  printf("Usage: %s <mode> <language>\n",argv[0]);
  return -1;
 }
 if (!strcmp(argv[1],"cmd")){
  return cmdParse(argc,argv);
 }else{
  printf("Unkown mode %s\n",argv[1]);
  printf("Usage: %s <mode> <language>\n",argv[0]);
  return -1;
 }
 return 0;
}