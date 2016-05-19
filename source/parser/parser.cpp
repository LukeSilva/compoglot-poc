#include "parser.h"
#include <stdio.h>
#include "../settings.h"
#include "../Language.h"
void Parser::_parseSubject(Language* lang){
	int sub=0;
	int subadj=0;
	while (rstLook() && string[lookptr]!=')'){
		if (rstLook() && LookAHead()==0){
			error("Premature end of string",__FILE__,__LINE__);
		}
		else if (rstLook() && check("n")){
			rstPtr();
			expect('(',__FILE__,__LINE__);
			Noun* n=parseNoun();
			lang->Subjects[sub]=*n;
			expect(')',__FILE__,__LINE__);
		}
		else if (rstLook() && check("adj")){
			rstPtr();
			expect('(',__FILE__,__LINE__);
			lang->Subjects[sub].Adjectives[subadj]=getInt();
			expect(')',__FILE__,__LINE__);
		}
		else if (rstLook() && check("it")){
			rstPtr();
			expect('(',__FILE__,__LINE__);
			int i = getInt();
			Noun* n=lang->getIt(i);
			lang->Subjects[sub]=*n;
			expect(')',__FILE__,__LINE__);
		}
		else if (rstLook() && check(",")){
			rstPtr();
			sub++;
			subadj=0;
		}
		else{
			error("Unkown Token!",__FILE__,__LINE__);
		}
	}
	LookAHead();
	rstPtr();
	lang->NumFilledSubjects=sub;
}
void Parser::__parseObject(Language* lang,int objid){
	int obj=0;
	int objadj=0;
	while (rstLook() && string[lookptr]!=')'){
		if (rstLook() && LookAHead()==0){
			error("Premature end of string",__FILE__,__LINE__);
		}
		else if (rstLook() && check("n")){
			rstPtr();
			expect('(',__FILE__,__LINE__);
			Noun* n=parseNoun();
			lang->Objects[objid][obj]=*n;
			expect(')',__FILE__,__LINE__);
		}
		else if (rstLook() && check("adj")){
			rstPtr();
			expect('(',__FILE__,__LINE__);
			if (lang->Objects[objid][obj].ID == 0)
			{
				lang->Objects[objid][obj].ID = 14;
			}
			lang->Objects[objid][obj].Adjectives[objadj]=getInt();
			expect(')',__FILE__,__LINE__);
			objadj++;
		}
		else if (rstLook() && check("it")){
			rstPtr();
			expect('(',__FILE__,__LINE__);
			int i = getInt();
			Noun* n=lang->getIt(i);
			lang->Objects[objid][obj]=*n;
			expect(')',__FILE__,__LINE__);
		}
		else if (rstLook() && check("reflex")){
			rstPtr();
			expect('(',__FILE__,__LINE__);
			expect(')',__FILE__,__LINE__);
			Noun* n=lang->getIt(lang->Subjects[0].ID);
			n->IsReflexive = true;
			lang->Objects[objid][obj]=*n;
		}
		else if (rstLook() && check(",")){
			rstPtr();
			obj++;
			objadj=0;
		}
		else{
			error("Unkown Token!",__FILE__,__LINE__);
		}
	}
	LookAHead();
	rstPtr();
	lang->NumFilledObjects[objid]=obj;
}

