#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f= -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x=  (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, V;
struct node{
    int pos, times;
    node(int times = 0,int pos = 0):pos(pos),times(times){}
    friend bool operator < (node a,node b){return a.times != b.times ? a.times < b.times : a.pos < b.pos;}
}a[maxn];

struct node1{
    int x, y;
    node1(int x = 0,int y = 0):x(x),y(y){}
    friend bool operator < (node1 a,node1 b){return a.x != b.x ? a.x < b.x : a.y < b.y;}
}b[maxn],tmp[maxn];

int x[maxn], y[maxn];
int que[maxn], r;

signed main(){
    n = read();
    for(int i = 1;i <= n;i++)a[i] = node(read(),read());
    V = read();
    int cnt = 0;
    for(int i = 1;i <= n;i++){
        b[i] = node1(-a[i].pos + V * a[i].times,a[i].pos + V * a[i].times);
        x[i] = -a[i].pos + V * a[i].times; y[i] = a[i].pos + V * a[i].times;
        if(b[i].x > 0 && b[i].y > 0){tmp[++cnt] = b[i];}
    }
    sort(x + 1,x + 1 + n);sort(y + 1,y + 1 + n);

    for(int i = 1;i <= cnt;i++){tmp[i] = node1(lower_bound(x + 1,x + 1 + n,tmp[i].x) - x,lower_bound(y + 1,y + 1 + n,tmp[i].y) - y);}
    sort(tmp + 1,tmp + 1 + cnt);
    int ans1 = 0;r = 0;
    que[0] = -1;que[++r] = 0x3f3f3f3f;
    for(int i = 1;i <= cnt;i++){
        int pos = upper_bound(que,que + r + 1,tmp[i].y) - que;
        if(que[pos] > tmp[i].y)que[pos] = tmp[i].y;
        if(pos >= r){que[++r] = 0x3f3f3f3f;}
    }
    ans1 = r - 1;

    for(int i = 1;i <= n;i++){b[i] = node1(lower_bound(x + 1,x + 1 + n,b[i].x) - x,lower_bound(y + 1,y + 1 + n,b[i].y) - y);}
    sort(b + 1,b + 1 + n);
    int ans = 0;r = 0;
    memset(que,0,sizeof(que));
    que[0] = -1;que[++r] = 0x3f3f3f3f;
    for(int i = 1;i <= n;i++){
        int pos = upper_bound(que,que + r + 1,b[i].y) - que;
        if(que[pos] > b[i].y)que[pos] = b[i].y;
        if(pos >= r){que[++r] = 0x3f3f3f3f;}
    }
    ans = r - 1;
    // for(int i = 1;i <= n;i++)printf("%d %d\n",b[i].x,b[i].y);
    printf("%d %d\n",ans1,ans);
    return 0;
}