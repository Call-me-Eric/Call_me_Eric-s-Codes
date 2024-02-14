#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
void main(){
    int T = read();
    while(T--){
        int S = read();
        if(S == 2 || (S < 9 && (S & 1))){puts("No");continue;}
        puts("Yes");
        if((S & 1) == 0){printf("0 0 2 0 %d %d\n",S / 2,S / 2);}
        else{printf("0 0 3 1 %d %d\n",(S - 9) / 2 + 3,(S - 9) / 2 + 3 + 1);}
    }
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}