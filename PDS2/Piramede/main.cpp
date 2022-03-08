#include <iostream>

using namespace std;

int main(){

    int num;
    char aux = '*';
    cin >> num;
    for(int i = 0; i<num;i++){
        for(int j =0;j<=i;j++){
             cout << aux ;
        }
        cout << endl;
    }
    for(int i = --num; i>=0;i--){
        for(int j =0;j<i;j++){
             cout << aux ;
        }
        cout << endl;
    }

    return 0;
}
