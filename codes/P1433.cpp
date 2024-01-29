#include<bits/stdc++.h>
using namespace std;
double e[20][20];
double a[20], b[20];
int n;
double ans = 0x3f3f3f3f;
bool book[20];
void dfs(int now,double sum,int k){
    if(sum > ans)return;
    if(n == k){
        if(sum < ans)ans = sum;
        return;
    }
    for(int i = 0;i <= n;i++){
        if(!book[i] && i != now){
            book[i] = 1;
            dfs(i,sum + e[now][i],k + 1);
            book[i] = 0;
        }
    }
}
int main(){
    scanf("%d",&n);
    a[0] = 0;
    b[0] = 0;
    for(int i = 1;i <= n;i++){
        scanf("%lf%lf",&a[i],&b[i]);
    }
    for(int i = 0;i <= n;i++){
        for(int j = 0;j <= n;j++){
            if(i != j){
                e[i][j] = e[j][i] = 
                sqrt((a[i] - a[j]) * (a[i] - a[j])
                 + (b[i] - b[j]) * (b[i] - b[j]));
            }
            else e[i][j] = 0x3f3f3f3f;
        }
    }
    book[0] = 1;
    dfs(0,0,0);
    printf("%.2lf\n",ans);
    return 0;
}