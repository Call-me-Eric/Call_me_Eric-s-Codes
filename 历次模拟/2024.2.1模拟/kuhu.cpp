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
const int maxn = 3e5 + 10;
int n, m, num;
int fa[maxn], lg[maxn], siz[maxn];
int getf(int x){return x == fa[x] ? x : fa[x] = getf(fa[x]);}
int calc(int l,int r){
    for(int i = l;i <= r;i++){fa[i] = i;siz[i] = 0;}
    for(int i = l;i <= r;i++)
        for(int j = lg[i] + 1;(1 << j) - i <= r;j++)
            if((1 << j) - i >= l)fa[getf(i)] = getf((1 << j) - i);
    for(int i = l;i <= r;i++)siz[getf(i)]++;
    int ans = 0;
    for(int i = l;i <= r;i++)ans += (siz[i] + 1) / 2;
    return ans;
}
void main(){
    n = read(); m = read(); num = read();
    lg[0] = -1;for(int i = 1;i <= n;i++){lg[i] = lg[i >> 1] + 1;}
    while(m--){
        int l = read(), r = read();
        int ans = 0;
        if(l == 1){
            for(int i = 0;(1 << i) <= r;i++){
                int x = r / (1 << i);
                ans += (x - !(x & 1)) / 4 + 1;
            }
        }
        else{ans = calc(l,r);}
        printf("%d\n",ans);
    }
    if(!num){puts("0");}
    else{
        long long sum = 0;
        for(int l = 1;l <= n;l++){
            for(int r = l;r <= n;r++){
                sum = sum + 1ll * calc(l,r);
            }
        }
        printf("%lld\n",sum);
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
/*
20 3 1
1 20
10 20
1 10
*/