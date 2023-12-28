#include<bits/stdc++.h>
using namespace std;
int n;
const int maxn = 6, maxm = 2010;
char ch[maxn][maxm];
int len[maxn], fail[maxm];
void pre(char *a){
    fail[1] = 0; int n = strlen(a + 1);
    for(int i = 2, j = 0;i <= n;i++){
        while(j > 0 && a[i] != a[j + 1])j = fail[j];
        if(a[i] == a[j + 1])j++;
        fail[i] = j;
    }
    return;
}
int kmp(char *a,int k){
    int res = 0, n = strlen(a + 1),len = strlen(ch[k] + 1);
    for(int i = 1, j = 0;i <= len;i++){
        while(j > 0 && ch[k][i] != a[j + 1]){res = max(res, j - 1) ;j = fail[j];}
        if(ch[k][i] == a[j + 1]){j++; res = max(res, j);}
        if(j == n)return n;
    }
    return res;
}
signed main(){
    scanf("%d",&n);
    int minn = 0x3f3f3f3f, minlen = 0x3f3f3f3f, tmp = 0;
    for(int i = 1;i <= n;i++){
        scanf("%s",ch[i] + 1); len[i] = strlen(ch[i] + 1);
        if(minn > len[i]){minlen = len[i];tmp = i;}
    }
    int ans = -0x3f3f3f3f;
    for(int l = 1;l <= minlen;l++){
        pre(ch[tmp] + l - 1); minn = 0x3f3f3f3f;
        for(int k = 1;k <= n;k++){
            if(k == tmp)continue;
            minn = min(minn, kmp(ch[tmp] + l - 1,k));
        }
        ans = max(ans,minn);
    }
    printf("%d\n",ans);
    return 0;
}