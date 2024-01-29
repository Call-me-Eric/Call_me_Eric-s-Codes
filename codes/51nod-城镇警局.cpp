#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int MAXN = 1e5 + 10;
int n, k, d;
int p[MAXN];
int f[MAXN];
bool book[MAXN];
int step[MAXN];
queue<int> que;
vector<int> tree[MAXN];
int main(){
    scanf("%d%d%d",&n,&k,&d);
    for(int i = 0;i < k;i++){
        scanf("%d",&p[i]);
        que.push(p[i]);
        book[p[i]] = 1;
    }
    int u,v;
    for(int i = 0;i < n - 1;i++){
        scanf("%d%d",&u,&v);
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    while(!que.empty()){
        int head = que.front();
        que.pop();
        if(step[head] == d)break;
        for(int i = 0,len = tree[head].size(); i < len;i++){
            int to = tree[head][i];
            if(book[to])continue;
            book[to] = 1;
            step[to] = step[head] + 1;
            que.push(to);
        }
    }
    int ans = 0;
    for(int i = 1;i <= n;i++){
        if(!book[i])ans++;
    }
    printf("%d",ans);
    return 0;
}