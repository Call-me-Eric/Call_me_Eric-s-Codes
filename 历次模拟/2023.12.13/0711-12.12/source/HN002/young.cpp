#include<bits/stdc++.h>
using namespace std;
int n,m,q,a[110],b[110],ans;
void dfs(int x){int he=0;
    for(int i=1;(a[i]!=0||b[i]!=0);i++){
        he+=abs(a[i]-b[i]);
    }if(he>x)return;
    if(!x){ans++;return;}
    for(int i=1;;i++){
        if(i==1||a[i-1]>a[i]){
            a[i]++;dfs(x-1);a[i]--;
        }if(!a[i])break;
    }
    for(int i=1;a[i]>0;i++){
        if(a[i]>a[i+1]){
            a[i]--;dfs(x-1);a[i]++;
        }
    }
}
int main(){
    freopen("young.in","r",stdin);
    freopen("young.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)scanf("%d",&b[i]);
    scanf("%d",&q);
    while(q--){
        int x;scanf("%d",&x);ans=0;
        dfs(x);printf("%d\n",ans);
    }return 0;
}