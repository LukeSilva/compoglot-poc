cd source
CFLAGS="-Wall -std=c++11"
BASEFILES="cmdparse.cpp fileparse.cpp main.cpp Language.cpp general.cpp"
PARSERFILES="parser.cpp parser_io.cpp parse_noun.cpp"
EN_OLDFILES="en_old.cpp en_old_nouns.cpp en_old_articles.cpp en_old_verbs.cpp en_old_adjectives.cpp en_adverbs.cpp en_old_prepos.cpp en_old_conjunctions.cpp en_general.cpp"
DEFILES="de.cpp de_articles.cpp de_nouns.cpp de_verbs.cpp de_prepos.cpp de_adjectives.cpp de_conjunctions.cpp de_general.cpp"
ENFILES="en.cpp en_nouns.cpp en_articles.cpp en_numerals.cpp en_verbs.cpp en_passiveverbs.cpp en_prepos.cpp en_adjectives.cpp en_conjunctions.cpp"

echo
echo "Compiling base..."
echo
for file in $BASEFILES
do
	echo $file
	g++ $CFLAGS -c $file
done

echo
echo "Compiling parser..."
echo
for file in $PARSERFILES
do
	echo $file
	g++ $CFLAGS -c parser/$file
done

#echo
#echo "Compiling en_old..."
#echo
#for file in $EN_OLDFILES
#do
#	echo $file
#	g++ $CFLAGS -c en_old/$file
#done

#echo
#echo "Compiling de..."
#echo
#for file in $DEFILES
#do
#	echo $file
#	g++ $CFLAGS -c de/$file
#done

echo
echo "Compiling en..."
echo
for file in $ENFILES
do
	echo $file
	g++ $CFLAGS -c en/$file
done

echo
echo "Linking..."
echo
g++ -o lang *.o

echo "Clean Up..."
rm *.o
cp lang ../examples/
