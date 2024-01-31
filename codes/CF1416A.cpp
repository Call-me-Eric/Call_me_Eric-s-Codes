#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int n, a[maxn];
int ans[maxn];
vector<int> vec[maxn];
signed main(){
int T = read();
while(T--){
    n = read();memset(ans,0x3f,sizeof(ans));
    for(int i = 1;i <= n;i++){a[i] = read();vec[i].clear();}
    for(int i = 1;i <= n;i++)vec[i].push_back(0);
    for(int i = 1;i <= n;i++)vec[a[i]].push_back(i);
    for(int i = 1;i <= n;i++)vec[i].push_back(n + 1);

    for(int i = n;i;i--){
        int mx = 0;
        for(int j = 0;j + 1 < vec[i].size();j++)
            mx = max(mx,vec[i][j + 1] - vec[i][j]);
        ans[mx] = i;
    }
    for(int i = 1;i <= n;i++){
        ans[i] = min(ans[i],ans[i - 1]);
        if(ans[i] == 0x3f3f3f3f)printf("-1 ");
        else printf("%d ",ans[i]);
    }
    puts("");
}
    return 0;
}