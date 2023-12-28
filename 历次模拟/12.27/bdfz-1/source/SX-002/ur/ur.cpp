#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,k;
int ans=0,ver=0;
vector<int>anss;
int main(){
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    scanf("%d%d",&n,&k);
    if(n==k){
        for(int i=1;i<=n;++i){
            printf("1");
        }
        return 0;
    }
    if(k<=1){
        for(int i=1;i<=n;++i){
            printf("0");
        }
        return 0;
    }
    for(int i=2;i<=n;++i){
        if((n%i)!=0) continue;
        if(k/i*i>ans){
            ans=k/i*i;
            ver=i;
            anss.clear();
            anss.push_back(0);
            for(int j=1;j<=n/i;++j){
                if(j<=k/i) anss.push_back(1);
                else anss.push_back(0);
            }
        }
    }
    // printf("%d %d\n",ans,ver);
    if(ans==0){
        for(int i=1;i<=n;++i){
            printf("0");
        }
    }
    else{
        for(int j=1;j<=ver;++j){
            for(int i=1;i<=n/ver;++i){
                printf("%d",anss[i]);
            }
        }
    }
    return 0;
}
/*
*/
