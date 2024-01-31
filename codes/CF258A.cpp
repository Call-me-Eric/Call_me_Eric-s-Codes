#include<bits/stdc++.h>
using namespace std;
char ch[110000];
signed main(){
    scanf("%s",ch + 1);int pos = -1,len = strlen(ch + 1);
    for(int i = 1;i <= len;i++)
        if(ch[i] == '0'){pos = i;break;}
    if(pos == -1)pos = 1;
    for(int i = 1;i <= len;i++){if(pos == i)continue;putchar(ch[i]);}
    puts("");
    return 0;
}