void Parser::__parseObjects(Language* lang){
	while (rstLook() && string[lookptr]!=')'){
		if (rstLook() && LookAHead()==0){
			error("premature end of string",__FILE__,__LINE__);
		}
		else{
			int i = getInt();
			if (i > 0 && i < 9){
				i=i-1;
				expect('(',__FILE__,__LINE__);
				__parseObject(lang,i);
			}else{
				error("object identifier was out of range",__FILE__,__LINE__);
			}
		}
	}	
	LookAHead();
	rstPtr();
}
void Parser::_parse(Language* lang){
	while (rstLook() && string[lookptr]!=')')
	{
		if (rstLook() && LookAHead()==0)
		{
			error("Premature end of string",__FILE__,__LINE__);
		}
		else if (rstLook() && check("sub"))
		{
			rstPtr();
			expect('(',__FILE__,__LINE__);
			_parseSubject(lang);
		}
		else if (rstLook() && check("obj"))
		{
			rstPtr();
			expect('(',__FILE__,__LINE__);
			__parseObjects(lang);	
		}
		else if (rstLook() && check("oprepos"))
		{
			rstPtr();
			expect('(',__FILE__,__LINE__);
			int id = getInt() - 1;
			if (id < 0 || id > 7)
			{
				error("Invalid id for oprepos()",__FILE__,__LINE__);
			}
			expect(',',__FILE__,__LINE__);
			int prepos = getInt();
			for (int i = 0; i < 16; ++i)
			{
				lang->Objects[id][i].PreposNum = prepos;
			}
			expect(')',__FILE__,__LINE__);
		}
		else if (rstLook() && check("oarticle"))
		{
			rstPtr();
			expect('(',__FILE__,__LINE__);
			int id = getInt() - 1;
			if (id < 0 || id > 7)
			{
				error("Invalid id for oarticle()",__FILE__,__LINE__);
			}
			expect(',',__FILE__,__LINE__);
			int article = getInt();
			for (int i = 0; i < 16; ++i)
			{
				lang->Objects[id][i].ArticleType = article;
			}
			expect(')',__FILE__,__LINE__);
		}
		else if (rstLook() && check("sarticle"))
		{
			rstPtr();
			expect('(',__FILE__,__LINE__);
			int article = getInt();
			for (int i = 0; i < 16; ++i)
			{
				lang->Subjects[i].ArticleType = article;
			}
			expect(')',__FILE__,__LINE__);
		}
		else if (rstLook() && check("datao"))
		{
			rstPtr();
			expect('(',__FILE__,__LINE__);
			int id = getInt() - 1;
			if (id < 0 || id > 7)
			{
				error("Invalid id for datao()",__FILE__,__LINE__);
			}
			expect(',',__FILE__,__LINE__);
			int data = getInt();
			for (int i = 0; i  < 16; ++i)
			{
				lang->Objects[id][i].Data=data;
			}
			expect(')',__FILE__,__LINE__);
		}
		else if (rstLook() && check("octype"))
		{
			rstPtr();
			expect('(',__FILE__,__LINE__);
			int id = getInt() - 1;
			if (id < 0 || id > 7 )
			{
				error("Invalid id for octype()",__FILE__,__LINE__);
			}
			expect(',',__FILE__,__LINE__);
			int ctype = getInt();
			lang->ObjConjunctionType[id] = ctype;
			expect(')',__FILE__,__LINE__);
		}
		else if (rstLook() && check("datas"))
		{
			expect('(',__FILE__,__LINE__);
			int data = getInt();
			for (int i = 0; i < 16; ++i)
			{
				lang->Subjects[i].Data=data;
			}
			expect(')',__FILE__,__LINE__);
		}
		else if (rstLook() && check("sctype"))
		{
			expect('(',__FILE__,__LINE__);
			int data = getInt();
			lang->SubConjunctionType=data;
			expect(')',__FILE__,__LINE__);
		}
		else if (rstLook() && check("Verb1"))
		{
			rstPtr();
			expect('(',__FILE__,__LINE__);
			lang->ExtVerb1=getInt();
			expect(')',__FILE__,__LINE__);
		} 
		else if (rstLook() && check("Verb2"))
		{
			rstPtr();
			expect('(',__FILE__,__LINE__);
			lang->ExtVerb2=getInt();
			expect(')',__FILE__,__LINE__);
		} 	
		else if (rstLook() && check("Verb3"))
		{
			rstPtr();
			expect('(',__FILE__,__LINE__);
			lang->ExtVerb3=getInt();
			expect(')',__FILE__,__LINE__);
		} 
		else if (rstLook() && check("Verb"))
		{
			rstPtr();
			expect('(',__FILE__,__LINE__);
			if (verb==0) lang->Verb1 = getInt();
			else lang->Verb2 =getInt();
			expect(')',__FILE__,__LINE__);
		}
		else if (rstLook() && check("v1"))
		{
			rstPtr();
			expect('(',__FILE__,__LINE__);
			lang->Verb1 = getInt();
			expect(')',__FILE__,__LINE__);
		}  
		else if (rstLook() && check("v2"))
		{
			rstPtr();
			expect('(',__FILE__,__LINE__);
			lang->Verb2 = getInt();
			expect(')',__FILE__,__LINE__);
		}
		else if (rstLook() && check("neg "))
		{
			rstPtr();
			lang->Negate=!lang->Negate;
		}
		else if (rstLook() && check("clause"))
		{
			rstPtr();
			expect('(',__FILE__,__LINE__);
			int conj = getInt();
			expect(',',__FILE__,__LINE__);
			Language* nlang = getLanguageFromStringId(langid);
			nlang->NewSentence();
			_parse(nlang);
			lang->Conjunction = conj;
			lang->SubClause=nlang;
		}
		else if (rstLook() && check("question"))
		{
			rstPtr();
			expect('(',__FILE__,__LINE__);
			lang->Question=getInt();
			expect(')',__FILE__,__LINE__);
		}
		else if (rstLook() && check("st"))
		{
			rstPtr();
			expect(' ',__FILE__,__LINE__);
			lang->st=getInt();
			expect(' ',__FILE__,__LINE__);
		}
		else if (rstLook() && check("punc"))
		{
			rstPtr();
			expect(' ',__FILE__,__LINE__);
			lang->Punctuation = getInt();
			expect(' ',__FILE__,__LINE__);
		}
		else
		{
			error("Unknown Token",__FILE__,__LINE__);
		}
	} 
}
std::string Parser::parse(char* _langid,std::string in){
	//Setup internals
	ptr=0;
	lookptr=0;
	string=in;
	look=in[lookptr];
	Language* lang;
	langid=_langid;
	//default Verb(x) to v1(x)
	verb=0;
	//Create the language class form the langid
	lang = getLanguageFromStringID(std::string(langid));
	lang->NewSentence();
	//Setup progressive present tense for default, should be in Language.cpp
	lang->st = 1;
	//Expect an opening clause
	expect('(',__FILE__,__LINE__);
	//Now do the parsing on lang
	_parse(lang);
	return lang->createSentence();
}
