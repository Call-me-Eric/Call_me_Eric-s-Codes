#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 4e5 + 10;
int n;
struct node{
    ll x, y;
    node(ll x = 0,ll y = 0):x(x),y(y){}
}a[maxn];

bool cmp2(node a,node b){return a.x != b.x ? a.x < b.x : a.y < b.y;}
bool cmp1(node a,node b){return a.y != b.y ? a.y < b.y : a.x < b.x;}

ll ans;
inline ll dist(int i,int j){return (a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y);}
void solve(int l,int r){
    if(l == r)return;
    int mid = l + r >> 1;solve(l,mid);solve(mid + 1,r);
    node tmp = a[mid + 1];
    inplace_merge(a + l,a + mid + 1,a + r + 1,cmp2);
    vector<int> vec;vec.clear();
    for(int i = l;i <= r;i++)if(abs(tmp.y - a[i].y) <= ans)vec.push_back(i);
    for(int i = 0, j = 0;i < vec.size();i++){
        while(j < vec.size() && (a[vec[j]].x - a[vec[i]].x) * (a[vec[j]].x - a[vec[i]].x) <= ans)j++;
        for(int k = i + 1;k < j;k++)ans = min(ans,dist(vec[i],vec[k]));
    }
}

signed main(){
    n = read();int u, v;
    for(int i = 1;i <= n;i++){
        u = read(); v = read();
        a[i] = node(u, v);
    }
    sort(a + 1,a + 1 + n,cmp1); ans = LONG_LONG_MAX;
    solve(1, n); printf("%lld\n",ans);
    return 0;
}