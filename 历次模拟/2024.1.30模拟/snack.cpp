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
const int maxn = 20, maxs = (1 << maxn) + 10;
typedef long long ll;
unordered_map<ll,int> mp;
int L, Q;
char ch[maxs];
char opt[maxn + 10];

namespace Subtask1{inline ll id(char *s){
    ll val = 0;int n = strlen(s + 1);
    for(int i = 1;i <= n;i++){val = val * 3ll + 1ll * (s[i] == '0' ? 0 : (s[i] == '1' ? 1 : 2));}
    return val;
}
// vector<int> pos;
int pos[maxn + 10], l;
ll calc(char *s){
    // printf("pos.siz = %d : ",pos.size());puts(s + 1);
    int idd = id(s);
    if(mp.count(idd))return mp[idd];
    int ps = 0;ll res = 0;
    ps = pos[l];l--;
    s[ps] = '0';res += calc(s);
    s[ps] = '1';res += calc(s);
    s[ps] = '?';l++;
    return mp[idd] = res;
}
void solve(){
    for(int i = 0;i < (1 << L);i++){
        for(int j = 1;j <= L;j++){opt[L - j + 1] = ((i >> (j - 1)) & 1) + '0';}
        // opt[L + 1] = '\0';printf("i = %d,id = %d:%s\n",i,id(opt),opt + 1);
        mp[id(opt)] = (ch[i] - '0');
    }
    while(Q--){
        scanf("%s",opt + 1);l = 0;
        for(int i = 1;i <= L;i++){if(opt[i] == '?')pos[++l] = i;}
        // opt[L + 1] = '\0';
        printf("%lld\n",calc(opt));
    }
}
};
namespace Subtask2{
int val[3][(1 << maxn) + 1];//[0]:0->0,1->1,[1]:0->0,?->1,[2]:1->1,0->?
inline int popcount(int x){int res = 0;while(x){if(x & 1)res++;x >>= 1;}return res;}
inline int lowbit(int x){return x & (-x);}
void solve(){
    for(int i = 0;i < (1 << L);i++){
        val[0][i] = ch[i] - '0';
        val[1][i] += ch[i] - '0';
        val[2][i] += ch[i] - '0';
    }
    for(int j = 1;j < 3;j++){
        for(int i = 0;i < (1 << L);i++){
            for(int k = i;k;i = (k - 1) & i){
                val[j][i] += val[j][k];
            }
        }
    }
    while(Q--){
        scanf("%s",opt + 1);int c[3] = {0};
        for(int i = 1;i <= L;i++){
            opt[i] = (opt[i] == '0' ? 0 : (opt[i] == '1' ? 1 : 2));
            c[opt[i]]++;
        }
        int u = 0;if(c[1] < c[u])u = 1;if(c[2] < c[u])u = 2;
        vector<int> pos;pos.clear();
        for(int i = 1;i <= L;i++){if(opt[i] == u)pos.push_back(i);}
        if(u == 0){
            
        }
        if(u == 1){}
        if(u == 2){}
    }
}
};
void main(){
    L = read(); Q = read();
    scanf("%s",ch);
    if(L <= 13)Subtask1::solve();
    else Subtask2::solve();
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