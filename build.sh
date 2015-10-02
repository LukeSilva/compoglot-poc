CFLAGS="-Wall -std=c++11"
BASEFILES="cmdparse.cpp fileparse.cpp main.cpp Language.cpp general.cpp"
PARSERFILES="parser.cpp parser_io.cpp parse_noun.cpp"
EN_OLDFILES="en_old.cpp en_old_nouns.cpp en_old_articles.cpp en_old_verbs.cpp en_old_adjectives.cpp en_adverbs.cpp en_old_prepos.cpp en_old_conjunctions.cpp en_general.cpp"
DEFILES="de.cpp de_nouns.cpp de_articles.cpp de_verbs.cpp de_numerals.cpp de_prepos.cpp de_adjectives.cpp"
ENFILES="en.cpp en_nouns.cpp en_articles.cpp en_numerals.cpp en_verbs.cpp en_passiveverbs.cpp en_prepos.cpp en_adjectives.cpp en_conjunctions.cpp"
FILEPREFIX="../source/"
base()
{
	echo
	echo "Compiling base..."
	echo
	for file in $BASEFILES
	do
		echo $file
		g++ $CFLAGS -c "${FILEPREFIX}$file"
	done
}

parser()
{
	echo
	echo "Compiling parser..."
	echo
	for file in $PARSERFILES
	do
		echo $file
		g++ $CFLAGS -c "${FILEPREFIX}parser/$file"
	done
}

en()
{
	echo
	echo "Compiling en..."
	echo
	for file in $ENFILES
	do
		echo $file
		g++ $CFLAGS -c "${FILEPREFIX}en/$file"
	done
}

de()
{
	echo
	echo "Compiling de..."
	echo
	for file in $DEFILES
	do
		echo $file
		g++ $CFLAGS -c "${FILEPREFIX}de/$file"
	done
}

clean()
{
	echo
	echo "Cleaning up..."
	echo
	rm *.o
}

mkdir -p build
cd build

PART=$1
if [[ -z "$PART" ]]
then
	base
	parser
	en
	de
else
	$PART
fi

if [[ "$PART" != "clean" ]]
then
	echo
	echo "Linking..."
	echo
	g++ -o lang *.o
	cp lang ../examples/
fi
