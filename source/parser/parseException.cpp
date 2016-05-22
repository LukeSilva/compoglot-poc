#include "parseException.h"

std::ostream& operator<<(std::ostream& os, const parseException& pe)
{
	os << "Parse Exception: " << pe.error << std::endl;

	os << pe.input << std::endl;

	for (int i = 0; i < pe.pos; ++i)
		os << " ";

	os << "^" << std::endl;

	return os;
}

