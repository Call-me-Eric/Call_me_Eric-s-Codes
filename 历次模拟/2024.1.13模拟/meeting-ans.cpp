#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 8e3 + 10;
int n, k;
vector<pair<int,int> > vec[maxn];
struct node{
    int l, r, val;
    node(int l = 0,int r = 0,int val = 0):l(l),r(r),val(val){}
    friend bool operator < (node a,node b){return a.l != b.l ? a.l < b.l : a.r < b.r;}
}a[maxn];
vector<int> X;
int f[maxn];
void solve(){
    n = read(); k = read(); X.clear();
    for(int i = 1;i <= n;i++){
        int u = read(), v = read();
        a[i] = node(u, v, read());
        X.push_back(u);X.push_back(v);
    }
    sort(X.begin(),X.end());X.erase(unique(X.begin(),X.end()),X.end());
    int m = X.size(), tot = 0,ans = 0x3f3f3f3f3f3f3f3f;
    for(int i = 1;i <= m;i++){vec[i].clear();f[i] = 0;}
    for(int i = 1;i <= n;i++){
        a[i].l = lower_bound(X.begin(),X.end(),a[i].l) - X.begin() + 1;
        a[i].r = lower_bound(X.begin(),X.end(),a[i].r) - X.begin() + 1;
        // printf("%lld %lld\n",a[i].l,a[i].r);
        vec[a[i].l].push_back(make_pair(a[i].r,a[i].val));tot += a[i].val;
    }
    for(int i = 1;i <= m;i++){
        priority_queue<int,vector<int>,greater<int> > que;
        int sum = 0;
        for(int j = i;j > 0;j--){
            for(auto x : vec[j]){
                if(x.first <= i){
                    if(que.size() < k){que.push(x.second);sum += x.second;}
                    else{
                        if(que.top() < x.second){
                            sum -= que.top();que.pop();
                            que.push(x.second);sum += x.second;
                        }
                    }
                }
            }
            f[i] = max(f[j - 1] + sum,f[i]);
        }
        // printf("f[%lld] = %lld\n",i,f[i]);
        ans = min(ans,tot - f[i]);
    }
    printf("%lld\n",ans);
}
signed main(){
    freopen("meeting.in","r",stdin);
    freopen("meeting.out","w",stdout);
    auto stclock = clock();
    int T = read();
    while(T--){solve();}
    cerr << (clock() - stclock) * 1000.0 / CLOCKS_PER_SEC << "  Time costed.\n";
    return 0;
}