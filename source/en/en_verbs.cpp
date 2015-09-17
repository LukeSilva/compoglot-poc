#include "../settings.h"
#include "en.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

std::string en::GetVerbPreAdd(int VerbNum)
{
#ifdef DEBUG
	std::cout << "[EN] GetVerbPreAdd(int VerbNum = " << VerbNum << " )" << std::endl;
#endif
	std::ifstream is (DICTIONARY EN_EN_FOLDER "verb_present");
	if (GotoLine(is,VerbNum)) return "";
	int Data = is.get();
	if (Data == '1')
	{
		if (GotoSegment(is,2)) return "";
		std::string Segment = GetSegment(is);
		is.close();
		return Segment;
	}
	else if (Data == '0')
	{
		if (GotoSegment(is,11)) return "";
		std::string Segment = GetSegment(is);
		is.close();
		return Segment;
	}
	else
	{
		if (GotoSegment(is,1)) return "";
		std::string Segment = GetSegment(is);
		is.close();
		//Now follow all the english spelling rules
		//http://www.oxforddictionaries.com/words/verb-tenses-adding-ed-and-ing
		//http://www.grammar.cl/Notes/Spelling_ING.htm
		int u = Segment.length();
		if (Segment[u-1] == 'e' && Segment[u-2] == 'i')
		{
			//Turn 'ie' into y
			Segment = Segment.substr(0,u-2);
			Segment += "y";
		}
		else if (Segment[u-1] == 'e' && ( Segment[u-2] != 'e' && Segment[u-2] != 'y' && Segment[u-2] != 'o' ))
		{
			//Drop final e, if e is not before y,e or o
			//make -> mak ( + {ed,ing} )
			Segment = Segment.substr(0,u-1);
		}
		else if (Segment[u-1] == 'c')
		{
			//Add a k after a c
			//picnic -> picnick ( + {ed,ing} )
			Segment += "k";
		}
		else if (!IsVowel(Segment[u-3]) && IsVowel(Segment[u-2]) && !IsVowel(Segment[u-1]) && Segment[u-1]!='x' && Segment[u-1]!='y' && Segment[u-1]!='z' && Segment[u-1]!='w')
		{
			//Double consonant after consonant-vowel-consonant cluster.
			//Provided that final consonant is not w,x,y or z
			//Travel -> Travell ( + {ed,ing} )
			Segment += Segment[u-1];
		}
		return Segment;
	}
	return "";
}


std::string en::GetVerbPresentSimple(int VerbForm, int VerbNum)
{
#ifdef DEBUG
	std::cout << "[EN] GetVerbPresentSimple(int VerbForm = " << VerbForm << " , int VerbNum = " << VerbNum << " ) " << std::endl;
#endif
	std::ifstream is(DICTIONARY EN_EN_FOLDER "verb_present");
	if (GotoLine(is,VerbNum)) return "";
	int Data = is.get();
	if (Data == '0')
	{
		if (GotoSegment(is,VerbForm+1)) return "";
		std::string Segment = GetSegment(is);
		is.close();
		return Segment;
	}
	else
	{
		if (GotoSegment(is,1)) return "";
		std::string Segment = GetSegment(is);
		if (Data != '3')
		{
			if (VerbForm > 2 && VerbForm < 6)
			{
				//Need to add 's' conjugation
				int u = Segment.length();
				if (Segment[u-1]=='o' || (Segment[u-1]=='s' && Segment[u-2]=='s') || (Segment[u-1]=='h' && Segment[u-2]=='s') || (Segment[u-1]=='h' && Segment[u-2]=='c') || (Segment[u-1]=='z' && Segment[u-2]=='z') || Segment[u-1]=='x')
				{
					Segment +="e";
				}
				Segment += "s";
			}
		}
		is.close();
		return Segment;
	}
	is.close();
	return "";
}

