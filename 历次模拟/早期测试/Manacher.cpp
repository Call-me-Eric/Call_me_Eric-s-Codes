#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxstr = 10001;
char c[maxstr],a[maxstr * 2 + 10];
int p[maxstr * 2 + 10];
int main(){
    freopen("9.in","r",stdin);
    scanf("%s",c + 1);
    a[0] = '$';
    int len = strlen(c + 1);
    for(int i = 1;i <= len;i++){
        a[i * 2] = c[i];
    }
    for(int i = 1;i <= len;i++){
        a[i * 2 - 1] = '#';
    }
    len = len * 2 + 2;
    a[len - 1] = '#';
    a[len] = '\0';
    int mi = 0,right = 0;
    int maxpoint = 0, maxlen = 0;
    for(int i = 1;i < len;i++){
        p[i] = right > i ? min(p[2 * mi - i],right - i) : 1;
        while(a[i + p[i]] == a[i - p[i]])p[i]++;
        if(right < i + p[i]){
            right = i + p[i];
            mi = i;
        }
        if(maxlen < p[i]){
            maxlen = p[i];
            maxpoint = i;
        }
    }
    printf("%d\n",maxlen - 1);
    return 0;
}