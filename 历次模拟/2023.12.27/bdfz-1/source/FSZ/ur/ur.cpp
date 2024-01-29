#include<bits/stdc++.h>
using namespace std;
int n,m;
vector<int> vec;
int main(){
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    scanf("%d%d",&n,&m);
    if(n==m){
        for(int i=1;i<=n;i++)putchar('1');puts("");
        return 0;
    }else if(m<=1){
        for(int i=1;i<=n;i++)putchar('0');puts("");
        return 0;
    }
    int n1=n;
    for(int i=2;i*i<=n1;i++)while(n1%i==0)n1/=i,vec.push_back(i);
    if(n1>1)vec.push_back(n1);
    if(vec.size()==1){
        for(int i=1;i<=n;i++)putchar('0');puts("");
        return 0;
    }else if(vec.size()==2){

    }
    return 0;
}