#define _CRT_SECURE_NO_WARNINGS
#include "Language.h"
#include "parser/parser.h"
#include "settings.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int fileParse(int argc,char* argv[]){
 if (argc!=5)
 {
  printf("Usage: %s %s <language> <input-file> <output-file>\n",argv[0],argv[1]);
  return -1;
 }
 FILE* rFile = fopen(argv[3],"r");
 FILE* wFile = fopen(argv[4],"w");
 char c = fgetc(rFile);
 while (c!=EOF){
  if (c!='$')
  {
   fputc(c,wFile);
  }else{
   //check for ${LANG in the worst way possible
   if ((c = fgetc(rFile)) == '{')
   {
     if ((c = fgetc(rFile)) == 'L')
     {     
       if ((c = fgetc(rFile)) == 'A')
       {    
         if ((c = fgetc(rFile)) == 'N')
         {
           if ((c = fgetc(rFile)) == 'G')
           {
	     //Allocate 1kB for the input buffer
             char* in = (char*)malloc(4096);
             int i=0;
  	     while (i<4096)
  	     {
		c = fgetc(rFile);   
                if (c==EOF){ return -1;	}
                if (c=='}') i=4096;
                in[i++]=c;
 	     }
             in[i]=0;
             Parser parser;
             std::string string;
             string = parser.parse(argv[2],in);
             fputs(string.c_str(),wFile);
             //free(in);
  		
           }else{fputs("${LAN",wFile);fputc(c,wFile);}
         }else{fputs("${LA",wFile);fputc(c,wFile);}
       }else{fputs("${L",wFile);fputc(c,wFile);}
     }else{fputs("${",wFile);fputc(c,wFile);}
   }else{fputc('$',wFile);fputc(c,wFile);}
  }
  c = fgetc(rFile);
 }
 fclose(rFile);
 fclose(wFile);
 return 0;
}
