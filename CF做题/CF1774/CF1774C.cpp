#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n;char ch[maxn];
signed main(){
int T;scanf("%d",&T);
while(T--){
    scanf("%d",&n);scanf("%s",ch + 1);
    int mx0 = 0, mx1 = 0,len0 = 0, len1 = 0;
    for(int i = 1;i < n;i++){
        len0 = (ch[i] == '0') ? (len0 + 1) : 0;
        len1 = (ch[i] == '1') ? (len1 + 1) : 0;
        printf("%d ",i - max(len0,len1) + 1);
    }
    puts("");
}
    return 0;
}