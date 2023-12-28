#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int L[10010], R[10010];
int n, ans;
int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%d%d",&L[i],&R[i]);
    }
    bool book = 1;
    for(int i = n;i > 0;i--){
        book = 1;
        for(int j = i + 1;j <= n;j++){
            if(L[j] <= L[i] && R[i] <= R[j]){
                book = 0;
                break;
            }
        }
        ans += book;
    }
    printf("%d\n",ans);
    return 0;
}