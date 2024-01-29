#include<bits/stdc++.h>
using namespace std;
int n,h[1000005],ans = 1;
bool book = 0;
int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%d",&h[i]);
    }
    if(h[2] >= h[1]){
        book = 1;
    }
    for(int i = 1;i <= n;i++){
        if(book == 0 && i == n){
            ans++;
            break;
        }
        else if(book == 1 && h[i + 1] < h[i]){
            ans++;
            book = 0;
        }
        else if(book == 0 && h[i + 1] > h[i]){
            ans++;
            book = 1;
        }
    }
    printf("%d\n",ans);
    return 0;
}