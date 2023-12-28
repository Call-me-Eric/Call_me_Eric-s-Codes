#include<bits/stdc++.h>
using namespace std;
const int maxn = 15 * 1e3 + 10;
int k, fail[maxn];
char ch[maxn];
long long ans = 0;
void solve(char *a){
    fail[1] = 0;
    int n = strlen(a + 1);
    for(int i = 1, j = 0;i < n;i++){
        while(j > 0 && a[i + 1] != a[j + 1])j = fail[j];
        if(a[i + 1] == a[j + 1])j++;
        fail[i + 1] = j;
    }
    for(int i = 1, j = 0;i < n;i++){
        while(j > 0 && a[i + 1] != a[j + 1])j = fail[j];
        if(a[i + 1] == a[j + 1])j++;
        while((j << 1) >= (i + 1))j = fail[j];
        if(j >= k)ans++;
    }
}
signed main(){
    scanf("%s",ch + 1);
    scanf("%d",&k);
    int n = strlen(ch + 1);
    for(int i = 0;i < n;i++) solve(ch + i);
    printf("%lld\n",ans);
    return 0;
}