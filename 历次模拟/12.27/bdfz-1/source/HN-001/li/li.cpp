#include<cstdio>
#include<cctype>
#include<cstdlib>

#define maxn 202202

bool Mbg;

template<class T>

inline T read(){
	T r=0,f=0;
	char c;
	while(!isdigit(c=getchar()))f|=(c=='-');
	while(isdigit(c))r=(r*10)+(c^48),c=getchar();
	return f?-r:r;
}

int n,m,deg[maxn],cnt[maxn][5];

int f[maxn],size[maxn],tot[maxn];

int find(int x){
	return x^f[x]?f[x]=find(f[x]):x;
}

inline bool check(int rt){
	if(size[rt]==tot[rt]){
		if(cnt[rt][2]!=size[rt])
			puts("-1"),exit(0);
		return 1;
	}
	if(size[rt]==1)return 0;
	if(cnt[rt][1]==2&&cnt[rt][2]==size[rt]-2)return 0;
	if(size[rt]==4&&cnt[rt][3]==1&&cnt[rt][1]==3)return 1;
	puts("-1"),exit(0);
}

bool Med;

int main(){
	double Mb=((&Mbg)-(&Med))/1e6;
	fprintf(stderr,"%.2lfMB\n",Mb=Mb<0?-Mb:Mb);
	if(Mb>100)fprintf(stderr,"MLE!!!\n");
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	n=read<int>();
	m=read<int>();
	for(int i=1;i<=n;i++)
		f[i]=i,size[i]=1;
	for(int i=1;i<=m;i++){
		int u=read<int>();
		int v=read<int>();
		deg[u]++,deg[v]++;
		u=find(u),v=find(v);
		if(u!=v){
			f[v]=u,size[u]+=size[v];
			tot[u]+=tot[v];
		}
		tot[u]++;
	}
	for(int i=1;i<=n;i++){
		if(deg[i]>3)return puts("-1"),0;
		cnt[find(i)][deg[i]]++;
	}
	int s=0;
	long long cnt=0,sum=0;
	for(int i=1;i<=n;i++){
		if(f[i]!=i)continue;
		bool o=check(i);
		if(o)s=1,cnt+=tot[i];
		else sum+=size[i]*(size[i]+1ll)/2;
	}
	printf("%d %lld\n",s,s?cnt:sum);
	return 0;
}
