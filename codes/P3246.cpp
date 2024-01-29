#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1 )+ (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, maxk = 1e3 + 10;
int n, m, len;
struct query{
    int l, r ,id;
    query(int r = 0,int l = 0,int id = 0):l(l),r(r),id(id){}
    friend bool operator < (query a,query b){
        if(a.l / len != b.l / len){return a.l < b.l;}
        else return (a.l / len) & 1 ? a.r > b.r : a.r < b.r;
    }
}q[maxn];
int a[maxn];
struct node{
    int val, id;
    node(int v = 0,int i = 0):val(v),id(i){}
    friend bool operator < (node a,node b){return a.val < b.val;}
};
stack<node> stk;
int fl[maxn], fr[maxn];
int f[maxk][maxk], pre[maxn], suf[maxn];
int lg[maxn], pw[24];
int RMQ[maxn][24];
int ask(int l,int r){
    int x = lg[r - l + 1];
    return a[RMQ[l][x]] < a[RMQ[r - pw[x] + 1][x]] ? RMQ[l][x] : RMQ[r - pw[x] + 1][x];
}
int ans[maxn], sum;
int L(int l,int r){int p = ask(l - 1,r);return a[p] * (r - p + 1) + fl[l - 1] - fl[p];}
int R(int l,int r){int p = ask(l,r + 1);return a[p] * (p - l + 1) + fr[r + 1] - fr[p];}
signed main(){
    n = read(); m = read();lg[0] = -1;pw[0] = 1;len = sqrt(n);

    for(int i = 1;i <= n;i++){lg[i] = lg[i >> 1] + 1;}
    for(int i = 1;i <= 23;i++){pw[i] = pw[i - 1] << 1;}
    
    a[0] = a[n + 1] = 0x3f3f3f3f;
    for(int i = 1;i <= n;i++){a[i] = read();RMQ[i][0] = i;}
    for(int i = 1;i <= m;i++){q[i] = query(read(),read(),i);}
    sort(q + 1,q + 1 + m);
    for(int j = 1;j <= lg[n];j++){
        for(int i = 1;i + pw[j - 1] - 1 <= n;i++){
            RMQ[i][j] = a[RMQ[i][j - 1]] < a[RMQ[i + pw[j - 1]][j - 1]] ? 
                          RMQ[i][j - 1]  :   RMQ[i + pw[j - 1]][j - 1];
        }
    }
    
    for(int i = 1;i <= n;i++){
        while(!stk.empty() && stk.top().val > a[i]){suf[stk.top().id] = i;stk.pop();}
        if(!stk.empty())pre[i] = stk.top().id; stk.push(node(a[i],i));
    }
    
    while(!stk.empty()){
        int u = stk.top().id;
        suf[u] = n + 1;stk.pop();
        if(stk.empty())break;
        pre[u] = stk.top().id;
    }
    for(int i = 1;i <= n;i++){fr[i] = a[i] * (i - pre[i]) + fr[pre[i]];}
    for(int i = n;i >= 1;i--){fl[i] = a[i] * (suf[i] - i) + fl[suf[i]];}
    
    int l = q[1].l, r = q[1].l - 1;
    for(int i = 1;i <= m;i++){
        while(l > q[i].l){sum += L(l,r);l--;}
        while(r < q[i].r){sum += R(l,r);r++;}
        while(l < q[i].l){l++;sum -= L(l,r);}
        while(r > q[i].r){r--;sum -= R(l,r);}
        ans[q[i].id] = sum;
    }
    for(int i = 1;i <= m;i++)printf("%lld\n",ans[i]);
    return 0;
}