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
const int maxn = 1e5 + 10, mod = 998244353;
int n;
char s1[maxn], s2[maxn];
map<pair<int,int>,int> f[2];
int ans[maxn];
bool check(int sta1,int sta2,int len){
    if(len == 1){return sta1 % 10 == sta2 % 10;}
    int a[4] = {sta1 % 10,(sta1 % 100) / 10,(sta1 % 1000) / 100,(sta1 % 10000) / 1000};
    int b[4] = {sta2 % 10,(sta2 % 100) / 10,(sta2 % 1000) / 100,(sta2 % 10000) / 1000};
    sort(a,a + len);sort(b,b + len);
    for(int i = 0;i < len;i++)if(a[i] != b[i])return false;
    if(len == 2){if(a[0] != a[1] - 1 && a[0] != a[1] - 3)return false;}
    if(len == 4){if(a[0] != a[1] - 1 || a[1] != a[2] - 2 || a[2] != a[3] - 1)return false;}
    return true;
}
pair<int,int> calc(pair<int,int> sta,int x, int y){
    int sta1 = sta.first * 10 + x, sta2 = sta.second * 10 + y;
    int l = 1;while(sta1 >= l)l *= 10;
    if(l == 10000 && check(sta1,sta2,4)){return make_pair(0,0);}
    else if(l == 100 && check(sta1,sta2,2)){return make_pair(0,0);}
    else if(l == 10 && check(sta1,sta2,1)){return make_pair(0,0);}
    return make_pair(sta1,sta2);
}
bool removable(pair<int,int> x){
    int sta1 = x.first, sta2 = x.second;
    int l = 1;while(sta1 >= l)l *= 10;
    if(l == 10 || l == 100 || l == 1)return 1;
    if(l >= 10000)return 0;
    int a[10] = {sta1 % 10,(sta1 % 100) / 10,(sta1 % 1000) / 100,(sta1 % 10000) / 1000};
    int b[4] = {sta2 % 10,(sta2 % 100) / 10,(sta2 % 1000) / 100,(sta2 % 10000) / 1000};
    bool buc[10] = {0};int cnt = 0;
    buc[a[0]] = buc[a[1]] = buc[a[2]] = 1;
    buc[b[0]] = buc[b[1]] = buc[b[2]] = 1;
    for(int i = 1;i <= 9;i++)if(buc[i])a[cnt++] = i;
    if(cnt == 3)return 1;if(cnt != 4)return 0;
    if(a[0] != a[1] - 1 || a[1] != a[2] - 2 || a[2] != a[3] - 1)return 0;
    return 1;
}
void main(){
    n = read();scanf("%s",s1 + 1);scanf("%s",s2 + 1);
    f[0][make_pair(0,0)] = 1;
    for(int i = 1;i <= n;i++){
        f[i & 1].clear();
        int lj = (s1[i] == '?' ? 1 : (s1[i] - '0')),rj = (s1[i] == '?' ? 9 : (s1[i] - '0'));
        int lk = (s2[i] == '?' ? 1 : (s2[i] - '0')),rk = (s2[i] == '?' ? 9 : (s2[i] - '0'));
        for(int j = lj;j <= rj;j++)for(int k = lk;k <= rk;k++){
            for(auto x : f[(i - 1) & 1]){
                auto y = calc(x.first,j,k);
                if(removable(y)){f[i & 1][y] = (f[i & 1][y] + x.second) % mod;}
            }
        }
    }
    printf("%d\n",f[n & 1][make_pair(0,0)]);
    return;
}
};
bool edmemory;
signed main(){
    freopen("fairlady.in","r",stdin);
    freopen("fairlady.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
5
?5???
???2?
*/