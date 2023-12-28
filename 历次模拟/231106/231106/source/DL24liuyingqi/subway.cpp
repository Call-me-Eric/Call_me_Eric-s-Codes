#include<bits/stdc++.h>
using namespace std;

#define int long long

const int N=10;
const int M=507;
const int V=1007;

const int MAXW=2e6+7;

bool st;

int to[MAXW],nxt[MAXW],head[MAXW],val[MAXW],cnt;

int n,t;
int a[N][M],b[N][M];
int P[N];
int L[N];

mt19937 rnd(random_device{}()^time(0));

void add(int u,int v,int w){
//	printf("%lld %lld %lld\n",u,v,w);
	to[++cnt]=v,nxt[cnt]=head[u],val[cnt]=w,head[u]=cnt;
}
int pt;
int e[10][1007][1007];

struct node{
	int id,dis;
	friend bool operator < (node a,node b){return a.dis>b.dis;}
};

int ans=0x3f3f3f3f3f3f3f3f;
int dis[MAXW];
bool vis[MAXW];

bool ed; 

void DJ(){
	memset(dis,100,sizeof dis);memset(vis,0,sizeof vis);
	priority_queue<node> q;
	q.push((node){pt+n+1,0});dis[pt+n+1]=0;
	while(!q.empty()){
		int u=q.top().id;q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=nxt[i]){
			int k=to[i],w=val[i];
			if(dis[k]>dis[u]+w){
				dis[k]=dis[u]+w;q.push((node){k,dis[k]});
			}
		}
	}
}

double c;

signed main(){
//	cerr<<"总空间："<<(&st-&ed)/1024/1024<<"MB"<<endl;
	freopen("subway.in","r",stdin);
	freopen("subway.out","w",stdout);
	c=clock();
	memset(e,-1,sizeof e);
	scanf("%lld%lld",&n,&t);
	for(int i=1;i<=t;i++) P[i]=i;
	for(int i=1;i<=t;i++){
		for(int j=1;j<=n;j++) scanf("%lld",&a[i][j]);
		for(int j=1;j<=n;j++) scanf("%lld",&b[i][j]);
		scanf("%lld",&L[i]);
		for(int j=1;j<=L[i];j++){
			int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
			e[i][u][v]=w,e[i][v][u]=w;
		}
	}
	pt=n*t;
	do{
		if(t>=6) shuffle(P+1,P+1+t,rnd);
		memset(head,-1,sizeof head),cnt=0;
		for(int i=1;i<=t;i++){//PingTai
			for(int j=i;j<=t;j++){
				for(int u=1;u<=n;u++){
					int id=P[j];
					add(pt+i*n+u,j*n+u,a[id][u]);
//					printf("平台 %lld 连向地铁 %lld  代价 %lld\n",i,id,a[id][u]);
				}
			}
		}
		for(int i=1;i<=t;i++){
			for(int j=i+1;j<=t+1;j++){
				for(int u=1;u<=n;u++){
					int id=P[i];
					add(i*n+u,pt+j*n+u,b[id][u]);
//					printf("地铁 %lld 连向平台 %lld  代价 %lld\n",id,j,b[id][u]);
				}
			}
		}
		for(int i=1;i<=t;i++){
			for(int u=1;u<=n;u++){
				for(int v=1;v<=n;v++){
					int id=P[i];
					if(e[id][u][v]!=-1){
						add(i*n+u,i*n+v,e[id][u][v]);
						add(i*n+v,i*n+u,e[id][v][u]);
					}
				}
			}
		}
		DJ();
		for(int i=1;i<=n;i++){
			ans=min(ans,dis[pt+i*n+n]);
		}
//		printf("%lld\n",ans);
		if((clock()-c)/1000>1.85){
//			cerr<<"用时:"<<(clock()-c)/1000<<"S"<<endl;
			printf("%lld\n",ans);
			exit(0);
		}
	}while(next_permutation(P+1,P+1+t));
	printf("%lld\n",ans);
	return 0;
//	cerr<<"用时:"<<(clock()-c)/1000<<"S"<<endl;
}
