#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e3 + 10;
char ch[maxn][maxn];
int f[maxn][maxn];
int n, k;
char ans[maxn * 2];
bool book[maxn][maxn];
queue<pair<int,int> > que;
signed main(){
    scanf("%d%d",&n,&k);
    for(int i = 1;i <= n;i++){scanf("%s",ch[i] + 1);}
    for(int i = 0;i <= n + 1;i++)f[i][0] = f[0][i] = 0x3f3f3f3f;
    f[1][0] = 0;int st = 0, tmp = 0;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++){
            f[i][j] = min(f[i - 1][j],f[i][j - 1]) + (ch[i][j] != 'a');
            if(f[i][j] <= k)st = max(st,i + j - 1),tmp = max(tmp,f[i][j]);
        }
    for(int i = 1;i <= n * 2;i++)ans[i] = 'z' + 1;
    if(k == 0){
        que.push(make_pair(1,1));st = 0;ans[1] = ch[1][1];
        while(!que.empty()){
            int u = que.front().first, v = que.front().second;que.pop();
            if(ch[u][v] > ans[u + v - 1])continue;
            if(v + 1 <= n){
                ans[u + v] = min(ans[u + v],ch[u][v + 1]);
                if(!book[u][v + 1] && ch[u][v + 1] == ans[u + v]){book[u][v + 1] = 1;que.push(make_pair(u,v + 1));}
            }
            if(u + 1 <= n){
                ans[u + v] = min(ans[u + v],ch[u + 1][v]);
                if(!book[u + 1][v] && ch[u + 1][v] == ans[u + v]){book[u + 1][v] = 1;que.push(make_pair(u + 1,v));}
            }
        }
    }
    else{
        for(int i = 1;i <= st && i <= n;i++)
            if(f[i][st - i + 1] == tmp){que.push(make_pair(i,st - i + 1));book[i][st - i + 1] = 1;}
        
        while(!que.empty()){
            int u = que.front().first, v = que.front().second;que.pop();
            if(ch[u][v] > ans[u + v - 1])continue;
            if(v + 1 <= n){
                ans[u + v] = min(ans[u + v],ch[u][v + 1]);
                if(!book[u][v + 1] && ch[u][v + 1] == ans[u + v]){book[u][v + 1] = 1;que.push(make_pair(u,v + 1));}
            }
            if(u + 1 <= n){
                ans[u + v] = min(ans[u + v],ch[u + 1][v]);
                if(!book[u + 1][v] && ch[u + 1][v] == ans[u + v]){book[u + 1][v] = 1;que.push(make_pair(u + 1,v));}
            }
        }
    }
    for(int i = 1;i <= st;i++){putchar('a');}
    for(int i = st + 1;i <= n * 2 - 1;i++)putchar(ans[i]);
    puts("");
    return 0;
}