#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e6 + 10;
int n;char ch[maxn];
stack<char> stk;
stack<int> point;
void solve50pts(){
    int ans = 0;
    for(int i = 1;i <= n;i++){
        while(!stk.empty())stk.pop();stk.push(ch[i]);
        for(int j = i + 1;j <= n;j++){
            if(stk.empty() || stk.top() != ch[j]){stk.push(ch[j]);continue;}
            else {stk.pop();if(stk.empty()){ans++;}}
        }
    }
    printf("%lld\n",ans);
}
map<int,int> mp[maxn];
int nxt[maxn], f[maxn];
signed main(){
    scanf("%lld",&n);scanf("%s",ch + 1);
    for(int i = 1;i <= n;i++){
        if(mp[i - 1].count(ch[i] - 'a')){
            int p = mp[i - 1][ch[i] - 'a'];
            nxt[i] = p;
            swap(mp[i],mp[p - 1]);
            if(p != 1)mp[i][ch[p - 1] - 'a'] = p - 1;
        }
        mp[i][ch[i] - 'a'] = i;
    }
    int ans = 0;
    for(int i = 1;i <= n;i++){
        if(!nxt[i])continue;
        f[i] = f[nxt[i] - 1] + 1;
        ans += f[i];
    }
    printf("%lld\n",ans);
    return 0;
}