#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10, maxk = 4e4 + 10;
int n, m, len;
int a[maxn], tmp[maxn];
struct query{
    int l, r, id, times;
    query(int l = 0,int r = 0,int id = 0,int times = 0):l(l),r(r),id(id),times(times){}
    friend bool operator < (query a,query b){
        if(a.l / len != b.l / len)return a.l < b.l;
        if(a.r / len != b.r / len)return a.r < b.r;
        return a.times < b.times;
    }
}q[maxn];
int upd[maxn][3];//upd[i] : [0] = pos, [1] = initial col, [2] = new col
int tot1, ans[maxn];

int buc[(int)(1e6) + 10], sum;
void del(int x){buc[x]--;if(!buc[x])sum--;}
void add(int x){if(!buc[x])sum++;buc[x]++;}

signed main(){
    n = read(); m = read(); len = pow(n,2.0 / 3.0);
    for(int i = 1;i <= n;i++)tmp[i] = a[i] = read();
    int u, v, times = 0; char opt[10];
    for(int i = 1;i <= m;i++){
        scanf(" %s%d%d",opt,&u,&v);
        if(opt[0] == 'R'){
            times++;
            upd[times][0] = u;
            upd[times][1] = tmp[u];
            upd[times][2] = v;
            tmp[u] = v;
        }
        else{tot1++;q[tot1] = query(u,v,tot1,times);}
    }

    sort(q + 1,q + 1 + tot1);
    int l = 1, r = 0;times = 0;
    for(int i = 1;i <= tot1;i++){
        while(l > q[i].l)add(a[--l]);
        while(l < q[i].l)del(a[l++]);
        while(r > q[i].r)del(a[r--]);
        while(r < q[i].r)add(a[++r]);
        while(times < q[i].times){
            times++;
            if(l <= upd[times][0] && upd[times][0] <= r){
                del(upd[times][1]); add(upd[times][2]);
            }
            a[upd[times][0]] = upd[times][2];
        }
        while(times > q[i].times){
            if(l <= upd[times][0] && upd[times][0] <= r){
                del(upd[times][2]); add(upd[times][1]);
            }
            a[upd[times][0]] = upd[times][1];
            times--;
        }
        ans[q[i].id] = sum;
    }
    for(int i = 1;i <= tot1;i++)printf("%d\n",ans[i]);
    return 0;
}