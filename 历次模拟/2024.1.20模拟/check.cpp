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
    freopen("didi.in","r",stdin);
    int n = read(), k = read();
    freopen("didi.out","r",stdin);
    int lst = -1;
    for(int i = 1;i <= n;i++){
        int u = read();
        if(lst != -1){
            if(abs(u - lst) != k && abs(u - lst) != k + 1){
                printf("Wrong on %d:pre = %d,now = %d\n",i,lst,u);
            }
        }
        if(u > n || u < 1)printf("out of range on %d: now = %d\n",i,u);
        lst = u;
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