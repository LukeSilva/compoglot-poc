#include "parser.h"
#include <iostream>
#include "../settings.h"
bool Parser::rstLook(){
	lookptr=ptr;
	look=string[lookptr];
	//So that rstLook can be used in if statements
	return true;
}
bool Parser::rstPtr(){
	ptr=lookptr;
	look=string[lookptr];
	//So that rstPtr can be used in if statements
	return true;
}
char Parser::LookAHead(){
	look=string[++lookptr];
	//Skip over whitespace
	if (look==' ' || look=='\n' || look=='\t')
		LookAHead();
	return look;
}
bool Parser::check(const char* _string){
	int _ptr=0;
	while(_string[_ptr]!=0){
		if(string[lookptr]!=_string[_ptr]) return false;
		lookptr++;
		_ptr++;
	}
	return true;
}
void Parser::error(char* str,const char* file,int line){
	std::cerr << "Error \"" << str << "\" (" << file << ":" << line << ") at "<< ptr << "," << lookptr << std::endl << string << std::endl;
	exit(-1);
}
void Parser::error(const char* str,const char* file,int line){
	std::cerr << "Error \"" << str << "\" (" << file << ":" << line << ") at " << line << "," << ptr << std::endl << string << std::endl;
	exit(-1);
}
void Parser::expect(char c,const char* file,int line){
	if (string[lookptr]!=c){
		if(c==' ')
			std::cerr << "Expected (space) (" << file << ":" << line << ") at " << ptr << "," << lookptr << std::endl;
		else
			std::cerr << "Expected '" << c << "' (" << file << ":" << line << ") at " << ptr << "," << lookptr << std::endl;
		std::cerr << "Code: \"" << string << "\"" << std::endl;
		exit(-1);
	}
	LookAHead();
	rstPtr();
}

int Parser::getInt()
{
	//Taken from stackoverflow.com/questions/4442658/c-parse-int-from-string
	char* s = &string[ptr];
	if ( s == NULL || *s == '\0' )
		error("null or empty string argument while parsing integer",__FILE__,__LINE__);

	bool negate = (s[0] == '-');

	if ( *s == '+' || *s == '-' ) 
		++s;

	if ( *s == '\0')
		error("sign character only while parsing integer",__FILE__,__LINE__);

	int result = 0;
	while(*s)
	{
		if ( *s >= '0' && *s <= '9' )
		{
			result = result * 10  - (*s - '0');  //assume negative number
		}
		else{
			++s;
			break;
		}
		++s;
	}
	ptr = s-&string[0]-1;
	rstLook();
	return negate ? result : -result; //-result is positive!
}
