#include "../settings.h"
#include "en.h"
#include <string>
#include <iostream>
#include <fstream>

std::string en_Articles[] = {"a", "the", "", "my", "your", "his", "her", "its", "our", "your", "their", "your", "a lot of ","this"};

std::string en::GetArticle(noun* Noun,bool NextLetterIsVowel)
{
#ifdef DEBUG
	std::cout << "[EN] GetArticle(noun* Noun,bool NextLetterIsVowel)" << std::endl;
#endif
	if (Noun->typ < -2 || Noun->typ > 11) return "";
	std::string Article = en_Articles[Noun->typ+2];
	if (NextLetterIsVowel && Noun->typ == -2)
		Article+="n";
	return Article;
}
