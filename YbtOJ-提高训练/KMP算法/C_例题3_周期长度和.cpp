#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6 + 10;
char ch[maxn];
int n, p[maxn];
int find(int x){
    if(p[x] != 0)return p[x] = find(p[x]);
    return x;
}
signed main(){
    scanf("%lld", &n);
    scanf("%s", ch + 1);
    int j = 0;p[1] = 0;
    for(int i = 1;i < n;i++){
        while(j > 0 && ch[j + 1] != ch[i + 1])j = p[j];
        if(ch[j + 1] == ch[i + 1])j++;
        p[i + 1] = j;
    }
    int ans = 0;
    for(int i = 1;i <= n;i++){
        ans += i - find(i);
    }
    printf("%lld\n",ans);
    return 0;
}