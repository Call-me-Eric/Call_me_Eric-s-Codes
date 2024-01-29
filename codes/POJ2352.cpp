#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
const int maxn = 15010,maxm = 35010;
int x[maxn], y[maxn];
int book[maxn];
int n, m;
int a[maxm], c[maxm];
int lownum(int i){
    return (-i) & i;
}
void update(int x,int z){
    a[x] += z;
    for(int i = x;i <= m;i += lownum(i)){
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
int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%d%d",&x[i],&y[i]);
        x[i]++;
        m = max(m,x[i]);
    }
    for(int i = 1;i <= n;i++){
        book[sum(x[i])]++;
        update(x[i],1);
    }
    for(int i = 0;i < n;i++){
        printf("%d\n",book[i]);
    }
    return 0;
}