#include<bits/stdc++.h>
using namespace std;
int r,g,b,m;
int n;
struct node{
    int u,v;
    char col;
}E[62555];//
vector<int> ljb[255];
class NetLogicFlow{
    public:
    int n,m,s,t;
    int cnt=1;
    int head[70000];
    int nxt[200000];
    int pos[70000];
    struct node{
        int v,flow,cost;
    }E[200000];
    void addedge(int u,int v,int flow,int cost){
        cnt++;
        nxt[cnt]=head[u];
        head[u]=cnt;
        E[cnt].v=v;
        E[cnt].flow=flow;
        E[cnt].cost=cost;
        return;
    }
    void Add(int u,int v,int flow,int cost){
        addedge(u,v,flow,cost);
        addedge(v,u,0,-cost);
        // printf("%d %d %d %d\n",u,v,flow,cost);
        return;
    }
    bool in[70000];
    int dep[70000];
    bool vis[70000];
    bool SPFA(){
        for(int i=1;i<=n;i++){
            dep[i]=2e9;
        }
        dep[s]=0;
        queue<int> q;
        q.push(s);
        in[s]=true;
        while(!q.empty()){
            int t=q.front();
            q.pop();in[t]=false;
            for(int i=head[t];i;i=nxt[i]){
                int v=E[i].v;
                int flow=E[i].flow;
                int cost=E[i].cost;
                if(flow&&dep[t]+cost<dep[v]){
                    dep[v]=dep[t]+cost;
                    if(!in[v]){
                        in[v]=true;
                        q.push(v);
                    }
                }
            }
        }
        return dep[t]<2000000000;
    }
    int ans=0;
    int dfs(int cur,int mini){
        vis[cur]=true;
        if(cur==t){
            ans+=mini;
            return mini;
        }
        int fl=0;
        for(int i=pos[cur];i;i=nxt[i]){
            pos[cur]=i;
            int v=E[i].v;
            int flow=E[i].flow;
            int cost=E[i].cost;
            if(flow&&(dep[cur]+cost==dep[v]&&(!vis[v]||v==t))){
                int tmp=dfs(v,min(mini-fl,flow));
                if(tmp){
                    E[i].flow-=tmp;
                    E[i^1].flow+=tmp;
                    fl+=tmp;
                    if(fl==mini)return fl;
                }
            }
        }
        return fl;
    }
    int dinic(){
        while(SPFA()){
            vis[t]=true;
            while(vis[t]){
                for(int i=1;i<=n;i++){
                    vis[i]=false;
                    pos[i]=head[i];
                }
                dfs(s,2e9);
            }
        }
        return ans;
    }
}F;
class B{
    public:
    int dfn[255];
    int low[255];
    int tot;
    int head[255];
    int nxt[200000];
    int E[200000];
    bool vis[200000];
    char Co[200000];
    int belone[255];
    int siz[255];
    int num=0;
    int cnt=1;
    void addedge(int u,int v,char c){
        cnt++;
        nxt[cnt]=head[u];
        head[u]=cnt;
        E[cnt]=v;
        Co[cnt]=c;
        return;
    }
    void tarjan(int cur,int fa){
        // printf("%d\n",cur);
        dfn[cur]=low[cur]=++tot;
        for(int i=head[cur];i;i=nxt[i]){
            int v=E[i];
            if(v==fa)continue;
            if(!dfn[v]){
                tarjan(v,cur);
                low[cur]=min(low[cur],low[v]);
                if(low[v]>dfn[cur]){
                    vis[i]=vis[i^1]=true;
                }
            }
            else{
                low[cur]=min(low[cur],dfn[v]);
            }
        }
        return;
    }
    void find(int cur){
        siz[num]++;
        belone[cur]=num;
        for(int i=head[cur];i;i=nxt[i]){
            int v=E[i];
            if(belone[v])continue;
            if(vis[i])continue;
            find(v);
        }
        return;
    }
}G;
bool ans[100000];
int main(){
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    scanf("%d%d%d%d",&r,&g,&b,&m);
    n=r+g+b+1;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&E[i].u,&E[i].v);
        cin>>E[i].col;
        ljb[E[i].u].push_back(E[i].v);
        ljb[E[i].v].push_back(E[i].u);
        G.addedge(E[i].u,E[i].v,E[i].col);
        G.addedge(E[i].v,E[i].u,E[i].col);
    }
    G.tarjan(1,0);
    // for(int i=1;i<=n;i++){
    //     printf("%d %d\n",G.dfn[i],G.low[i]);
    // }
    // for(int i=2;i<=G.cnt;i++)
    //     printf("%d %d\n",G.E[i],G.vis[i]);
    //这个时候割边已经出来了，我们需要把边双缩出来，具体的，我们需要把割边加入答案，然后剩下的边参与边双的讨论。。
    for(int i=1;i<=n;i++){
        if(!G.belone[i]){
            G.num++;
            G.find(i);
        }
    }
    for(int i=1;i<=m;i++){
        if(G.vis[2*i]){
            ans[i]=true;
            if(G.Co[2*i]=='r'){
                r--;
            }
            else{
                if(G.Co[2*i]=='g'){
                    g--;
                }
                else{
                    b--;
                }
            }
        }
    }
    if(r<0||g<0||b<0){
        puts("NO");
        return 0;
    }
    // for(int i=1;i<=n;i++){
    //     printf("%d %d\n",i,G.belone[i]);
    // }
    // for(int i=1;i<=G.num;i++){
    //     printf("%d ",G.siz[i]);
    // }
    // puts("");
    // printf("%d %d %d %d\n",r,g,b,G.num);
    F.Add(n+m+G.num+1,n+m+G.num+2,r*2,0);
    F.Add(n+m+G.num+1,n+m+G.num+3,g*2,0);
    F.Add(n+m+G.num+1,n+m+G.num+4,b*2,0);
    for(int i=1;i<=n;i++){
        F.Add(m+i,m+n+G.belone[i],(G.siz[G.belone[i]]>1),-2e9);//那对应的就是1~n。
    }
    for(int i=1;i<=G.num;i++){
        F.Add(m+n+i,m+n+G.num+5,2*(G.siz[i]-1),0);
    }
    //只要这些边全部满流就是满足条件的。
    //也就是前3+n+G.num条边流量全部为0
    //如果只有一个点我直接不连了。。。
    for(int i=1;i<=m;i++){
        if(!G.vis[2*i]){//如果不是割边那就一定参与网络流
            if(E[i].col=='r')F.Add(n+m+G.num+2,i,2,0);
            else if(E[i].col=='g')F.Add(n+m+G.num+3,i,2,0);
            else F.Add(n+m+G.num+4,i,2,0);
        }
    }
    for(int i=1;i<=n;i++){
        if(G.siz[G.belone[i]]>1)F.Add(m+i,m+n+G.belone[i],2e9,0);
    }
    for(int i=1;i<=m;i++){
        if(!G.vis[2*i]){
            F.Add(i,m+E[i].u,1,0);
            F.Add(i,m+E[i].v,1,0);
        }
    }
    F.s=n+m+G.num+1;
    F.t=n+m+G.num+5;
    F.n=n+m+G.num+5;
    F.dinic();
    bool tag=false;
    // printf("%d %d %d\n",r,g,b);
    // for(int i=1;i<=3+n+G.num+m;i++){
    //     printf("%d %d %d\n",i,F.E[i*2].v,F.E[i*2].flow);
    //     // if(F.E[i*2].flow){
    //     //     tag=true;
    //     //     break;
    //     // }
    // }//如果只有一个点那不是寄飞吗。。。。。
    if(tag){
        puts("NO");
        return 0;
    }
    else{
        puts("YES");
        int St=3+n+G.num;
        for(int i=1;i<=m;i++){
            if(!G.vis[2*i]){//如果不是割边那就一定参与网络流
                St++;
                if(!F.E[St*2].flow){
                    ans[i]=true;
                }
            }
        }
        for(int i=1;i<=m;i++){
            // if(ans[i]){
            //     printf("%d %d %c\n",E[i].u,E[i].v,E[i].col);
            // }
            printf("%d",ans[i]);
        }
    }
    return 0;
}
/*
考虑生成树是一个怎么样的结构。

我们的目的就是删掉一定颜色的边使得剩下的是生成树。

实际上这个很难做到吧。。

先缩个边双，那么我们现在只需要关心边双以内的点应该是怎么办，剩下的rgb我们可以直接计算出来。

那现在问题就变成了怎么能够做到一个边双内可能的rgb全部拉出来。

考虑一个边双他一定是好几个环组在一起拿出来的。
我们卡绿从一个点

假设我们能艘出来有意味着什么呢。。。

假设给你一张完全图那不是很多种方案吗，反着删肯定是寄

假设每个都是250那也就三次方，但是这只是一条，实际上那个合并的时候呢是要n方的，然后刚好这里有n个点每个点都有一个像这样的rgb

每个边双你们都有一个这样的rgb，然后合并的时候还要枚举两边的素有的rgb方案数，实际上就是能不能的问题，每次三次方枚举rgb并暴力合并。

这个时间复杂度是n^7，什么都过不了。

暴力合并是做不了的。

倒不如说和合并有关就肯定做不了。

特殊性质A，完全图并且rgb相等，那就好办了，我们考虑完全图的话是不是不需要考虑联通的问题啊，一条边连了就是连了，像这样的？

特殊性质B，只有rg。

还是首先边双，然后两个边双的值怎么能够合并啊，是不是只能枚举。。。

我们显然没有办法合并几个边双之间的信息所以这条路走不通。。

要不就这样：

考虑要生成树的话，我先给所有边定向，然后既然是生成树那么怎么走也都是可以走得到的。

哦好像不对，这好像意味着要取一条边必须取走很多前驱。

哦我们对于每个边双统计边的数量？

显然是不行的。

我首先把rgb锁死，然后把边拿下。

一个边双在所有点都联通的情况下最多这么多条边。。。

那就这样。

首先，我们把边变成点。
然后造三个r点g点b点。
然后连边，然后考虑这些边有一些在同一个边双里面，那就再造一些边双点，然后连过去，最后边双只会带走一些边。

最主要的是每个点都必须被覆盖到。并且一个点只会带走一个。

那就对于一个点我们把他相连的边双里面的边要连向他们两个。

我们要覆盖到每一个点，因为是跑边双。。。

众所周知一条点提供两个度数，所以我们可以限制边数，但是还是要限制每个点都被拿到。

然后每个点都被拿到并且总边数还没有问题，回去检查总边数即可。

然后因为长得像二分图所以应该是m根号m<n^3吧



14 15 4 0
14 16 2 0
14 17 2 0
6 11 1 -2000000000
7 11 1 -2000000000
8 11 1 -2000000000
9 12 1 -2000000000
10 13 1 -2000000000
11 18 4 0
12 18 0 0
13 18 0 0
6 11 2000000000 0
7 11 2000000000 0
8 11 2000000000 0
9 12 2000000000 0
10 13 2000000000 0
1 6 1 0
1 7 1 0
15 1 2 0
2 7 1 0
2 8 1 0
15 2 2 0
3 6 1 0
3 8 1 0
15 3 2 0

这样确实能做到选择但是怎么做到都由一条边来选呢。。。
按理来说搜一次应该就全部搜完了才对阿

我草泥马，跑费用流会因为需要费用然后就直接全部流完啊。。

我们要求的是全部流完，就是要流一条边那么后面的就必须全部流掉不管代价。

如果不减费用我们就踩不到，，，
我们要求的是一个点要踩就两个都踩，但是很明显一条边如果只踩
*/