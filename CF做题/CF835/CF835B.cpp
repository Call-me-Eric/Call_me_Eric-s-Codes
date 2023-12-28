#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int k, sum;char ch[maxn];
priority_queue<int,vector<int>, greater<int> > que;
signed main(){
    scanf("%d",&k); scanf("%s",ch + 1);int len = strlen(ch + 1);
    for(int i = 1;i <= len;i++){que.push(ch[i] - '0');sum += int(ch[i] - '0');}
    int cnt = 0;
    // printf("%d\n",que.top());
    while(sum < k && !que.empty()){sum += (9 - que.top());que.pop();cnt++;}
    printf("%d\n",cnt);
    return 0;
}