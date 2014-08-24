#ifndef SETTINGS_H
#define SETTINGS_H
#define DICTIONARY "../lang/"
#define EN_EN_FOLDER "en/"
#define DE_FOLDER "de/"
#define BUFFER_SIZE 100
#define NUM_ADVERBS 5
#define EN_NEGATIVE "negative"
#define EN_EN_DONOT "don't "
#define EN_EN_ANDNOUN "and "
#define DE_UNDNOMEN "und "
#define DE_NEGATIVE "minus "
#define DE_AUTOCHANGESIMPLE 1
void warn(const char * message, const char * fallback);
int nDigits(int i);
#include "Language.h"
Language* getLanguageFromStringId(char* Id);


#define DE_CONTRACTPREPOSITIONS 1


#endif
