#include "../settings.h"
#include "en.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

std::string en::GetVerbPreAdd(int VerbNum)
{
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


std::string en::GetVerbPresentSimple(int VerbForm, int VerbNum, std::string Mid, bool IgnoreMid, bool HelperVerb)
{
	std::ifstream is(DICTIONARY EN_EN_FOLDER "verb_present");
	if (GotoLine(is,VerbNum)) return "";
	int Data = is.get();
	if (Data == '0')
	{
		if (GotoSegment(is,VerbForm+1)) return "";
		std::string Segment = GetSegment(is);
		is.close();
		if (!IgnoreMid && (VerbNum == 1 || HelperVerb) && Mid.compare("")!=0 ) Segment += " " + Mid;
		else if (!IgnoreMid && Mid.compare("")!=0)
		{
			return GetVerbPresentSimple(VerbForm,68,"",true) + " " + Mid + " " + GetVerbPresentSimple(0,VerbNum,"",true);
		}
		return Segment;
	}
	else
	{

		if (!IgnoreMid && Mid.compare("")!=0 && Data != '3')
		{
			is.close();
			return GetVerbPresentSimple(VerbForm,68,"",true) + " " + Mid + " " + GetVerbPresentSimple(0,VerbNum,"",true);
		}
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
		else if (!IgnoreMid && Mid.compare("")!=0) Segment+= " " + Mid;
		is.close();
		return Segment;
	}
	is.close();
	return "";
}

std::string en::GetVerbPresentProgressive(int VerbForm, int VerbNum, std::string Mid, bool IgnoreMid)
{
	return GetVerbPresentSimple(VerbForm,1,Mid) + " " + GetVerbPreAdd(VerbNum) + "ing";
}

std::string en::GetVerbPastSimple(int VerbForm, int VerbNum, std::string Mid, bool Perfect, bool IgnoreMid, bool HelperVerb)
{
	std::ifstream is(DICTIONARY EN_EN_FOLDER "verb_past");
	GotoLine(is,VerbNum);
	int Data = is.get();
	if (Data == '2' || Data == '3')
	{
		is.close();
		if (!IgnoreMid && Mid.compare("")!=0)
		{
			return GetVerbPastSimple(VerbForm,68,"",Perfect,true) + " " + Mid + " " + GetVerbPresentSimple(0,VerbNum,"",true,false);
		}
		std::string V = GetVerbPreAdd(VerbNum);
		if (Data == '3') V += "e";
		V += "d";
		return V;
	} 
	else if (Data == '1')
	{
		if (!IgnoreMid && Mid.compare("")!=0)
		{
			is.close();
			return GetVerbPastSimple(VerbForm,68,"",Perfect,true,true) + " " + Mid + " " + GetVerbPresentSimple(0,VerbNum,"",true);
		}
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
		if (!IgnoreMid && (VerbNum == 1 || HelperVerb) && Mid.compare("")!=0 ) Verb += " " + Mid;
		else if (!IgnoreMid && Mid.compare("")!=0)
		{
			return GetVerbPastSimple(VerbForm,68,"",Perfect,true,true) + " " + Mid + " " + GetVerbPresentSimple(0,VerbNum,"",true);
		}
		return Verb;
	}
	return "";
}

std::string en::GetVerbPastProgressive(int VerbForm, int VerbNum, std::string Mid, bool IgnoreMid)
{
	return GetVerbPastSimple(VerbForm,1,Mid,false) + " " + GetVerbPreAdd(VerbNum) + "ing";
}

std::string en::GetVerbPastPerfect(int VerbForm, int VerbNum, std::string Mid, bool IgnoreMid)
{
	return GetVerbPresentSimple(VerbForm,2,Mid,IgnoreMid,true) + " " + GetVerbPastSimple(1,VerbNum,"",true,true);
}

std::string en::GetVerbPastPerfectProgressive(int VerbForm, int VerbNum, std::string Mid, bool IgnoreMid)
{
	return GetVerbPastPerfect(VerbForm,1,Mid,IgnoreMid) + " " + GetVerbPreAdd(VerbNum) + "ing";
}

std::string en::GetVerbFutureSimple(int VerbForm, int VerbNum, std::string Mid, bool IgnoreMid)
{
	return FutureTenseMarker + " " + Mid + " " + GetVerbPresentSimple(0,VerbNum,"",true);
}

std::string en::GetVerbFutureProgressive(int VerbForm, int VerbNum, std::string Mid, bool IgnoreMid)
{
	return FutureTenseMarker + " " + Mid + " " + GetVerbPresentSimple(0,1,"",true) + " " + GetVerbPreAdd(VerbNum) + "ing";
}

std::string en::GetVerbFuturePast(int VerbForm, int VerbNum, std::string Mid, bool IgnoreMid)
{
	return FutureTenseMarker + " " + Mid + " " + GetVerbPastPerfect(0,VerbNum,"",true);
}

std::string en::GetVerbFuturePastProgressive(int VerbForm, int VerbNum, std::string Mid, bool IgnoreMid)
{

	return FutureTenseMarker + " " + Mid + " " + GetVerbPastPerfectProgressive(0,VerbNum,"",true);
}

std::string en::GetVerb(Noun& NounObj, int snum, int VerbNum, int SentenceType, std::string Mid)
{
	
	//If the verb is not a verb, return now, preventing any crashes.
	if (VerbNum == 0) return "";

	//First we need to figure out which form of a verb we need.
	//We can do this with Noun and snum information.

	//By default use the he/she/it verb form (append 's' in present tense)
	int VerbForm = 5;

	//If a pronoun, VerbForm is the pronoun number
	if (NounObj.ID < 10 && NounObj.ID > 0) VerbForm = NounObj.ID;
	//If more than one subject, or the subject is plural, use the plural form
	if (snum > 0 || NounObj.IsPlural) VerbForm = 8;
	//If there is no subjects, set the infinitive verb form.
	if (snum < 0) VerbForm = 0;

	if (Negate)
	{
		if (Mid.compare("")!=0)
			Mid += " ";
		Mid += "not";
	}
	
	//Then we need to get the verb string from the appropriate function, and return it.
	//We can do this with VerbNum and VerbForm information.
	switch (st)
	{
		case PRESENT_PROGRESSIVE:
			return GetVerbPresentProgressive(VerbForm,VerbNum,Mid);
		case PRESENT_SIMPLE:
			return GetVerbPresentSimple(VerbForm,VerbNum,Mid);
		case PAST_RECENT:
		case PAST_RECENT_FORMAL:			
			return GetVerbPastSimple(VerbForm,VerbNum,Mid);
		case PAST_RECENT_PROGRESSIVE:
		case PAST_RECENT_PROGRESSIVE_FORMAL:
			return GetVerbPastProgressive(VerbForm,VerbNum,Mid);
		case PAST_DISTANT:
		case PAST_DISTANT_FORMAL:
			return GetVerbPastPerfect(VerbForm,VerbNum,Mid);
		case PAST_DISTANT_PROGRESSIVE:
		case PAST_DISTANT_PROGRESSIVE_FORMAL:
			return GetVerbPastPerfectProgressive(VerbForm,VerbNum,Mid);
		case FUTURE_RECENT:
		case FUTURE_DISTANT:
			return GetVerbFutureSimple(VerbForm,VerbNum,Mid);
		case FUTURE_RECENT_PROGRESSIVE:
		case FUTURE_DISTANT_PROGRESSIVE:
			return GetVerbFutureProgressive(VerbForm,VerbNum,Mid);
		case FUTURE_PAST:
			return GetVerbFuturePast(VerbForm,VerbNum,Mid);
		case FUTURE_PAST_PROGRESSIVE:
			return GetVerbFuturePastProgressive(VerbForm,VerbNum,Mid);
		case PASSIVE_PRESENT_PROGRESSIVE:
			return GetVerbPassivePresentProgressive(VerbForm,VerbNum,Mid);
		case PASSIVE_PRESENT_SIMPLE:
			return GetVerbPassivePresentSimple(VerbForm,VerbNum,Mid);
		case PASSIVE_PAST_RECENT:
		case PASSIVE_PAST_RECENT_FORMAL:
			return GetVerbPassivePastSimple(VerbForm,VerbNum,Mid);
		case PASSIVE_PAST_RECENT_PROGRESSIVE:
		case PASSIVE_PAST_RECENT_FORMAL_PROGRESSIVE:
			return GetVerbPassivePastProgressive(VerbForm,VerbNum,Mid);
		case PASSIVE_PAST_DISTANT:
		case PASSIVE_PAST_DISTANT_FORMAL:
			return GetVerbPassivePastPerfect(VerbForm,VerbNum,Mid);		
		case PASSIVE_PAST_DISTANT_PROGRESSIVE:
		case PASSIVE_PAST_DISTANT_FORMAL_PROGRESSIVE:
			return GetVerbPassivePastPerfectProgressive(VerbForm,VerbNum,Mid);
		case PASSIVE_FUTURE_RECENT:
		case PASSIVE_FUTURE_DISTANT:
			return GetVerbPassiveFutureSimple(VerbForm,VerbNum,Mid);
		case PASSIVE_FUTURE_RECENT_PROGRESSIVE:
		case PASSIVE_FUTURE_DISTANT_PROGRESSIVE:
			return GetVerbPassiveFutureProgressive(VerbForm,VerbNum,Mid);
		case PASSIVE_FUTURE_PAST:
			return GetVerbPassiveFuturePast(VerbForm,VerbNum,Mid);
		case PASSIVE_FUTURE_PAST_PROGRESSIVE:
			return GetVerbPassiveFuturePastProgressive(VerbForm,VerbNum,Mid);	
		case BUTTON_TEXT:
			return GetVerbPresentSimple(VerbForm,VerbNum,Mid);
	}
	return "";
}

std::string en::GetOtherVerb(int VerbNum1,int VerbNum2)
{
	
	int data = '1';
	if (VerbNum1!=0)
	{
		std::ifstream is(DICTIONARY EN_EN_FOLDER "verb_present");
		GotoLine(is,VerbNum1);
		is.get();
		data = is.get();
		is.close();
	}
	if (data == '2')
		return GetVerbPreAdd(VerbNum2) + "ing";
	else if (data == '3' || data == '0')
		return GetVerbPresentSimple(0,VerbNum2);
	else if (data == '1')
		return "to " + GetVerbPresentSimple(0,VerbNum2);
	return GetVerbPresentSimple(0,VerbNum2);
}
