#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, p[maxn];
bool book[maxn];
vector<pair<int,int> > vec;
signed main(){
    n = read();
    for(int i = 1;i <= n;i++)p[i] = read();
    int u = 0;for(int i = 1;i <= n;i++)if(p[i] == i){u = i;break;}
    if(u){
        puts("YES");
        for(int i = 1;i <= n;i++)
            if(i != u)printf("%d %d\n",i,u);
        return 0;
    }
    u = 0;
    for(int i = 1;i <= n;i++)if(p[p[i]] == i){u = i;book[p[u]] = book[u] = 1;break;}
    if(!u){puts("NO");return 0;}
    else{
        for(int i = 1;i <= n;i++){
            if(!book[i]){
                int cnt = 0, v = p[i];book[i] = 1;
                while(v != i){book[v] = 1;cnt++;v = p[v];}
                if((cnt & 1) == 0){puts("NO");return 0;}
                v = p[i];vec.push_back(make_pair(p[u],i));
                while(v != i){vec.push_back(make_pair(u, v));v = p[v];u = p[u];}
            }
        }
        vec.push_back(make_pair(u,p[u]));
        puts("YES");
        for(auto i : vec)printf("%d %d\n",i.first,i.second);
    }
    return 0;
}