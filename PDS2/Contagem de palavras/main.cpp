#include "WordCounter.hpp"
#include <iostream>


using namespace std;

int main() {

	WordCounter *wc = new WordCounter(100);
	string s;
	cin >> s;
	while (s != ".") {
		wc->addWord(s);
		cin >> s;
	}
	wc->print();

	return 0;
}