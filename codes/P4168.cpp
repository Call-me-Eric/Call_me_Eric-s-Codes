#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 4e4 + 10, maxm = 5e4 + 10, maxk = 220;
int n, m, L, len;
struct node{int d, id, col;}a[maxn];
struct node1{int val, cnt;}p[maxk][maxk];
struct cmp{bool operator ()(node x,node b){return x.d < b.d;}};
struct cmp2{bool operator()(node a,node b){return a.id < b.id;}};
int f[maxk][maxk];
int buc[maxn], sum[maxk][maxn], book[maxn];
int inv[maxn];//inv[i] -> 真实颜色 ; i -> 离散化颜色
int calc(int x){int res = x / L;if(x % L)res++;return res;}

signed main(){
    #ifndef ONLINE_JUDGE
    freopen("P4168_1.in","r",stdin);
    freopen("P4168.out","w",stdout);
    #endif
    n = read(); m = read(); L = sqrt(n);
    len = (n + L - 1) / L;
    for(int i = 1;i <= n;i++){a[i].d = read(); a[i].id = i;}

    sort(a + 1,a + 1 + n, cmp()); a[0].d = -1;
    for(int i = 1;i <= n;i++){
        a[i].col = a[i - 1].col;
        if(a[i].d != a[i - 1].d)a[i].col++;//离散化
        inv[a[i].col] = a[i].d;
    }

    sort(a + 1,a + 1 + n,cmp2());

    for(int i = 1;i <= len;i++){
        memset(buc,0,sizeof(buc));node1 tmp;tmp.cnt = tmp.val = 0;
        for(int j = i;j <= len;j++){
            for(int k = (j - 1) * L + 1;k <= min(n,L * j);k++){
                buc[a[k].col]++;
                if(buc[a[k].col] > tmp.cnt){
                    tmp.cnt = buc[a[k].col];
                    tmp.val = a[k].col;
                }
                else if(buc[a[k].col] == tmp.cnt){
                    tmp.val = min(a[k].col,tmp.val);
                }
            }
            p[i][j] = tmp;
        }
    }
    for(int i = 1;i <= len;i++){
        for(int j = 1;j <= n;j++){sum[i][a[j].col] = sum[i - 1][a[j].col];}
        for(int j = (i - 1) * L + 1;j <= min(n,i * L);j++){sum[i][a[j].col]++;}
    }

    int lastans = 0;
    for(int i = 1;i <= m;i++){
        int l = read(), r = read();
        l = (l + lastans - 1) % n + 1;
        r = (r + lastans - 1) % n + 1;
        if(l > r)swap(l,r);
        int posl = calc(l), posr = calc(r);
        if(posr - posl <= 2){
            int ans = 0;
            for(int j = l;j <= r;j++)buc[a[j].col] = 0;
            for(int j = l;j <= r;j++){
                buc[a[j].col]++;
                if(buc[a[j].col] > buc[ans]){ans = a[j].col;}
                else if(buc[a[j].col] == buc[ans])ans = min(ans,a[j].col);
            }
            lastans = ans;
        }
        else{
            int ans = p[posl + 1][posr - 1].val;buc[ans] = 0;book[ans] = 0;
            for(int j = l;j <= min(n,posl * L);j++){buc[a[j].col] = 0;book[a[j].col] = 0;}
            for(int j = (posr - 1) * L + 1;j <= r;j++){buc[a[j].col] = 0;book[a[j].col] = 0;}
            for(int j = l;j <= min(n,posl * L);j++){buc[a[j].col]++;}
            for(int j = (posr - 1) * L + 1;j <= r;j++){buc[a[j].col]++;}
            node1 tmp;tmp.cnt = tmp.val = 0;
            for(int j = l;j <= min(posl * L,n);j++){
                if(!book[a[j].col]){
                    book[a[j].col] = true;
                    int cnt = buc[a[j].col] + sum[posr - 1][a[j].col] - sum[posl][a[j].col];
                    if(tmp.cnt < cnt){tmp.cnt = cnt;tmp.val = a[j].col;}
                    else if(tmp.cnt == cnt){tmp.val = min(tmp.val,a[j].col);}
                }
            }
            for(int j = (posr - 1) * L + 1;j <= r;j++){
                if(!book[a[j].col]){
                    book[a[j].col] = true;
                    int cnt = buc[a[j].col] + sum[posr - 1][a[j].col] - sum[posl][a[j].col];
                    if(tmp.cnt < cnt){tmp.cnt = cnt;tmp.val = a[j].col;}
                    else if(tmp.cnt == cnt){tmp.val = min(tmp.val,a[j].col);}
                }
            }
            if(tmp.cnt > buc[ans] + p[posl + 1][posr - 1].cnt)ans = tmp.val;
            else if(tmp.cnt == buc[ans] + p[posl + 1][posr - 1].cnt)ans = min(ans,tmp.val);
            lastans = ans;
        }
        lastans = inv[lastans];
        printf("%lld\n",lastans);
    }
    return 0;
}