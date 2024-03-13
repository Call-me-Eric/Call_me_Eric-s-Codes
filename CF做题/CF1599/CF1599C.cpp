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
const int maxn = 1e3 + 10;
int n;double p;
void main(){
    scanf("%d%lf",&n,&p);
    for(int i = 0;i <= n;i++){
        double ans = 0;
        if(i >= 1 && n - i >= 2)ans += 3.0 * (i) * (n - i) * (n - i - 1) * 0.5;
        if(i >= 2 && n - i >= 1)ans += 3.0 * (i) * (i - 1) * (n - i) * 1;
        if(i >= 3 && n - i >= 0)ans += (i) * (i - 1) * (i - 2) * 1;
        // printf("i = %d, ans = %lf\n",i,ans / n / (n - 1) / (n - 2));
        if(ans >= p * (n) * (n - 1) * (n - 2)){
            printf("%d\n",i);break;
        }
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