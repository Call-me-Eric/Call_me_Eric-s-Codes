#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
char ch[maxn];
int fail[maxn], n;
signed main(){
    while(scanf("%s", ch + 1) && ch[1] != '.'){
        fail[1] = 0;int j = 0; n = strlen(ch + 1);
        for(int i = 1;i < n;i++){
            while(j > 0 && ch[j + 1] != ch[i + 1])j = fail[j];
            if(ch[j + 1] == ch[i + 1])j++;
            fail[i + 1] = j;
        }
        if(n % (n - fail[n]) == 0)printf("%d\n",n / (n - fail[n]));
        else puts("1");
    }
    return 0;
}