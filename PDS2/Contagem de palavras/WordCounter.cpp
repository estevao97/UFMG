#include "Word.hpp"
#include "WordCounter.hpp"
#include <iostream>

std::map<std::string,int> lista;

WordCounter::WordCounter(int num_words) {

	words = new Word[num_words];
}
void WordCounter::addWord(string w) {
	Word aux = Word(w);
	for (int i =0;i<size;++i) {
		if (words[i].word==aux.word) {
			words[i].incrementFreq();
			return;
		}
	}
	aux.incrementFreq();
	words[size] = aux;
	size++;
}

void WordCounter::print(){
	for (int i=0; i<size; ++i) {
		lista.insert(std::pair<std::string,int>(words[i].word,words[i].count));	
	}
	for (auto it=lista.begin();it!=lista.end(); ++it) {
		std::cout<<it->first<<" "<<it->second<<std::endl;	
	}
	
}

WordCounter:: ~WordCounter() {
	delete words;
}
