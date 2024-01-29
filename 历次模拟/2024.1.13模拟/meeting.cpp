#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e3 + 10, maxk = 11;
int n, k;
struct node{
    int l, r, val;
    node(int l = 0,int r = 0,int val = 0):l(l),r(r),val(val){}
    friend bool operator < (node a,node b){return a.l != b.l ? a.l < b.l : a.r < b.r;}
}a[maxn];
bool e[maxn][maxn];
bool book[maxn];
int fa[maxn], siz[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
void solve(){
    n = read(); k = read();int total = 0;
    for(int i = 1;i <= n;i++){
        int u = read() , v = read();
        a[i] = node(u, v, read());
        total += a[i].val;
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            node x = a[i], y = a[j];
            if(x.l > y.l)swap(x,y);
            e[i][j] = (y.l <= x.r);
            // printf("(%d[%d,%d],%d[%d,%d]) = %d,\n",i,a[i].l,a[i].r,j,a[j].l,a[j].r,e[i][j]);
        }
    }
    if(n <= 10){
        int ans = 0;
        for(int st = 0;st < (1 << n);st++){
            int sum = 0;bool chk = true;
            for(int i = 0;i < n;i++)
                if((st >> i) & 1){i++;fa[i] = i;siz[i] = 1;book[i] = 1;sum += a[i].val;i--;}
                else book[i + 1] = 0;
            for(int i = 1;i <= n && chk;i++){
                if(book[i]){
                    for(int j = 1;j < i && chk;j++){
                        if(book[j] && e[i][j]){
                            int fx = getf(i), fy = getf(j);
                            if(fx != fy){
                                fa[fx] = fy;siz[fy] += siz[fx];
                                if(siz[fy] > k){chk = false;break;}
                            }
                        }
                    }
                }
            }
            ans = max(ans,sum * chk);
            // printf("%d %d %d\n",st,sum,chk);
            // for(int i = 1;i <= n;i++){
            //     if(book[i]){
            //         printf("i = %d, fa = %d\n",i,getf(i));
            //     }
            // }
        }
        printf("%d\n",total - ans);
    }
    else{

    }
}
signed main(){
    freopen("meeting.in","r",stdin);
    freopen("meeting.out","w",stdout);
    int T = read();
    while(T--){solve();}
    return 0;
}