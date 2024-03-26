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
const int maxn = 5e5 + 10;
int n, k, L, R;
int a[maxn];

int lg[maxn];
typedef pair<int,int> pii;
pii st[21][maxn];
pii query(int l,int r){
    // cerr << "r - l + 1 = " << r - l + 1 << endl;
    int k = lg[r - l + 1];
    return max(st[k][l],st[k][r - (1 << k) + 1]);
}

struct node{
    int lp, l, r;
    int pos, ans;
    node(){}
    node(int lp,int l,int r):lp(lp),l(l),r(r){
        pii tmp = query(l, r);
        pos = tmp.second;ans = tmp.first - a[lp];
    }
    friend bool operator < (node a,node b){return a.ans < b.ans;}
    friend bool operator > (node a,node b){return a.ans > b.ans;}
};
priority_queue<node,vector<node>,less<node> > que;

void main(){
    n = read() + 1;k = read(); L = read(); R = read();
    a[1] = 0;st[0][1] = make_pair(0,1); lg[0] = -1;lg[1] = 0;
    for(int i = 2;i <= n;i++)a[i] = read() + a[i - 1],lg[i] = lg[i >> 1] + 1,st[0][i] = make_pair(a[i],i);
    for(int j = 1;j <= 20;j++)for(int i = 1;i + (1 << j) - 1 <= n;i++)
        st[j][i] = max(st[j - 1][i],st[j - 1][i + (1 << j - 1)]);
    for(int i = 1;i + L <= n;i++){que.push(node(i,i + L,min(i + R,n)));}
    int ans = 0;
    while(k--){
        // cerr << "k = " << k << " que.size() = " << que.size() << endl;
        node tmp = que.top();que.pop();
        ans += tmp.ans;
        if(tmp.l < tmp.pos){que.push(node(tmp.lp,tmp.l,tmp.pos - 1));}
        if(tmp.pos < tmp.r){que.push(node(tmp.lp,tmp.pos + 1,tmp.r));}
    }
    printf("%lld\n",ans);
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