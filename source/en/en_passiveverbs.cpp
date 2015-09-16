#include "../settings.h"
#include "en.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

std::string en::GetVerbPassivePresentProgressive(int VerbForm, int VerbNum)
{
#ifdef DEBUG
	std::cout << "[EN] GetVerbPassivePresentProgressive(int VerbForm = " << VerbForm << " , int VerbNum = " << VerbNum << " )" << std::endl;
#endif
	return GetVerbPresentProgressive(VerbForm,1) + " " + GetVerbPastSimple(0,VerbNum);
}
