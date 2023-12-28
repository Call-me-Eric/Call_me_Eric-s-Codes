#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define int long long
using namespace std;
int n, q;
const int maxn = 1e6 + 10;
int a[maxn], c[maxn * 4];
int lownum(int i){
    return (-i) & i;
}
void update(int x,int z){
    a[x] += z;
    for(int i = x;i <= n;i += lownum(i)){
        c[i] += z;
    }
}
int sum(int x){
    int res = 0;
    for(int i = x;i > 0;i -= lownum(i)){
        res += c[i];
    }
    return res;
}
int sum(int x,int y){
    return sum(y) - sum(x - 1);
}
signed main(){
    scanf("%lld%lld",&n,&q);
    int tmp;
    for(int i = 1;i <= n;i++){
        scanf("%lld",&tmp);
        update(i,tmp);
    }   
    int x, y, z;
    for(int i = 1;i <= q;i++){
        scanf("%lld%lld%lld",&z,&x,&y);
        if(z == 1){
            update(x,y);
        }
        else{
            printf("%lld\n",sum(x,y));
        }
    }
    return 0;
}