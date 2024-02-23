#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
int n, m;
int s[maxn], t[maxn], a[maxn], b[maxn], p[maxn], q[maxn];
int x[maxn], y[maxn];
struct node{
    int x, y, val, opt;
    node(int x = 0,int y = 0,int val = 0,int opt = 0):x(x),y(y),val(val),opt(opt){}
};
vector<node> vec;
namespace Subtask1{
    void solve(){
        for(int i = 1;i <= n;i++)p[i] += p[i - 1];
        for(int i = 1;i <= m;i++)q[i] += q[i - 1];
        int ans = 0;
        for(int i = 1;i <= n;i++){ans = max(ans,p[i] + q[x[i]]);}
        printf("%lld\n",ans);return;
    }
};
namespace BF{
    const int maxm = 2e3 + 10;
int lft[maxm][maxm], dwn[maxm][maxm];
int f[maxm][maxm];
bool book[maxm][maxm];//0=up,1=left
void solve(){
    for(auto i : vec){
        // printf("(%lld, %lld) ,val = %lld, opt = %lld\n",i.x,i.y,i.val,i.opt);
        if(i.opt == 0){
            for(int j = 0;j <= i.y;j++){
                lft[i.x][j] += i.val;
            }
        }
        else{
            for(int j = 0;j <= i.x;j++){
                dwn[j][i.y] += i.val;
            }
        }
    }
    memset(f,-0x3f,sizeof(f));f[0][0] = 0;
    for(int i = 0;i <= n;i++){
        for(int j = 0;j <= m;j++){
            if(i > 0){f[i][j] = f[i - 1][j] + lft[i][j];}
            if(j > 0 && f[i][j] < f[i][j - 1] + dwn[i][j]){f[i][j] = f[i][j - 1] + dwn[i][j];book[i][j] = 1;}
        }
    }
    // for(int i = n;i + 1;i--){
    //     for(int j = 0;j <= m;j++)
    //         printf("% .5lld ",dwn[i][j]);
    //     puts("");
    // }
    // puts("");
    // for(int i = n;i + 1;i--){
    //     for(int j = 0;j <= m;j++)
    //         printf("% .5lld ",lft[i][j]);
    //     puts("");
    // }
    // puts("");
    // for(int i = n;i + 1;i--){
    //     for(int j = 0;j <= m;j++)
    //         printf("% .5lld ",f[i][j]);
    //     puts("");
    // }
    // puts("");
    // for(int i = n;i + 1;i--){
    //     for(int j = 0;j <= m;j++)
    //         printf("%d ",book[i][j]);
    //     puts("");
    // }
    // puts("");
    printf("%lld\n",f[n][m]);
}
};
void main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++){a[i] = read() + a[i - 1];s[i] = read();p[i] = read();}
    for(int i = 1;i <= m;i++){b[i] = read() + b[i - 1];t[i] = read();q[i] = read();}
    for(int i = 1;i <= n;i++){
        if(a[i] > s[i])continue;
        int u = upper_bound(b,b + 1 + m,s[i] - a[i]) - b - 1;
        x[i] = u;vec.push_back(node(i,u,p[i],0));
    }
    for(int i = 1;i <= m;i++){
        if(b[i] > t[i])continue;
        int u = upper_bound(a,a + 1 + n,t[i] - b[i]) - a - 1;
        y[i] = u;vec.push_back(node(u,i,q[i],1));
    }
    bool flag = s[1] == t[1];
    for(int i = 2;i <= n;i++)flag &= s[i] == s[i - 1];
    for(int i = 2;i <= m;i++)flag &= t[i] == t[i - 1];
    if(flag){Subtask1::solve();return;}
    BF::solve();
    return;
}
};
bool edmemory;
signed main(){
    freopen("chef.in","r",stdin);
    freopen("chef.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
4 3
2 1 1
3 8 1
2 13 1
1 13 1
3 6 1
2 11 1
2 15 1

*/