#include<bits/stdc++.h>
using namespace std;
int pr[22]={11,19,41,61,89,409,449,499,881,991,6469,6949,9001,9049,9649,9949,60649,666649,946669,60000049,66000049,66600049};
int hx[5]={0,4,6,8,9},prtl=21;
int T,xw[20][3];
bool chk1(int xx){
    for(int i=0;i<=prtl;i++){
        int x=xx,y=pr[i];
        while(x&&y){
            if(x%10==y%10)y/=10;
            x/=10;
        }if(!y)return false;
    }return true;
}
void dfs(int x,int zh,int flg){
    if(!chk1(zh))return;
    if(x>9){
        for(int i=1;i<=T;i++){
            if(xw[i][0]<=zh&&zh<=xw[i][1]){xw[i][2]++;}
        }return;
    }
    for(int i=0;i<5;i++){
        dfs(x+1,zh*10+hx[i],flg);
    }if(!flg)dfs(x+1,zh*10+1,1);
}
int main(){
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        scanf("%d%d",&xw[i][0],&xw[i][1]);if(xw[i][1]==1000000000)xw[i][2]++;
    }
    dfs(1,0,0);
    for(int i=1;i<=T;i++)
        printf("%d\n",xw[i][2]);
    return 0;
}