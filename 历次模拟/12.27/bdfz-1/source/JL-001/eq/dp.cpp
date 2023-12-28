#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int main(){
    while(1){
        system("./gen > in && ./eq <in > res && ./2 <in >ans");
        if(system("diff res ans -w -s")) cerr<<"Wa",exit(0);
    }
}