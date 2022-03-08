#ifndef WORDCOUNTER
#define WORDCOUNTER

#include "Word.hpp"
#include <iostream>
#include <string>
#include <map>


using namespace std;

class WordCounter {

public:

	Word *words;
	int size = 0;

	WordCounter(int num_words);
	~WordCounter();
	void addWord(string w);
	void print();
};

#endif