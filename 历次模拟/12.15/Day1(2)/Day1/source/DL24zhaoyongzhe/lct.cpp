#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;

int n;
pair<int,int> edg[maxn];
int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}

signed main(){
    freopen("lct.in","r",stdin);
    freopen("lct.out","w",stdout);
    n = read(); int q = read();
    for(int i = 1;i < n;i++)
        edg[i] = make_pair(read(), read());
    for(int i = 1;i <= q;i++){
        int l = read(), r = read();
        for(int i = 1;i <= n;i++)fa[i] = i;
        for(int i = 1;i < n;i++){
            if(edg[i].first <= r && edg[i].first >= l && edg[i].second <= r && edg[i].second >= l){
                int fu = getf(edg[i].first), fv = getf(edg[i].second);
                if(fu != fv)fa[fu] = fv;
            }
        }
        int cnt = 0;
        for(int i = l;i <= r;i++)
            if(fa[i] == i)cnt++;
        printf("%d\n",cnt);
    }
    return 0;
}