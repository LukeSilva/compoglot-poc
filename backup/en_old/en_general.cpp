#include "en.h"
#include "../settings.h"
#include "../parser/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void en_en::parseVerb(int verb,int n){
 FILE * rFile=fopen(DICTIONARY EN_EN_FOLDER "general","r");
 gotoline(rFile,n);
 char* buf = (char*)calloc(BUFFER_SIZE,sizeof(char));
 fgets(buf,BUFFER_SIZE*2-1,rFile);
 fclose(rFile);
 Parser* p=new Parser; 
 p->string=buf;
 p->ptr=0;
 p->lookptr=0;
 p->look=buf[0];
 p->verb=verb;
 p->expect('(',__FILE__,__LINE__);
 p->_parse(this);
 
}
