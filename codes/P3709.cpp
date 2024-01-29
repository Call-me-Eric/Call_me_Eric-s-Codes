#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, m;
int a[maxn];vector<int> tmp;

int len, cnt[maxn], tot[maxn],ans;
int res[maxn];
struct query{
    int l, r, id;
    query(int l = 0,int r = 0,int id = 0):l(l),r(r),id(id){}
    friend bool operator < (query a,query b){
        if(a.l / len != b.l / len)return a.l < b.l;
        return ((a.l / len) & 1) ? a.r < b.r : a.r > b.r;
    }
}q[maxn];

signed main(){
    n = read(); m = read();int l, r;
    for(int i = 1;i <= n;i++)tmp.push_back(a[i] = read());
    sort(tmp.begin(),tmp.end());tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
    for(int i = 1;i <= n;i++)a[i] = lower_bound(tmp.begin(),tmp.end(),a[i]) - tmp.begin();

    for(int i = 1;i <= m;i++){l = read(); r = read(); q[i] = query(l,r,i);}
    len = sqrt(n);sort(q + 1,q + 1 + m);
    
    l = 1, r = 1;cnt[a[1]]++;ans = 1;tot[1] = 1;
    for(int i = 1;i <= m;i++){
        while(q[i].l < l){--l;cnt[a[l]]++;ans += !tot[cnt[a[l]]]++;}
        while(r < q[i].r){++r;cnt[a[r]]++;ans += !tot[cnt[a[r]]]++;}
        while(l < q[i].l){ans -= !--tot[cnt[a[l]]];--cnt[a[l]];l++;}
        while(q[i].r < r){ans -= !--tot[cnt[a[r]]];--cnt[a[r]];r--;}
        // printf("l = %d r = %d\n",l,r);
        // for(int i = 0;i <= tmp.size();i++)
        //     printf("[%d]cnt=%d, tot=%d\n",i,cnt[i],tot[i]);
        // printf("ans = %d\n",ans);
        res[q[i].id] = ans;
    }
    for(int i = 1;i <= m;i++)printf("%d\n",-res[i]);
    return 0;
}