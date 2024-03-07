#include<bits/stdc++.h>
using namespace std;
int n;
const int maxn = 1e6 + 10;
char ch[maxn];
int fail[maxn];
signed main(){
    scanf("%d",&n);
    scanf("%s",ch + 1);
    int j = 0;
    for(int i = 2;i <= n;i++){
        while(j > 0 && ch[i] != ch[j + 1])j = fail[j];
        if(ch[i] == ch[j + 1])j++;
        fail[i] = j;
    }
    printf("%d\n",n - fail[n]);
    return 0;
}