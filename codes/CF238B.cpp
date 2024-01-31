#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, h;
struct node{
    int val, id;
    node(int val = 0,int id = 0):val(val),id(id){}
    friend bool operator < (node a,node b){return a.val < b.val;}
}a[maxn];
bool cmp(node a,node b){return a.id < b.id;}
signed main(){
    n = read();h = read();
    for(int i = 1;i <= n;i++)a[i] = node(read(),i);
    sort(a + 1,a + 1 + n);
    int val1 = max(h + a[n].val + a[1].val,a[n].val + a[n - 1].val) - min(a[1].val + a[2].val + h,a[2].val + a[3].val);
    int val2 = a[n].val + a[n - 1].val - a[1].val - a[2].val;
    if(val1 < val2){a[1].val = -1;}
    sort(a + 1,a + 1 + n,cmp);
    printf("%d\n",min(val1,val2));
    for(int i = 1;i <= n;i++){
        putchar((a[i].val == -1) ? '1' : '2');
        putchar(' ');
    }
    puts("");
    return 0;
}