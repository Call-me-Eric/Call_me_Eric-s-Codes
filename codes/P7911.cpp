#include<bits/stdc++.h>
using namespace std;
int n;
struct computer{
    int type;//type = 0:server type = 1:client
    string address;
    int a,b,c,d,e;
    int id;
    bool err;//err = 0:OK err = 1:ERR
    int check(){//0:ERR
        if(address[0] == 'S'){
            type = 0;
        }
        else {
            type = 1;
        }
        string tmp = address;
        tmp.erase(0,7);
        char t = tmp[0];
        bool book1 = 1;
        int i = 0;
        while(t <= '9' && t >= '0'){
            if(book1 && t == '0'){//eg:010
                err = 1;
                return 0;
            }
            a = a * 10 + (t - '0');
            i++;
            t = tmp[i];
        }
        if(a > 255){
            err = 1;
            return 0;
        }
    }
}a[10000];
int main(){
    scanf("%d",&n);
    getchar();
    string s;
    for(int i = 1;i <= n;i++){
        getline(cin,s);
        a[i].address = s;
        a[i].id = i;
        int t = a[i].check();
    }
    return 0;
}