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
const int maxn = 5e5 + 10;
int n, m;
struct node{
    int x, y;int typ, id, ans, f;
    node(int x = 0,int y = 0,int typ = 0,int id = 0,int ans = 0,int f = 0
    ):x(x),y(y),typ(typ),id(id),ans(ans),f(f){}
    friend bool operator < (node a,node b){return a.x == b.x ? (a.y == b.y ? (a.typ < b.typ) : a.y < b.y) : a.x < b.x;}
}x[maxn * 5], vec[maxn * 5];
int ans[maxn];
void cdq(int l,int r){
    if(l == r)return;
    int mid = l + r >> 1;
    cdq(l,mid);cdq(mid + 1,r);
    int lp = l, rp = mid + 1, ans = 0, pos = 0;
    while(lp <= mid || rp <= r){
        if(rp > r || (lp <= mid && x[lp].y <= x[rp].y)){
            if(x[lp].typ == 1)ans++;
            vec[pos++] = x[lp];lp++;
        }
        else{
            if(x[rp].typ == 2)x[rp].ans += ans;
            vec[pos++] = x[rp];rp++;
        }
    }
    for(int i = 0;i < r - l + 1;i++)x[i + l] = vec[i];
}
void main(){
    n = read();m = read();int cnt = 0;
    for(int i = 1;i <= n;i++){
        int a = read(), y = read();
        x[++cnt] = node(a,y,1,0,0,0);
    }
    for(int i = 1;i <= m;i++){
        int a = read(), b = read(), c = read(), d = read();
        x[++cnt] = node(c,d,2,i,0,1);
        x[++cnt] = node(c,b - 1,2,i,0,-1);
        x[++cnt] = node(a - 1,d,2,i,0,-1);
        x[++cnt] = node(a - 1,b - 1,2,i,0,1);
    }
    sort(x + 1,x + 1 + cnt);
    cdq(1,cnt);
    for(int i = 1;i <= cnt;i++){ans[x[i].id] += x[i].ans * x[i].f;}
    for(int i = 1;i <= m;i++)printf("%d\n",ans[i]);
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