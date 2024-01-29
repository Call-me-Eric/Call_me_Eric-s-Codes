#include<bits/stdc++.h>
using namespace std;
int n;
const int maxn = 100010;
int a[maxn];
int maxx[maxn];
int ans;
int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
        maxx[i] = max(maxx[i - 1],a[i]);
    }
    for(int i = 1;i <= n;i++){
        if(maxx[i] <= i - 1){
            ans++;
        }
    }
    printf("%d",ans);
    return 0;
}