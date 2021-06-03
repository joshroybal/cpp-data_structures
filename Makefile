CXX = g++
CFLAGS = -std=c++98 -pedantic -Werror -O2 -g
LFLAGS = -Werror

all: a.out words

a.out: main.o random.o
	$(CXX) -o $@ $^ $(LFLAGS)

words: words.o
	$(CXX) -o $@ $^ $(LFLAGS)

main.o: main.cpp random.hpp linkedlist.hpp bst.hpp avl.hpp
	$(CXX) -c $< $(CFLAGS)

words.o: words.cpp bst.hpp avl.hpp
	$(CXX) -c $< $(CFLAGS)

random.o: random.cpp random.hpp
	$(CXX) -c $< $(CFLAGS)

clean:
	$(RM) a.out *.o
