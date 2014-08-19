cd source
g++ -Wall -c cmdparse.cpp
g++ -Wall -c fileparse.cpp
g++ -Wall -c main.cpp
g++ -Wall -c Language.cpp
g++ -Wall -c general.cpp

g++ -Wall -c parser/parser.cpp
g++ -Wall -c parser/parser_io.cpp
g++ -Wall -c parser/parse_noun.cpp

g++ -Wall -c en/en.cpp
g++ -Wall -c en/en_nouns.cpp
g++ -Wall -c en/en_articles.cpp
g++ -Wall -c en/en_verbs.cpp
g++ -Wall -c en/en_adjectives.cpp
g++ -Wall -c en/en_adverbs.cpp
g++ -Wall -c en/en_prepos.cpp
g++ -Wall -c en/en_conjunctions.cpp
g++ -Wall -c en/en_general.cpp

g++ -Wall -c de/de.cpp
g++ -Wall -c de/de_articles.cpp
g++ -Wall -c de/de_nouns.cpp
g++ -Wall -c de/de_verbs.cpp
g++ -Wall -c de/de_prepos.cpp
g++ -Wall -c de/de_adjectives.cpp
g++ -Wall -c de/de_conjunctions.cpp
g++ -Wall -c de/de_general.cpp

g++ -o lang *.o
rm *.o
cp lang ../examples/
