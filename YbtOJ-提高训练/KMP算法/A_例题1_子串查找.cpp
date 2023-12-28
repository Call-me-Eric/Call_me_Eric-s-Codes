#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
char a[maxn], b[maxn];
int fail[maxn];
signed main(){
    scanf("%s",a + 1); scanf("%s",b + 1);
    int lena = strlen(a + 1);
    int lenb = strlen(b + 1);
    int j = 0, cnt = 0;
    for(int i = 1;i < lenb;i++){
        while(j > 0 && b[j + 1] != b[i + 1])j = fail[j];
        if(b[j + 1] == b[i + 1])j++;
        fail[i + 1] = j;
    }
    j = 0;
    for(int i = 0;i < lena;i++){
        while(j > 0 && b[j + 1] != a[i + 1])j = fail[j];
        if(b[j + 1] == a[i + 1])j++;
        if(j == lenb)cnt++, j = fail[j];
    }
    printf("%d\n",cnt);
    return 0;
}