#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n;char A[maxn], B[maxn];
signed main(){
    scanf("%s",A + 1);n = strlen(A + 1);
    for(int i = 1;i <= n;i++){
        int j = i;while(A[j + 1] == A[i])j++;
        char ch = 'a';while(A[j + 1] == ch || A[i] == ch)ch++;
        bool book = 0;
        for(int k = i;k <= j;k++){B[k] = book ? ch : A[i];book = !book;}
        i = j;
    }
    for(int i = 1;i <= n;i++)putchar(B[i]);
    puts("");
    return 0;
}