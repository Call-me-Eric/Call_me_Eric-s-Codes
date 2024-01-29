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
void write(int x){if(x / 10)write(x / 10);putchar('0' + (x % 10));}
const int maxn = 2e6 + 10;
int p[maxn], tot;
int k, n;
void upk(){p[tot + 1] = p[tot] + k;tot++;}
void upk1(){p[tot + 1] = p[tot] + k + 1;tot++;}
void downk(){p[tot + 1] = p[tot] - k;tot++;}
void main(){
    n = read(); k = read();
    if(k == 1){
        for(int i = 1;i <= n;i++){write(i);putchar(' ');}
        putchar('\n');return;
    }
    p[++tot] = 1;
    int f1 = 2 * k + 1, f2 = (k - 1) * f1 + 1,A = 0, B = 0;
    for(int i = 0;i <= (n - 1) / f1;i++)
        if((n - 1 - i * f1) % f2 == 0){A = i;B = (n - 1 - i * f1) / f2;}
    for(int i = 1;i <= A;i++){for(int j = 1;j <= k;j++){upk1();downk();}upk1();}
    for(int i = 1;i <= B;i++){
        for(int j = 1;j < k;j++){
            upk();upk1();
            for(int l = 1;l < j;l++){downk();upk1();}
            downk();
            for(int l = j;l < k;l++){downk();upk1();}
        }
        upk();
    }
    for(int i = 1;i <= n;i++){write(p[i]);putchar(' ');}
    putchar('\n');return;
    return;
}
};
bool edmemory;
signed main(){
    freopen("didi.in","r",stdin);
    freopen("didi.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}