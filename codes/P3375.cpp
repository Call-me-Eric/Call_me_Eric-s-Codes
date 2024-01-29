#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
char a[maxn], b[maxn];
int fail[maxn];
signed main(){
    scanf("%s%s",a + 1,b + 1);
    int lena = strlen(a + 1), lenb = strlen(b + 1);
    int j = 0; fail[1] = 0;
    for(int i = 2;i <= lenb;i++){
        while(j > 0 && b[i] != b[j + 1])j = fail[j];
        if(b[i] == b[j + 1])j++;
        fail[i] = j;
    }
    j = 0;
    for(int i = 1;i <= lena;i++){
        while(j > 0 && a[i] != b[j + 1])j = fail[j];
        if(a[i] == b[j + 1])j++;
        if(j == lenb)printf("%d\n",i - lenb + 1), j = fail[j];
    }
    for(int i = 1;i < lenb;i++) printf("%d ",fail[i]);
    printf("%d",fail[lenb]);
    return 0;
}