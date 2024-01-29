#include<bits/stdc++.h>
using namespace std;
int T;
int n,m;
int tot;
double x[100],y[100];
double a[100],b[100];
bool used[100];
int total;
int ans = 0x3f3f3f3f;
bool compare(double a,double b){
    return fabs(a - b) < 1e-8;
}
void dfs(int now,int sum){
    if(now == n + 1){
        if(sum + n - total < ans){
            ans = sum + n - total;
        }
        return;
    }
    if(sum >= ans)  return;
    bool book = false;
    for(int i = 1;i <= tot;i++){
        if(compare(a[i] * x[now] * x[now] + b[i] * x[now],y[now])){
            book = true;
            break;
        }
    }
    if(!book){
        for(int i = 1;i < now;i++){
            if(used[i]) continue;
            if(compare(x[i],x[now]))    continue;
            double a1 = (y[now] * x[i] - x[now] * y[i]) / 
            (x[i] * x[now] * x[now] - x[i] * x[now] * x[i]);
            double b1 = (y[now] - x[now] * x[now] * a1) / x[now];
            if(a1 < 0){
                a[++tot] = a1;
                b[tot] = b1;
                used[now] = 1;
                total ++;
                dfs(now + 1,sum + 1);
                total--;
                used[now] = 0;
                a[tot] = 0;
                b[tot--] = 0;
            }
        }
        dfs(now + 1,sum);
    }
    else{
        total++;
        dfs(now + 1,sum);
        total--;
    }
}
int main(){
    scanf("%d",&T);
    while(T--){
        ans = 0x3f3f3f3f;
        tot = 0;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(used,0,sizeof(used));
        total = 0;
        scanf("%d%d",&n,&m);
        for(int i = 1;i <= n;i++){
            scanf("%lf%lf",&x[i],&y[i]);
        }
        dfs(1,0);
        printf("%d\n",ans);
    }
    return 0;
}