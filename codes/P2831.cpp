#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
bool equal(double a,double b){
    return abs(a - b) < eps;
}
int n, m, T;
double x[20], y[20];
double a[20], b[20];
int lonepig[20];//lonepig[i] means the i.st lone pig is lonepig[i]
int ans = 20;
void dfs(int num,int line,int pig){
    if(line + pig > ans)return;
    if(num > n){
        ans = line + pig;
        return;
    }
    bool flag = 0;
    for(int i = 1;i <= line;i++){//if there is a line across it
        if(equal(a[i] * x[num] * x[num] + b[i] * x[num],y[num])){
            dfs(num + 1,line,pig);
            flag = 1;
            break;
        }
    }
    if(!flag){//but nope
        for(int i = 1;i <= pig;i++){
            if(equal(x[lonepig[i]],x[num]))//if they are in a line(x=i), there won't a line across them
                continue;         //in a time
            double A = (y[num] * x[lonepig[i]] - y[lonepig[i]] * x[num]) / (x[num] * x[num] * x[lonepig[i]] - x[lonepig[i]] * x[lonepig[i]] * x[num]);
            double B = (y[num] - x[num] * x[num] * A) / x[num];
            if(A < 0){
                a[line + 1] = A;
                b[line + 1] = B;
                int tmp = lonepig[i];
                for(int j = i;j <= pig;j++){
                    lonepig[j] = lonepig[j + 1];
                }
                dfs(num + 1,line + 1,pig - 1);
                for(int j = pig;j >= i;j--){
                    lonepig[j] = lonepig[j - 1];
                }
                lonepig[i] = tmp;
            }
        }
    }
    lonepig[pig + 1] = num;
    dfs(num + 1,line,pig + 1);
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i = 1;i <= n;i++){
            scanf("%lf%lf",&x[i],&y[i]);
        }
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        ans = 20;
        dfs(1, 0, 0);
        printf("%d\n",ans);
    }
    return 0;
}