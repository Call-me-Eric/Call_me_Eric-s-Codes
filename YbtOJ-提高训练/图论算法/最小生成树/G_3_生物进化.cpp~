#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n;
const int maxn = 110, INF = 0x3f3f3f3f;
int dis[maxn],pre[maxn];
bool book[maxn];
int w[maxn][maxn];
signed main(){
    n = read();
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            w[i][j] = read();
        }
    }
    memset(dis,0x3f,sizeof(dis));
    dis[1] = 0;
    for(int i = 1;i <= n;i++){
        int k = 0, minn = INF;
        for(int j = 1;j <= n;j++){
            if(!book[j] && dis[j] < minn){
                k = j;minn = dis[j];
            }
        }
        book[k] = 1;
        for(int j = 1;j <= n;j++){
            if(!book[j] && dis[j] > w[k][j]){
                dis[j] = w[k][j];
                pre[j] = k;
            }
        }
    }
    for(int i = 2;i <= n;i++)printf("%d\n",pre[i]);
    return 0;
}
