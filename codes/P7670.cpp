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
const int maxn = 30, maxk = (1 << 20) + 10;
int L, Q;
char ch[maxk];
char opt[maxn];
int val[3][maxk];
int ans;
int pos[3][maxn], cnt[3] = {0}, opt0 = 0, opt1 = 0;
void dfs0(int u,int f,int sta){
    if(u == cnt[0] + 1){ans += f * val[2][sta];return;}
    dfs0(u + 1, f,sta);
    dfs0(u + 1,-f,sta | (1 << pos[0][u]));
}
void dfs1(int u,int f,int sta){
    if(u == cnt[1] + 1){ans += f * val[1][sta];return;}
    dfs1(u + 1, f,sta | (1 << pos[1][u]));
    dfs1(u + 1,-f,sta);
}
void dfs2(int u,int f,int sta){
    if(u == cnt[2] + 1){ans += f * val[0][sta];return;}
    dfs2(u + 1, f,sta);
    dfs2(u + 1, f,sta | (1 << pos[2][u]));
}
void main(){
    L = read(); Q = read(); scanf("%s",ch);
    for(int i = 0;i < (1 << L);i++){val[0][i] = val[1][i] = val[2][i] = ch[i] - '0';}
    for(int i = 1;i < (1 << L);i <<= 1)
        for(int j = 0;j < (1 << L);j += (i << 1))
            for(int k = 0;k < i;k++){
                val[1][i + j + k] += val[1][    j + k];
                val[2][    j + k] += val[2][i + j + k];
            }
    while(Q--){
        scanf("%s",opt);reverse(opt,opt + L);
        cnt[0] = cnt[1] = cnt[2] = opt0 = opt1 = 0;
        for(int i = 0;i < L;i++){
            if(opt[i] == '0'){pos[0][++cnt[0]] = i;}
            if(opt[i] == '1'){pos[1][++cnt[1]] = i;opt1 |= (1 << i);}
            if(opt[i] == '?'){pos[2][++cnt[2]] = i;opt0 |= (1 << i);}
        }
        ans = 0;
        // dfs0(1,1,opt1);
        if(cnt[0] <= 6){dfs0(1,1,opt1);}
        else if(cnt[1] <= 6){dfs1(1,1,opt0);}
        else{dfs2(1,1,opt1);}
        printf("%d\n",ans);
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