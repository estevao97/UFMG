#ifndef WORD
#define WORD

#include <string>
#include<iostream>

using namespace std;

class Word
{

public:
	string word;
	int count;

	Word();
	Word(string);
	void incrementFreq();
};

#endif
