#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
int n;
int head[maxn], tot = 1;
struct edge{
    int from, to, nexte, wei;
    edge(int fr = 0,int to = 0,int ne = 0,int we = 0):from(fr),to(to),nexte(ne),wei(we){}
}e[maxn << 1];
void add(int u,int v,int w){e[++tot] = edge(u,v,head[u],w);head[u] = tot;}

bool book[maxn];
int fat[maxn];
bool ring[maxn];
bool dfs1(int u,int father){
// printf("u = %d\n",u);
    book[u] = 1;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;
        if((i ^ 1) == father)continue;
        fat[v] = u;
        if(!book[v]){if(dfs1(v,i))return 1;}
        else{
            int tmp = u;
            while(1){
// printf("top() = %lld\n",tmp);
                ring[tmp] = 1;tmp = fat[tmp];
                if(tmp == u || !tmp)break;
            }
            return 1;
        }
    }
    return 0;
}

int f[maxn][2];
void dfs2(int u,int father){
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to, w = e[i].wei;
        if(v == father || ring[v])continue;
        dfs2(v, u);
        if(f[v][0] + w > f[u][0]){f[u][1] = f[u][0];f[u][0] = f[v][0] + w;}
        else if(f[v][0] + w > f[u][1]){f[u][1] = f[v][0] + w;}
    }
}

int wei[maxn], val[maxn];
int idx, mp[maxn];
void dfs3(int u,int father){
    if(book[u]){return;}book[u] = 1;
    idx++; val[idx] = f[u][0];mp[u] = idx;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to, w = e[i].wei;
        if(!ring[v] || (i ^ 1) == father)continue;
        wei[idx] = w;dfs3(v, i);break;
    }
}

int suf[maxn], pre[maxn];
int pre1[maxn], suf1[maxn];

int solve(vector<int> vec){
// puts("IN");
    /*找基环*/ dfs1(vec[0], 0);
// puts("11111");
    /*算各自子树最大值,并统计各自子树直径*/
    int ans2 = 0, sum = 0;
    for(int i : vec)if(ring[i]){dfs2(i,i);sum++;}
    for(int i : vec)ans2 = max(ans2,f[i][0] + f[i][1]);
// puts("22222");
// for(int i = 1;i <= n;i++)printf("ring[%lld]=%d\n",i,ring[i]);
    /*将环转变成链并重新编号*/
    for(int i : vec)book[i] = 0;
    for(int i = 1;i <= sum;i++){val[i] = wei[i] = 0;}idx = 0;
    for(int i : vec){if(ring[i]){dfs3(i,0);break;}}

    // if(idx == 2){return max(ans2,val[2] + val[1] + max(wei[2],wei[1]));}

// for(int i = 1;i <= n;i++){printf("mp[%lld] = %lld\n",i,mp[i]);}
// for(int i = 1;i <= n;i++){printf("wei[%lld] = %lld\n",i,wei[i]);}
// for(int i = 1;i <= n;i++){printf("val[%lld] = %lld\n",i,val[i]);}
    /*统计答案*/
    pre[1] = val[1];int tmp = 0;
    for(int i = 2;i <= idx;i++){
        tmp += wei[i - 1];
        pre[i] = max(pre[i - 1],val[i] + tmp);
    }
    suf[idx] = val[idx];tmp = 0;
    for(int i = idx - 1;i;i--){
        tmp += wei[i];
        suf[i] = max(suf[i + 1], val[i] + tmp);
    }
// for(int i = 1;i <= idx;i++)printf("pre[%lld] = %lld\n",i,pre[i]);
// for(int i = 1;i <= idx;i++)printf("suf[%lld] = %lld\n",i,suf[i]);
    int ans1 = 0, prex = val[1]; pre1[1] = val[1];
    for(int i = 1;i < idx;i++){
        pre1[i + 1] = prex + wei[i] + val[i + 1];
        prex += wei[i];prex = max(prex,val[i + 1]);
    }
    for(int i = 2;i <= idx;i++){pre1[i] = max(pre1[i],pre1[i - 1]);}
    int sufx = val[idx]; suf1[idx] = val[idx];
    for(int i = idx;i > 1;i--){
        suf1[i - 1] = sufx + wei[i - 1] + val[i - 1];
        sufx += wei[i - 1];sufx = max(sufx,val[i - 1]);
    }
    for(int i = idx - 1;i;i--)suf1[i] = max(suf1[i],suf1[i + 1]);
    for(int i = 1;i <= idx;i++){ans1 = max(ans1,pre1[i]);}
// printf("%lld~%lld : %lld\n",idx,1LL,ans1);
    for(int i = 1;i < idx;i++)ans1 = max(ans1,max(max(pre1[i],suf1[i + 1]),pre[i] + suf[i + 1] + wei[idx]));
    int tmp1 = max(ans1,ans2);
    // printf("tmp1 = %lld\n",tmp1);
    return tmp1;
}

int fa[maxn], total ,id[maxn];
int getf(int x){return x == fa[x] ? x : fa[x] = getf(fa[x]);}
vector<int> vec[maxn];

signed main(){
    n = read();int u, v, w;
    for(int i = 1;i <= n;i++)fa[i] = i;
    for(int i = 1;i <= n;i++){
        u = i; v = read(); w = read();
        add(u, v, w);add(v, u, w);
        if(getf(u) != getf(v))fa[getf(u)] = getf(v);
    }
    int ans = 0;
    for(int i = 1;i <= n;i++){
        if(!id[getf(i)])id[getf(i)] = ++total;
        vec[id[getf(i)]].push_back(i);
    }
    for(int i = 1;i <= total;i++)ans += solve(vec[i]);
    printf("%lld\n",ans);
    
    // for(int i = 1;i <= total;i++){
    //     printf("i = %lld\n",i);
    //     for(int j : vec[i])printf("id = %lld\n",j);
    // }

    return 0;
}