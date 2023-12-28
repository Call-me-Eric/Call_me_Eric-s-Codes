#include<bits/stdc++.h>
using namespace std;
const int maxn = 110;
int n;char S[maxn];
char a[maxn][maxn];
char opt;
bool book[maxn], chg[maxn];
char tolow(char ch){if(ch >= 'A' && ch <= 'Z')return ch - 'A' + 'a';return ch;}
char toup(char ch){if(ch >= 'a' && ch <= 'z')return ch - 'a' + 'A';return ch;}
signed main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%s",a[i] + 1);
        for(int j = strlen(a[i] + 1);j;j--)a[i][j] = tolow(a[i][j]);
    }
    scanf("%s",S + 1);scanf(" %c",&opt);int len = strlen(S + 1);
    for(int i = strlen(S + 1);i;i--){if(S[i] >= 'A' && S[i] <= 'Z'){book[i] = 1;S[i] = tolow(S[i]);}}
    for(int i = 1;i <= len;i++){
        for(int j = 1;j <= n;j++){
            bool flag = 1;
            for(int k = 1,l = strlen(a[j] + 1);k <= l;k++){
                if(S[k + i - 1] != a[j][k]){flag = false;break;}
            }
            if(flag){for(int k = 1,l = strlen(a[j] + 1);k <= l;k++)chg[k + i - 1] = 1;}
        }
    }
    opt = tolow(opt);
    for(int i = 1;i <= len;i++){
        if(chg[i]){
            if(S[i] == opt){
                if(S[i] == 'a')S[i] = 'b';
                else S[i] = 'a';
            }
            else S[i] = opt;
        }
    }
    for(int i = 1;i <= len;i++){
        if(book[i])putchar(toup(S[i]));
        else putchar(S[i]);
    }
    puts("");
    return 0;
}