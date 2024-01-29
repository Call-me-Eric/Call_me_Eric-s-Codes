#include<bits/stdc++.h>
using namespace std;
const int maxn = 1048576 + 100;
char s[maxn];
int T;
int a[maxn],b[maxn],c[maxn];//a[i]:1~i奇数,b[i]:i~n奇数
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%s",s+1);
        int len = strlen(s+1);
        bool flag = 0;
        int ans = 0;
        for(int i = 2;i <= len;i++){
            if(s[i] != s[i - 1]){
                flag = 1;
                break;
            }
        }
            memset(c,0,sizeof(c));
            a[0] = 0;
            for(int i = 1;i <= len;i++){
                c[s[i]]++;
                if(c[s[i]] & 1){
                    a[i] = a[i - 1] + 1;
                }
                else{
                    a[i] = a[i - 1] - 1;
                }
            }
            b[len + 1] = 0;
            memset(c,0,sizeof(c));
            for(int i = len;i >= 1;i--){
                c[s[i]]++;
                if(c[s[i]] & 1){
                    b[i] = b[i + 1] + 1;
                }
                else{
                    b[i] = b[i + 1] - 1;
                }
            }
            for(int i = 1;i < len;i++){
                for(int j = i + 1;j < len;j++){
                    for(int k = j + 1;k <= len;k += j){
                        if(strncmp(s + 1,s + k - j,j))break;
                        if(a[i] <= b[k])ans++;
                    }
                }
            }
            printf("%d\n",ans);
    }
    return 0;
}
//知道|AB|和C就确定i了
//所以要枚举|AB|和C
//暴力......
//A:0~i,B:i+1~j,C:j~n
//所以每当以上条件满足时ans++