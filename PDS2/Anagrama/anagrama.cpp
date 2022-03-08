#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

bool anagram(string s0, string s1)
{
    string palavraUm=s0;
    string palavraDois=s1;
    sort(palavraUm.begin(),palavraUm.end());
    sort(palavraDois.begin(), palavraDois.end());
    
  if(palavraUm == palavraDois)
        return true;
    return false;

}

int main(int argc, char** argv) {
  string s0, s1;
  cin >> s0;
  cin >> s1;
  cout << anagram(s0, s1) << endl;
  return 0;
}