#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10;
int n, m;
vector<int> vec[maxn];
long double p;
struct BIT{
    long double c[maxn];
    inline int lowbit(int x){return x & (-x);}
    void upd(int x,long double add){for(;x < n;x += lowbit(x))c[x] += add;}
    long double qry(int x){long double ans = 0;for(;x;x -= lowbit(x))ans += c[x];return ans;}
}tree;
long double qpow(long double x,int a){
    long double res = 1;
    while(a){
        if(a & 1)res = res * x;
        x = x * x;a >>= 1;
    }
    return res;
}
signed main(){
    scanf("%d%d%Lf",&n,&m,&p);
    for(int i = 1;i <= m;i++){
        int x = read(), y = read();
        vec[x].push_back(y);
    }
    for(int i = 1;i <= n;i++)sort(vec[i].begin(),vec[i].end());
    long double ans = 0;
    for(int i = 1;i <= n;i++){
        if(vec[i].empty())continue;
        long double tm = p / (1.0 - qpow(1.0 - p,vec[i].size())), pw = tm;
        for(int j = 0;j < vec[i].size();j++,pw *= (1.0 - p)){
            ans += pw * tree.qry(n - vec[i][j]);
            // printf("%Lf %Lf\n",pw,tree.qry(n - vec[i][j]));
        }
        pw = tm;
        for(int j = 0;j < vec[i].size();j++,pw *= (1.0 - p)){
            tree.upd(n - vec[i][j] + 1,pw);
            // printf("%Lf\n",pw);
        }
        // printf("%.2Lf\n",ans);
    }
    printf("%.2Lf\n",ans);
    return 0;
}