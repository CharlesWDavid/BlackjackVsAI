game: main.o blackjack.o
	g++ -std=c++11 main.o blackjack.o -o test

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

blackjack.o: blackjack.cpp
	g++ -std=c++11 -c blackjack.cpp

	