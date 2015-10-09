#include "../settings.h"
#include "eo.h"
#include <string>
#include <iostream>
#include <fstream>

const std::string eo::Articles[14] = { "","la","","mia","via","lia","ŝia","ĝia","nia","via","ilia","via","multe de","ĉi tiu"};


std::string eo::GetArticle(Noun& NounObj)
{
	if (NounObj.ArticleType < -2 || NounObj.ArticleType > 11) return "";
	std::string Article = Articles[NounObj.ArticleType+2];
	return Article;
}