std::string en::GetVerbPresentProgressive(int VerbForm, int VerbNum)
{
#ifdef DEBUG
	std::cout << "[EN] GetVerbPresentProgressive(int VerbForm = " << VerbForm << " ,int VerbNum = " << VerbNum << " )" << std::endl;
#endif
	return GetVerbPresentSimple(VerbForm,1) + " " + GetVerbPreAdd(VerbNum) + "ing";
}

std::string en::GetVerbPastSimple(int VerbForm, int VerbNum, bool Perfect)
{
#ifdef DEBUG
	std::cout << "[EN] GetVerbPastSimple(int VerbForm = " << VerbForm << ", int VerbNum = " << VerbNum << " )" << std::endl;
#endif
	std::ifstream is(DICTIONARY EN_EN_FOLDER "verb_past");
	GotoLine(is,VerbNum);
	int Data = is.get();
	if (Data == '2' || Data == '3')
	{
		is.close();
		std::string V = GetVerbPreAdd(VerbNum);
		if (Data == '3') V += "e";
		V += "d";
		return V;
	} 
	else if (Data == '1')
	{
		if(GotoSegment(is,Perfect?2:1))
		{
			is.close();
			return "";
		}
		std::string Verb = GetSegment(is);
		is.close();
		return Verb;
	}
	else if (Data == '0')
	{
		if (Perfect) VerbForm = 0;
		if (GotoSegment(is,VerbForm+1))
		{
			is.close();
			return "";
		}
		std::string Verb = GetSegment(is);
		is.close();
		return Verb;
	}
	return "";
}

std::string en::GetVerbPastProgressive(int VerbForm, int VerbNum)
{
#ifdef DEBUG
	std::cout << "[EN] GetVerbPastProgressive(int VerbForm = " << VerbForm << " , VerbNum = " << VerbNum << " )" << std::endl;
#endif
	return GetVerbPastSimple(VerbForm,1,false) + " " + GetVerbPreAdd(VerbNum) + "ing";
}

std::string en::GetVerbPastPerfect(int VerbForm, int VerbNum)
{
#ifdef DEBUG
	std::cout << "[EN] GetVerbPastPerfect(int VerbForm = " << VerbForm << " , VerbNum = " << VerbNum << " )" << std::endl;
#endif
	return GetVerbPresentSimple(VerbForm,2) + " " + GetVerbPastSimple(1,VerbNum,true);
}

std::string en::GetVerbPastPerfectProgressive(int VerbForm, int VerbNum)
{
#ifdef DEBUG
	std::cout << "[EN] GetVerbPastPerfectProgressive(int VerbForm = " << VerbForm << " , VerbNum = " << VerbNum << " )" << std::endl;
#endif
	return GetVerbPastPerfect(VerbForm,1) + " " + GetVerbPreAdd(VerbNum) + "ing";
}

std::string en::GetVerbFutureSimple(int VerbForm, int VerbNum)
{
#ifdef DEBUG
	std::cout << "[EN] GetVerbFutureSimple(int VerbForm = " << VerbForm << " , VerbNum = " << VerbNum << " )" <<std::endl;
#endif
	return FutureTenseMarker + " " + GetVerbPresentSimple(0,VerbNum);
}

std::string en::GetVerbFutureProgressive(int VerbForm, int VerbNum)
{
#ifdef DEBUG
	std::cout << "[EN] GetVerbFutureProgressive(int VerbForm = " << VerbForm << " , VerbNum = " << VerbNum << " )" << std::endl;
#endif
	return FutureTenseMarker + " " + GetVerbPresentSimple(0,1) + " " + GetVerbPreAdd(VerbNum) + "ing";
}

std::string en::GetVerbFuturePast(int VerbForm, int VerbNum)
{
#ifdef DEBUG
	std::cout << "[EN] GetVerbFuturePast(int VerbForm = " << VerbForm << " , VerbNum = " << VerbNum << " )" << std::endl;
#endif
	return FutureTenseMarker + " " + GetVerbPastPerfect(0,VerbNum);
}

