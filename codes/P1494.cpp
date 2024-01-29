#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 5e4 + 10;
int n, m, len;
struct query{
    int l, r, id;
    query(int r = 0,int l = 0,int id = 0):l(l),r(r),id(id){}
    friend bool operator < (query a,query b){//奇偶卡常
        if(a.l / len != b.l / len) return a.l < b.l;
        return (a.l / len) & 1 ? a.r < b.r : a.r > b.r;
        //或者干脆按照lr排序
    }
}q[maxn];

int col[maxn];
int ans1[maxn], ans2[maxn];
int cnt[maxn], sum;
void add(int x){sum += cnt[x];cnt[x]++;}
void del(int x){cnt[x]--;sum -= cnt[x];}

int gcd(int x,int y){return y == 0 ? x : gcd(y,x % y);}

signed main(){
    n = read(); m = read();len = sqrt(n);
    for(int i = 1;i <= n;i++){col[i] = read();}
    for(int i = 1;i <= m;i++){q[i] = query(read(),read(),i);}
    sort(q + 1,q + 1 + m);
    for(int i = 1,l = 1, r = 0;i <= m;i++){
        if(q[i].l == q[i].r){
            ans1[q[i].id] = 0;ans2[q[i].id] = 1;
            continue;
        }
        while(l > q[i].l)add(col[--l]);
        while(r < q[i].r)add(col[++r]);
        while(l < q[i].l)del(col[l++]);
        while(r > q[i].r)del(col[r--]);
        ans1[q[i].id] = sum;
        ans2[q[i].id] = (r - l + 1) * (r - l) / 2;
    }
    for(int i = 1;i <= m;i++){
        if(ans1[i] != 0){
            int g = gcd(ans1[i],ans2[i]);
            ans1[i] /= g;ans2[i] /= g;
        }
        else ans2[i] = 1;
        printf("%lld/%lld\n",ans1[i],ans2[i]);
    }
    return 0;
}