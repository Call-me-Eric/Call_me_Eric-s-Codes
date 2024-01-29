#include<bits/stdc++.h>
using namespace std;
int n, m, a[50050],d[50050];
int minn[50050];
int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++){
        minn[i] = 0x7f7f7f7f;
        scanf("%d",&a[i]);
    }
    for(int i = n;i >= 1;i--){
        minn[i] = min(minn[i - 1],a[i]);
    }
    for(int i = 1;i <= m;i++){
        scanf("%d",&d[i]);
        
    }
    return 0;
}