std::string en::GetVerbFuturePastProgressive(int VerbForm, int VerbNum)
{
#ifdef DEBUG
	std::cout << "[EN] GetVerbFuturePastProgressive(int VerbForm = " << VerbForm << " , VerbNum = " << VerbNum << " )" << std::endl;
#endif
	return FutureTenseMarker + " " + GetVerbPastPerfectProgressive(0,VerbNum);
}

std::string en::GetVerb(noun& Noun, int snum, int VerbNum, int SentenceType)
{
#ifdef DEBUG
	std::cout << "[EN] GetVerb(noun& Noun, int snum = " << snum << " , int VerbNum = " << VerbNum << " , int SentenceType = " << SentenceType << " )" << std::endl;
#endif


	//First we need to figure out which form of a verb we need.
	//We can do this with Noun and snum information.

	//By default use the he/she/it verb form (append 's' in present tense)
	int VerbForm = 5;

	//If a pronoun, VerbForm is the pronoun number
	if (Noun.id < 10 && Noun.id > 0) VerbForm = Noun.id;
	//If more than one subject, or the subject is plural, use the plural form
	if (snum > 0 || Noun.plural) VerbForm = 8;
	//If there is no subjects, set the infinitive verb form.
	if (snum < 0) VerbForm = 0;

#ifdef DEBUG
	std::cout << "[EN] VerbForm = " << VerbForm << std::endl;
#endif
	//Then we need to get the verb string from the appropriate function, and return it.
	//We can do this with VerbNum and VerbForm information.
	if (st == 0)
		return GetVerbPresentProgressive(VerbForm,VerbNum);
	else if (st == 1)
		return GetVerbPresentSimple(VerbForm,VerbNum);
	else if (st == 2 || st == 3)
		return GetVerbPastSimple(VerbForm,VerbNum);
	else if (st == 4 || st == 5)
		return GetVerbPastProgressive(VerbForm,VerbNum);
	else if (st == 6 || st == 7)
		return GetVerbPastPerfect(VerbForm,VerbNum);
	else if (st == 8 || st == 9)
		return GetVerbPastPerfectProgressive(VerbForm,VerbNum);
	else if (st == 10 || st == 12)
		return GetVerbFutureSimple(VerbForm,VerbNum);	
	else if (st == 11 || st == 13)
		return GetVerbFutureProgressive(VerbForm,VerbNum);
	else if (st == 14)
		return GetVerbFuturePast(VerbForm,VerbNum);
	else if (st == 15)
		return GetVerbFuturePastProgressive(VerbForm,VerbNum);
	else if (st == 16)
		return GetVerbPassivePresentProgressive(VerbForm,VerbNum);
	else if (st == 17)
		return GetVerbPassivePresentSimple(VerbForm,VerbNum);
	else if (st == 18 || st == 19)
		return GetVerbPassivePastSimple(VerbForm, VerbNum);
	else if (st == 20 || st == 21)
		return GetVerbPassivePastProgressive(VerbForm,VerbNum);
	else if (st == 22 || st == 23)
		return GetVerbPassivePastPerfect(VerbForm,VerbNum);
	else if (st == 24 || st == 25)
		return GetVerbPassivePastPerfectProgressive(VerbForm,VerbNum);
	else if (st == 26 || st == 28)
		return GetVerbPassiveFutureSimple(VerbForm,VerbNum);
	else if (st == 27 || st == 29)
		return GetVerbPassiveFutureProgressive(VerbForm,VerbNum);
	else if (st == 30)
		return GetVerbPassiveFuturePast(VerbForm,VerbNum);
	else if (st == 31)
		return GetVerbPassiveFuturePastProgressive(VerbForm,VerbNum);
	return GetVerbPastSimple(VerbForm,VerbNum);
}
