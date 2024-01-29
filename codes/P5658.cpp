#include<bits/stdc++.h>
using namespace std;
const int maxn = 5 * 1e5 + 5;
stack<int> stk;
int n;
char c[maxn];
vector<int> son[maxn];
int fa[maxn];
long long res[maxn],sum[maxn];
long long ans;
void dfs(int root){
    int tmp = 0;
    if(c[root] == ')'){
        if(!stk.empty()){
            tmp = stk.top();
            res[root] = res[fa[tmp]] + 1;
            stk.pop();
        }
    }
    else if(c[root] == '(')stk.push(root);
    sum[root] = sum[fa[root]] + res[root];
    for(int i = 0,len = son[root].size();i < len;i++){
        dfs(son[root][i]);
    }
    if(tmp != 0)stk.push(tmp);
    else if(!stk.empty())stk.pop();
    return;
}
int main(){
    int t;
    scanf("%d",&n);
    scanf("%s",c + 1);
    for(int i = 2;i <= n;i++){
        scanf("%d",&t);
        fa[i] = t;
        son[t].push_back(i);
    }
    dfs(1);
    for(int i = 1;i <= n;i++){
        ans ^= sum[i] * (long long)i;
    }
    printf("%lld",ans);
    return 0;
}