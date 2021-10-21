#include <iostream>
#include <string>

using namespace std;

typedef unsigned char byte;

void function(const char *charArray){
    string str = charArray;
    cout << "string: " << str;
}


int main(){
    const char *charArray = "hello";
    function(charArray);

    return 0;
}
