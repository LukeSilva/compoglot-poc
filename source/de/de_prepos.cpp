#include "../settings.h"
#include "de.h"
#include <string>
#include <iostream>
#include <fstream>



std::string de::GetPrepos(Noun& n)
{
	if (n.PreposNum<1) return "";
	std::ifstream is(DICTIONARY DE_FOLDER "prepos.txt");
	if (GotoLine(is,n.PreposNum)) return "";
	int Data = is.get();
	if (Data == '1')
	{
		int Case = is.get();
		n.Data = Case - '0';
	}
	if (GotoSegment(is,1)) return "";
	std::string Segment = GetSegment(is);
	is.close();
	return Segment;
}