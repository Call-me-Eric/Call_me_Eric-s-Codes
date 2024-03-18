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
const int maxn = 1e5 + 10;
struct node{
    int x, y;
    node(int x = 0,int y = 0):x(x),y(y){}
    friend bool operator < (node a,node b){return a.y != b.y ? a.y < b.y : a.x < b.x;}
    friend node operator + (node a,node b){return node(a.x + b.x,a.y + b.y);}
    friend node operator - (node a,node b){return node(a.x - b.x,a.y - b.y);}
    friend int operator * (node a,node b){return b.y * a.x - a.y * b.x;}
    int len(){return x * x + y * y;}
}a1[maxn],a2[maxn];
int n, m, q;
struct mystk{
    int stk[maxn << 1], tp;
    inline int top(){return stk[tp];}
    inline void push(int x){stk[++tp] = x;}
    inline void pop(){tp--;}
    inline int size(){return tp;}
    inline void clear(){tp = 0;}
    inline int second(){return stk[tp - 1];}
    int operator [](int x){return stk[x];}
}stk;
bool cmp(node a,node b){return a * b == 0 ? a.len() < b.len() : a * b > 0;}
void convex(node *a,int &n){
    sort(a + 1,a + 1 + n);stk.clear();
    node base = a[1];stk.push(1);
    for(int i = 1;i <= n;i++)a[i] = a[i] - base;
    sort(a + 2,a + 1 + n,cmp);
    for(int i = 2;i <= n;stk.push(i),i++)
        while(stk.size() >= 2 && (a[i] - a[stk.second()]) * (a[stk.top()] - a[stk.second()]) >= 0){stk.pop();}
    for(int i = 1;i <= stk.size();i++)a[i] = a[stk[i]] + base;
    n = stk.size();a[n + 1] = a[1];
}
node s1[maxn], s2[maxn], ans[maxn];int tot = 0;
void Minkowski(node *a,int n,node *b,int m,node *A,int &tot){
    for(int i = 1;i < n;i++)s1[i] = a[i + 1] - a[i];s1[n] = a[1] - a[n];
    for(int i = 1;i < m;i++)s2[i] = b[i + 1] - b[i];s2[m] = b[1] - b[m];
    A[++tot] = a[1] + b[1];int l = 1, r = 1;
    while(l <= n && r <= m){++tot;A[tot] = A[tot - 1] + (s1[l] * s2[r] >= 0 ? s1[l++] : s2[r++]);}
    while(l <= n){++tot;A[tot] = A[tot - 1] + s1[l++];}while(r <= m){++tot;A[tot] = A[tot - 1] + s2[r++];}
}
bool in(node a){
    if(a * ans[1] > 0 || ans[tot] * a > 0){return 0;}
    int pos = lower_bound(ans + 1,ans + 1 + tot,a,cmp) - ans - 1;
    return (a - ans[pos]) * (ans[pos % tot + 1] - ans[pos]) <= 0;
}
void main(){
    n = read(); m = read(); q = read();int u, v;
    for(int i = 1;i <= n;i++){u =  read(),v =  read();a1[i] = node(u,v);}
    for(int i = 1;i <= m;i++){u = -read(),v = -read();a2[i] = node(u,v);}
    convex(a1,n); convex(a2,m);
    // puts("afsdl;ajfldjas;lfasjdflasjl;fjasl;fj");
    Minkowski(a1,n,a2,m,ans,tot);
    convex(ans,tot);
    node base = ans[1];for(int i = tot;i;i--){ans[i] = ans[i] - base;}
    while(q--){
        u = read(), v = read();
        printf("%d\n",in(node(u,v) - base));
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