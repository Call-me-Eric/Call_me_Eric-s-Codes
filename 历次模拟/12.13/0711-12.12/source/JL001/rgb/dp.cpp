#include<iostream>
using namespace std;
int main(){
    int tot=0;
    for(int i=1;i<=400;i++){
        cerr<<(++tot)<<endl;
        system("./gen > in ");
        if(system("./1 < in")) cerr<<"Wa",exit(0);
    }
}