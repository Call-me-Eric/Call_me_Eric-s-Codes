#include<bits/stdc++.h>
using namespace std;
int n;char ch[222];
signed main(){
    scanf("%d",&n);int ans = 0;
    while(scanf("%s",ch + 1) != EOF){
        int cnt = 0;for(int i = 1;i <= strlen(ch + 1);i++){if('A' <= ch[i] && ch[i] <= 'Z')cnt++;}
        ans = max(ans,cnt);
    }
    printf("%d\n",ans);
    return 0;
}