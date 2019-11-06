test: test-bsearch.o search.o
	g++ -o test test-bsearch.o search.o
test-bsearch.o: test-bsearch.cpp
	g++ -std=gnu++98 -pedantic -Wall -c test-bsearch.cpp
search.o: search.cpp
	g++ -std=gnu++98 -pedantic -Wall -c search.cpp
