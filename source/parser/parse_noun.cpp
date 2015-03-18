#include "parser.h"
#include "../Language.h"
#include <stdio.h>
#include <stdlib.h>
#include "../settings.h"
noun* Parser::parseNoun(){
 
 noun* n = new noun;
 n->id = getInt();
 expect(',',__FILE__,__LINE__);
 n->num = getInt();
 expect(',',__FILE__,__LINE__);
 if (rstLook() && check("true"))
  n->reflex=true;
 else if (rstLook() && check("false"))
  n->reflex=false;
 else error("Couldn't parse boolean",__FILE__,__LINE__);
 expect(',',__FILE__,__LINE__);
 if (rstLook() && check("true"))
  n->plural=true;
 else if (rstLook() && check("false"))
  n->plural=false;
 else error("Couldn't parse boolean",__FILE__,__LINE__);
 expect(',',__FILE__,__LINE__);
 n->typ = getInt();
 expect(',',__FILE__,__LINE__);
 if (rstLook() && check("true"))
  n->usegenitive=true;
 else if (rstLook() && check("false"))
  n->usegenitive=false;
 else error("Couldn't parse boolean (genitive-bool)",__FILE__,__LINE__);
 if (n->usegenitive==true)
 {
  expect(',',__FILE__,__LINE__);
  expect('n',__FILE__,__LINE__);
  expect('(',__FILE__,__LINE__);
  n->genitivenoun = parseNoun();
  expect(')',__FILE__,__LINE__);
 }
 expect(',',__FILE__,__LINE__);
 if (rstLook() && check("true"))
 {
  expect(',',__FILE__,__LINE__);
  n->prepos = getInt();
 }
 else if (rstLook() && check("false"))
  n->prepos = 0;
 else error("Couldn't parse boolean (preposition-bool)",__FILE__,__LINE__);
 if (n->num>2 || n->num<-2)
  n->plural = true;
 for (int i = 0; i < 16; ++i)
 {
  n->adj[i]=0;
 }
 return n;
}

