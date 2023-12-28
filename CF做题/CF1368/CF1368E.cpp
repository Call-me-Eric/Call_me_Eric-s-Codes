#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, m, col[maxn];
signed main(){
int T = read(), u, v;
while(T--){
    n = read(); m = read();
    vector<set<int>> fr(n + 1);
    for(int i = 1;i <= n;i++)col[i] = 0;
    for(int i = 1;i <= m;i++){
        u = read(); v=  read();
        fr[v].insert(u);
    }
    for(int v = 1;v <= n;v++){
        for(int u : fr[v]){
            if(col[u] == 1){col[v] = 2;break;}
            if(!col[u])col[v] = 1;
        }
    }
    vector<int> ans;ans.clear();
    for(int i = 1;i <= n;i++)
        if(col[i] == 2)ans.push_back(i);
    printf("%d\n",ans.size());
    for(int i : ans)printf("%d ",i);
    puts("");
}
    return 0;
}