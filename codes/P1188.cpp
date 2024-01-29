#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;
int n, k, a, b, c;
vector<int> txt, paste;
int main(){
    scanf("%d%d",&n,&k);
    for(int i = 1;i <= n;i++){
        txt.push_back(i);
    }
    for(int i = 1;i <= k;i++){
        scanf("%d%d%d",&a,&b,&c);
        paste.assign(txt.begin() + a - 1,txt.begin() + b);
        txt.erase(txt.begin() + a - 1,txt.begin() + b);
        txt.insert(txt.begin() + c,paste.begin(),paste.end());
        paste.clear();
    }
    for(int i = 0;i < 10;i++){
        printf("%d\n",txt[i]);
    }
    return 0;
}