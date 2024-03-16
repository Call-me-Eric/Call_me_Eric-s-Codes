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
const int maxn = 1e5 + 10;
int n, q;
int a[maxn], lg[maxn];
pair<int,int> st[21][21][maxn];
pair<int,int> qry(int x,int l,int r){
    int k = lg[r - l + 1];
    return make_pair(min(st[x][k][l].first,st[x][k][r - (1 << k) + 1].first)
                    ,max(st[x][k][l].second,st[x][k][r - (1 << k) + 1].second));
}
void main(){
    n = read(); q = read();lg[0] = -1;
    for(int i = 1;i <= n;i++){a[i] = read();st[0][0][i] = make_pair(a[i],a[i]);lg[i] = lg[i >> 1] + 1;}
    for(int j = 1;j <= 20;j++){
        for(int i = 1;i + (1 << j) - 1 <= n;i++){
            st[0][j][i] = make_pair(
                 min(st[0][j - 1][i].first,st[0][j - 1][i + (1 << j - 1)].first)
                ,max(st[0][j - 1][i].second,st[0][j - 1][i + (1 << j - 1)].second));
        }
    }
    for(int i = 1;i <= 20;i++)for(int j = 0;j <= 20;j++)
        for(int k = 1;k + (1 << j) - 1 <= n;k++)
            st[i][j][k] = qry(i - 1,st[i - 1][j][k].first,st[i - 1][j][k].second);
    for(int i = 1;i <= q;i++){
        int l = read(), r = read(), res = 1;
        if(l == 1 && r == n){puts("0");continue;}
        for(int j = 20;j + 1;j--){
            auto tmp = qry(j,l,r);
            if(tmp.first > 1 || tmp.second < n){
                res += (1 << j); l = tmp.first, r = tmp.second;
            }
        }
        auto tmp = qry(0,l,r);
        l = tmp.first, r = tmp.second;
        if(l > 1 || r < n){puts("-1");continue;}
        printf("%d\n",res);
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