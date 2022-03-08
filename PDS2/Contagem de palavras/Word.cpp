#include "Word.hpp"

Word::Word () {
	this->word = "";
	this->count = 0;
}
Word::Word (string word) {
	this->word = word;
	this->count = 0;
}
void Word::incrementFreq () {
	count += 1;
}
