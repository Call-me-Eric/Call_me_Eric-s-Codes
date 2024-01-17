#include<bits/stdc++.h>
#define int long long
using namespace std;
int n=100000000,s[100000010],pr[100000010],prtl;
bool chk(int x){
    while(x){
        int xx=x%10;x/=10;
        if(xx!=0&&xx!=1&&xx!=4&&xx!=6&&xx!=8&&xx!=9)return false;
    }return true;
}
bool chk1(int xx){
    for(int i=1;i<=prtl;i++){
        int x=xx,y=pr[i];
        while(x&&y){
            if(x%10==y%10)y/=10;
            x/=10;
        }if(!y)return false;
    }return true;
}
signed main(){
    freopen("pr.out","w",stdout);
    s[1]=1;
    for(int i=2;i<=n;i++){
        if(s[i])continue;
        if(chk(i)&&chk1(i)){prtl++;pr[prtl]=i;printf("%lld,",i);}
        for(int j=i;1ll*i*j<=n;j++){
            s[i*j]=1;
        }
    }
    /*for(int i=n+1;i<=10000000000;i++){
        if(i%2==0||i%3==0||i%5==0||i%7==0)continue;
        if((!chk(i))||(!chk1(i)))continue;
        int flg=0;
        for(int j=2;1ll*j*j<=i;j++){
            if(i%j==0){flg=1;break;}
        }if(!flg)printf("%lld ",i);
    }*/
}