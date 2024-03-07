#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch =getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
int n, m, c;
struct query{
    int l, r, id;
    query(int l = 0,int r = 0,int id = 0):l(l),r(r),id(id){}
    friend bool operator < (query a,query b){return a.r < b.r;}
}qu[maxn];
struct BIT{
    int c[maxn << 2];
    int sum(int x){int ans = 0;for(;x;x -= x & (-x))ans += c[x];return ans;}
    void add(int x,int t){for(;x <= n;x += x & (-x))c[x] += t;}
}tree;
int a[maxn], lst[maxn], lst2[maxn];
int ans[maxn];
signed main(){
    n = read(); c = read(); m = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 1;i <= m;i++){
        int l = read(), r = read();
        qu[i] = query(l,r,i);
    }
    sort(qu + 1,qu + 1 + m);int j = 1;
    for(int i = 1;i <= m;i++){
        for(;j <= qu[i].r;j++){
            if(!lst[a[j]])lst[a[j]] = j;
            else{
                if(!lst2[a[j]]){
                    lst2[a[j]] = j;
                    tree.add(lst[a[j]],1);
                }
                else{
                    tree.add(lst2[a[j]],1);
                    tree.add(lst[a[j]],-1);
                    lst[a[j]] = lst2[a[j]];
                    lst2[a[j]] = j;
                }
            }
        }
        ans[qu[i].id] = tree.sum(qu[i].r) - tree.sum(qu[i].l - 1);
    }
    for(int i = 1;i <= m;i++)printf("%d\n",ans[i]);
    return 0;
}