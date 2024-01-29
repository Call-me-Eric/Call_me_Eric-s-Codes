#include<bits/stdc++.h>
using namespace std;
int n,k,d;
bool tag[1000005];
int main(){
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    scanf("%d%d",&n,&k);
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            d=i;
            break;
        }
    }
    if(d==0){
        if(k<n){
            for(int i=1;i<=n;i++){
                putchar('0');
            }
        }
        else{
            for(int i=1;i<=n;i++){
                putchar('1');
            }
        }
        return 0;
    }
    for(int j=1;j*d<=k;j++){
        int st=j;
        for(int l=1;l<=d;l++){
            st+=(n/d);
            if(st>n){
                st-=n;
            }
            tag[st]=true;
        }
    }
    // int sum=0;
    for(int i=1;i<=n;i++){
        // sum+=tag[i];
        printf("%d",tag[i]);
    }
    // puts("");
    // printf("%d",sum);
    return 0;
}