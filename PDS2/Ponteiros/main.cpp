#include <iostream>

#define SIZE 5

using namespace std;

int main(){
    long value1=200000;
    long value2;

    long *long_ptr = nullptr;
    long_ptr = &value1;
    cout << *long_ptr <<  " ";
    value2 = *long_ptr;
    cout << value2 << " ";
    cout << &value1 <<  " ";
    cout << long_ptr << " " << bool(long_ptr==&value1) << " ";
    unsigned int values[] = {2,4,6,8,10};
    unsigned int *v_ptr = nullptr;
    for(int i=0;i<SIZE;i++){ cout << values[i] << " ";}
    v_ptr = values;
    v_ptr = &values[0];
    for(int i=0;i<SIZE;i++){ cout << *(v_ptr+i) <<  " ";}
    for(int i=0;i<SIZE;i++){ cout << *(values+i) <<  " ";}
    for(int i=0;i<SIZE;i++){ cout << v_ptr[i] <<  " ";}
    cout << values[4] <<  " ";
    cout << *(values+4) <<  " ";
    cout << v_ptr[4] <<  " ";
    cout << *(v_ptr+4) <<  " ";
    cout << (v_ptr+3) << " " << *(v_ptr+3) <<  " ";
    cout << (v_ptr) << " " << *(v_ptr) <<  " ";
    return 0;
}
