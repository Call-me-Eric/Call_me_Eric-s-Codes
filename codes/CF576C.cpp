#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
int len, n;
struct node{
    int l, r, id;
    node(int l = 0,int r = 0,int id = 0):l(l),r(r),id(id){}
    friend bool operator< (node a,node b){
        if(a.l / len != b.l / len)return a.l < b.l;
        return ((a.l / len) & 1) ? a.r < b.r : a.r > b.r;
    }
}a[maxn];
signed main(){
    len = sqrt(n = read());
    for(int i = 1;i <= n;i++){
        int x = read(), y  =read();
        a[i] = node(x,y,i);
    }
    sort(a + 1,a + 1 + n);
    for(int i = 1;i <= n;i++)printf("%d ",a[i].id);
    puts("");
    return 0;
}