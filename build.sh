CFLAGS="-Wall -std=c++11"
BASEFILES="cmdparse.cpp fileparse.cpp main.cpp Language.cpp general.cpp"
PARSERFILES="parser.cpp parser_io.cpp parse_noun.cpp"
DEFILES="de.cpp de_nouns.cpp de_articles.cpp de_verbs.cpp de_numerals.cpp de_prepos.cpp de_adjectives.cpp de_conjunctions.cpp"
ENFILES="en.cpp en_nouns.cpp en_articles.cpp en_numerals.cpp en_verbs.cpp en_passiveverbs.cpp en_prepos.cpp en_adjectives.cpp en_conjunctions.cpp"
EOFILES="eo.cpp eo_nouns.cpp"
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

eo()
{
	echo
	echo "Compiling eo..."
	echo
	for file in $EOFILES
	do
		echo $file
		g++ $CFLAGS -c "${FILEPREFIX}eo/$file"
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
	eo
else
	$PART
fi

if [[ "$PART" != "clean" ]]
then
	echo
	echo "Linking..."
	echo
	g++ -o compoglot *.o
	cp compoglot ../examples/
fi
