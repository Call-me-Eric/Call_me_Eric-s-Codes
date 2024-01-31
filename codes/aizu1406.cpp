#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e3 + 10;
int val[maxn],len[maxn],n;
char ch[100];
typedef pair<int,int> pii;
priority_queue<pii,vector<pii>,greater<pii> > que;
vector<int> dis[maxn];
void main(){
    n = read();
    for(int i = 1;i <= n;i++){
        scanf("%s",ch + 1); val[i] = 0; len[i] = strlen(ch + 1);
        for(int j = 1;j <= len[i];j++){val[i] = (val[i] << 1) + ch[j] - '0';}
        dis[i].assign(20,0x3f3f3f3f);
        dis[i][len[i]] = len[i];
        que.push(make_pair(dis[i][len[i]],i * 20 + len[i]));
    }
    while(!que.empty()){
        pii tmp = que.top();que.pop();
        int d = tmp.first, i = tmp.second / 20, r = tmp.second % 20;
        if(!r){printf("%d\n",d);return;}
        if(dis[i][r] < d)continue;
        int suf = val[i] & ((1 << r) - 1);
        for(int j = 1;j <= n;j++){
            if(i == j && r == len[i])continue;
            int ti = -1, tr = 0, w = 0;
            if(len[j] <= r){
                if((suf >> (r - len[j])) == val[j]){
                    ti = i;tr = r - len[j];w = 0;
                }
            }
            else{
                if((val[j] >> (len[j] - r)) == suf){
                    ti = j;w = tr = len[j] - r;
                }
            }
            if(ti == -1)continue;
            int td = w + d;
            if(dis[ti][tr] > td){
                dis[ti][tr] = td;
                que.push(make_pair(dis[ti][tr],ti * 20 + tr));
            }
        }
    }
    puts("0");
    return;
}
};
bool edmemory;
signed main(){
    int stclock = clock();
    Call_me_Eric::main();
    int edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}