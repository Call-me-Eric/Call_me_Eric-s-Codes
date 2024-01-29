#include <iostream>
#include <cstring>
using namespace std;
int main(){
    char k[1005], c[1005];
    scanf("%s%s",k,c);
    int clen = strlen(c), klen = strlen(k);
    for (int i = 0;i < clen;i++) {
        int t = (k[i % klen] & 31) - 1;
        if((c[i] & 31) - t > 0)c[i] -= t;
        else c[i] = c[i] - t + 26;
    }
    printf("%s",c);
    return 0;
}
