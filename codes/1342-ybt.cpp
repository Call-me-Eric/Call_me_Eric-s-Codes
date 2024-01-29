#include<bits/stdc++.h>
using namespace std;
const int maxn = 11000;
const double inf = (double)0x3f3f3f3f;
double e[maxn][maxn];
double dis[maxn];
int n;
int m;
int a,b;
int x[maxn],y[maxn];
int s,t;
int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%d%d",&x[i],&y[i]);
    }
    scanf("%d",&m);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(i != j){
                e[i][j] = inf;
            }
            else e[i][j] = 0;
        }
        dis[i] = inf;
    }
    for(int i = 1;i <= m;i++){
        scanf("%d%d",&a,&b);
        e[a][b] = sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]));
        e[b][a] = e[a][b];
    }
    scanf("%d%d",&s,&t);
    dis[s] = 0;
    /*for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(dis[i] + e[i][j] < dis[j]){
                dis[j] = dis[i] + e[i][j];
            }
        }
    }
    */
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++ ){
                if(e[i][j] > e[i][k] + e[k][j])
                    e[i][j] = e[i][k] + e[k][j];
            }
        }
    }
    printf("%.2lf",e[s][t]);
    return 0;
}