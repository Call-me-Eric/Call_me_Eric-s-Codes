#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char  ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e3 + 10;
int n, m;
int a[maxn];
int mn[maxn], mx[maxn], tot1, tot2;

int match[maxn];
bool book[maxn];
bool dfs(int u){
    for(int v = 1;v <= tot1;v++){
        if(mx[u] % mn[v] == 0 && !book[v] && mx[u] * 2 + mn[v] <= m){
            book[v] = 1;
            if(!match[v] || dfs(match[v])){
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

vector<pair<int,int> > vec;

signed main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    sort(a + 1,a + 1 + n);
    if(a[n] > m / 2){puts("-1");return 0;}
    for(int i = 1;i <= n;i++){
        if(a[i] <= m / 3)mn[++tot1] = a[i];
        else mx[++tot2] = a[i];
    }
    if(tot1 < tot2){puts("-1");return 0;}
    for(int i = 1;i <= tot2;i++){
        for(int j = 1;j <= tot1;j++)book[j] = 0;
        if(!dfs(i)){puts("-1");return 0;}
    }
    for(int i = 1;i <= tot1;i++){
        if(!match[i])vec.push_back(make_pair(mn[i] * 3,mn[i] * 2));
        else vec.push_back(make_pair(mx[match[i]] + mx[match[i]] + mn[i],mx[match[i]] + mn[i]));
    }
    printf("%d\n",vec.size());
    for(auto i : vec)printf("%d %d\n",i.first,i.second);
    return 0;
}