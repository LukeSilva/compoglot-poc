#include "parser.h"
#include "../Language.h"
#include <stdio.h>
#include <stdlib.h>
#include "../settings.h"
noun* Parser::parseNoun(){
 
 noun* n = new noun;
 n->id = getInt();
 n->data = 0;
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
 expect(',',__FILE__,__LINE__);
 if (rstLook() && check("true"))
 {
  expect(',',__FILE__,__LINE__);
  if (rstLook() && check("true"))
  {
   n->rClauseEssential = true;
  }
  else if (rstLook() && check("false"))
  {
   n->rClauseEssential = false;
  }
  else error("Couldn't parse boolean (rClause-Essential-bool)",__FILE__,__LINE__);
  expect(',',__FILE__,__LINE__);
  n->rClauseObj = getInt();
  expect(',',__FILE__,__LINE__);
  expect('(',__FILE__,__LINE__);
  Language* nlang = getLanguageFromStringId(langid);
  nlang->newSentence();
  nlang->s[0].id = 14;
  nlang->s[0].plural=n->plural;
	nlang->snum = 0;	
  _parse(nlang);
  nlang->punctuation = false;
  n->rClause = nlang;
  n->useRClause = true;
 }
 else if (rstLook() && check("false"))
 {
  n->useRClause = false;
 }
 else error("Couldn't parse boolean (rClause-bool)",__FILE__,__LINE__);
 if (n->num>2 || n->num<-2)
  n->plural = true;
 for (int i = 0; i < 16; ++i)
 {
  n->adj[i]=0;
 }
 return n;
}

