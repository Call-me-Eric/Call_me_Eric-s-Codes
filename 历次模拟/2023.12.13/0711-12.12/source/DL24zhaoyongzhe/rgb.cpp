#include<bits/stdc++.h>
#include<time.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x  =(x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 260, maxm = maxn * maxn;
struct edge{
    int u, v, col, id;
    edge(int u = 0,int v = 0,int col = 0,int id = 0):u(u),v(v),col(col),id(id){}
}e[maxm];

int r, g, b, m, n;
int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
int ned[4], tot[4];
bool book[maxm];

signed main(){
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    r = read(), g = read(), b = read();n = r + g + b + 1;m = read();
    ned[1] = r;ned[2] = g;ned[3] = b;
    for(int i = 1;i <= m;i++){
        char ch[6];
        int u = read(), v = read();scanf(" %s",ch);
        e[i] = edge(u, v,ch[0] == 'r' ? 1 : (ch[0] == 'g' ? 2 : 3) , i);
        tot[e[i].col]++;
    }
    if(tot[1] < ned[1] || tot[2] < ned[2] || tot[3] < ned[3]){puts("NO");return 0;}
    for(int test = 5e7 / max(n,m);test;test--){
        random_shuffle(e + 1,e + 1 + m);int cnt[4] = {0};
        for(int i = 1;i <= n;i++)fa[i] = i;
        for(int i = 1;i <= m;i++)book[i] = 0;
        bool check = false;
        for(int i = 1;i <= m;i++){
            int u = getf(e[i].u), v = getf(e[i].v);
            if(u != v){
                if(cnt[e[i].col] < ned[e[i].col]){
                    fa[u] = v;cnt[e[i].col]++;
                    book[e[i].id] = 1;
                }
            }
            if(cnt[3] == ned[3] && cnt[1] == ned[1] && cnt[2] == ned[2]){check = true;break;}
        }
        if(check){
            puts("YES");
            for(int i = 1;i <= m;i++){putchar('0' + book[i]);}
            return 0;
        }
    }
    puts("NO");
    return 0;
}