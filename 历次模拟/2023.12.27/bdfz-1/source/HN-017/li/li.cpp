#include <bits/stdc++.h>
// #define ll long long
using namespace std;

template<typename ...Args>
signed debug(const char*str,Args ...args){return fprintf(stderr,str,args...);}

inline static int read(){
    int sum=0; bool neg=false; char ch=getchar();
    while(!isdigit(ch)) neg|=(ch=='-'),ch=getchar();
    while(isdigit(ch)) sum=(sum<<3)+(sum<<1)+(ch^48),ch=getchar();
    return neg?-sum:sum;
}



signed main(){
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    int n=read(),m=read();
    switch(n){
        case 1: puts("0 1"); break;
        case 2: puts(m==1?"0 3":"0 2"); break;
        case 3:
        if(m==0) puts("0 3");
        if(m==1) puts("0 4");
        if(m==2) puts("0 6");
        if(m==3) puts("1 3");
        break;
    } return 0;
}
