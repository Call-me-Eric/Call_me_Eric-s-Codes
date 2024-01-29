#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, t, x[maxn];
struct node{
    int pos, val;
    node(int pos = 0,int val = 0):pos(pos),val(val){}
    friend bool operator< ( node a,node b){return a.pos < b.pos;}
}a[maxn];
signed main(){
    n = read(); t = read();
    for(int i = 1;i <= n;i++)x[i] = read();
    for(int i = 1;i <= n;i++)a[i] = node(x[i],read());
    sort(a + 1,a + 1 + n);
    
    return 0;
}