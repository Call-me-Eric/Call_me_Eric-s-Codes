#include<bits/stdc++.h>
using namespace std;
int n;
const int maxn = 50000 + 5;
int h[maxn];
int ans;
int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%d",&h[i]);
    }
    int maxx = -114514;
    for(int i = 2,s = 1;i <= n;i++){
        if(h[s] > h[i]){
            ans += h[s] - h[i];
        }
        else {
            s = i;
        }
        if(h[i] > maxx)maxx = h[i];
    }
    for(int i = n - 1,s = n;i >= 1;i--){
        if(h[s] > h[i]){
            ans += h[s] - h[i];
        }
        else {
            s = i;
        }
    }
    int tmp = 0;
    for(int i = 1;i <= n;i++){
        tmp += maxx - h[i];
    }
    printf("%d\n",ans - tmp);
    return 0;
}