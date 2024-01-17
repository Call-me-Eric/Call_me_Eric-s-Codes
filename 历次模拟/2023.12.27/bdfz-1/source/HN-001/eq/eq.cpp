#include<cstdio>
#include<cctype>
#include<vector>
#include<algorithm>

#define maxn 777

const int mod=998244353;

bool Mbg;

template<class T>

inline T read(){
	T r=0,f=0;
	char c;
	while(!isdigit(c=getchar()))f|=(c=='-');
	while(isdigit(c))r=(r*10)+(c^48),c=getchar();
	return f?-r:r;
}

inline long long qpow(long long a,int b){
	long long ans=1;
	for(;b;b>>=1){
		if(b&1)(ans*=a)%=mod;
		(a*=a)%=mod;
	}
	return ans;
}

int n,m;

namespace bf{

	long long a[maxn][maxn],b[maxn][maxn];

	inline void calc(){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n+1;j++)
				a[i][j]=b[i][j];
		for(int i=1;i<=n;i++){
			if(!a[i][i]){
				for(int j=i+1;j<=n;j++)
					if(a[j][i]){
						std::swap(a[i],a[j]);
						break;
					}
			}
			if(!a[i][i])continue;
			long long inv=qpow(a[i][i],mod-2);
			for(int j=1;j<=n;j++){
				if(j==i||!a[j][i])continue;
				long long d=(mod-inv)*a[j][i]%mod;
				for(int k=i;k<=n+1;k++)
					(a[j][k]+=d*a[i][k])%=mod;
			}
		}
	}

	inline void Out(){
		static long long ans[maxn];
		for(int i=n;i;i--){
			long long s=a[i][n+1];
			for(int j=i+1;j<=n;j++)
				(s+=(mod-a[i][j])*ans[j])%=mod;
			if(!a[i][i]){
				if(!s)puts("Many");
				else puts("No");
				return;
			}
			ans[i]=s*qpow(a[i][i],mod-2)%mod;
		}
		for(int i=1;i<=n;i++)
			printf("%lld%c",ans[i]," \n"[i==n]);
	}

	inline void work(){
		int x=read<int>();
		for(int i=1;i<=n+1;i++)
			b[x][i]=read<int>();
		calc(),Out();
	}

	inline void solve(){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n+1;j++)
				b[i][j]=read<int>();
		calc(),Out();
		while(m--)work();
	}

}

namespace luangao{

	int tot,id[maxn],L[maxn<<1],R[maxn<<1];

	int c[maxn<<1][maxn];

	inline int get(){
		tot++;
		for(int i=1;i<=n+1;i++)
			c[tot][i]=read<int>();
		return tot;
	}

	int cnt[maxn][maxn],mid[maxn][maxn];

    int S[maxn<<1],f[maxn][maxn];

	int top,rk[maxn],pos[maxn],g[maxn][maxn];

	long long a[maxn][maxn];

	inline bool Add(int x){
		top++;
		for(int i=1;i<=n+1;i++)
			a[top][i]=c[x][i];
		for(int i=1;i<=n;i++){
			int p=pos[i];
			if(!p||!a[top][i])continue;
			long long d=(mod-a[top][i])*qpow(a[p][i],mod-2)%mod;
			for(int k=i;k<=n+1;k++)
				(a[top][k]+=d*a[p][k])%=mod;
		}
		rk[top]=0;
		for(int i=1;i<=n&&!rk[top];i++)
			if(a[top][i])rk[top]=i;
		if(!rk[top])return !a[top][n+1];
		pos[rk[top]]=top;
		int p=rk[top];
		long long inv=qpow(a[top][p],mod-2);
		for(int i=1;i<top;i++){
			g[top][i]=0;
			if(!a[i][p])continue;
			long long d=(mod-a[i][p])*inv%mod;
			for(int k=p;k<=n+1;k++)
				(a[i][k]+=d*a[top][k])%=mod;
			g[top][i]=mod-d;
		}
		return true;
	}

	inline void Del(int lst){
		while(top>lst){
			int p=rk[top];
			if(!p){
				top--;
				continue;
			}
			for(int i=1;i<top;i++){
				long long d=g[top][i];
				if(!d)continue;
				for(int k=p;k<=n+1;k++)
					(a[i][k]+=d*a[top][k])%=mod;
			}
			pos[p]=0,top--;
		}
	}

	inline void Out(){
		static long long ans[maxn];
		for(int i=1;i<=n;i++){
			if(!rk[i]){
				if(!a[i][n+1])puts("Many");
				else puts("No");
				return;
			}
			ans[rk[i]]=a[i][n+1]*qpow(a[i][rk[i]],mod-2)%mod;
		}
		for(int i=1;i<=n;i++)
			printf("%lld%c",ans[i]," \n"[i==n]);
	}

	void dfs(int l,int r,std::vector<int> &vec){
		int lst=top;
		int mid=luangao::mid[l][r];
		std::vector<int> vecl,vecr;
		for(auto x:vec){
			if(L[x]<=l&&R[x]>=r){
			    if(!Add(x)){
					for(int i=l;i<=r;i++)puts("No");
					return Del(lst);
				}
				continue;
			}
			if(L[x]<=mid)vecl.push_back(x);
			if(R[x]>mid)vecr.push_back(x);
		}
		if(l==r)Out();
		else dfs(l,mid,vecl),dfs(mid+1,r,vecr);
		Del(lst);
	}

	inline void work(){
		for(int i=1;i<=n;i++)
			id[i]=get(),L[i]=0;
		for(int i=1;i<=m;i++){
			int x=read<int>();
			R[id[x]]=i-1;
			L[id[x]=get()]=i;
		}
		for(int i=1;i<=n;i++)R[id[i]]=m;
		for(int l=0;l<=m;l++)
			for(int r=l;r<=m;r++)
				for(int i=1;i<=tot;i++)
					if(L[i]<=l&&R[i]>=r)cnt[l][r]++;
		for(int i=1;i<=tot;i++)
			S[i]=i*(i+1)/2;
		for(int i=0;i<=m;i++)mid[i][i]=i;
		for(int p=1;p<=m;p++)
			for(int l=0,r=p;r<=m;l++,r++){
				int pos=-1;
				f[l][r]=1e9;
				for(int k=l;k<r;k++){
				    int val=f[l][k]+f[k+1][r];
					val+=S[cnt[l][k]]+S[cnt[k+1][r]];
					if(val<f[l][r])f[l][r]=val,pos=k;
				}
				f[l][r]-=S[cnt[l][r]]*2;
				mid[l][r]=pos;
			}
		std::vector<int> vec;
		for(int i=1;i<=tot;i++)
			vec.push_back(i);
		dfs(0,m,vec);
	}

}

namespace Luangao{

	int id[maxn],rk[maxn];

	long long a[maxn][maxn],b[maxn][maxn];

	inline void Add(int x,int y,int d){
		for(int i=1;i<=n+1;i++)
			(a[y][i]+=d*a[x][i])%=mod;
		for(int i=1;i<=n;i++)
			(b[y][i]+=d*b[x][i])%=mod;
	}

	inline void init(){
		for(int i=1;i<=n;i++)b[i][i]=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)
				if(!rk[j]&&a[j][i]){
					rk[j]=i,id[i]=j;
					break;
				}
			if(!id[i])continue;
			long long inv=qpow(a[id[i]][i],mod-2);
			for(int j=1;j<=n;j++){
				if(id[i]==j||!a[j][i])continue;
				Add(id[i],j,(mod-inv)*a[j][i]%mod);
			}
		}
	}

	inline void Out(){
		static long long ans[maxn];
		for(int i=1;i<=n;i++){
			if(!a[i][rk[i]]){
				if(!a[i][n+1])puts("Many");
				else puts("No");
				return;
			}
			ans[rk[i]]=a[i][n+1]*qpow(a[i][rk[i]],mod-2)%mod;
		}
		for(int i=1;i<=n;i++)
			printf("%lld%c",ans[i]," \n"[i==n]);
	}

	void update(int x){
		int K=rk[x];
		for(int i=1;i<=n;i++)
			if(id[i]!=x&&a[x][i])
				Add(id[i],x,(mod-a[x][i])*qpow(a[id[i]][i],mod-2)%mod);
		if(!a[x][K])return;
		long long inv=qpow(a[x][K],mod-2);
		for(int i=1;i<=n;i++)
			if(i!=x&&a[i][K])
				Add(x,i,(mod-inv)*a[i][K]%mod);
		update(id[K+1]);
	}

	inline void change(int x){
		long long inv=qpow(b[x][x],mod-2);
		for(int i=1;i<=n;i++){
			if(i==x||!b[i][x])continue;
			Add(x,i,(mod-b[i][x])*inv%mod);
		}
		for(int i=1;i<=n;i++)
			b[x][i]=(x==i);
		for(int i=1;i<=n+1;i++)
			a[x][i]=read<int>();
		update(x);
	}

	inline void work(){
		change(read<int>()),Out();
	}

	inline void solve(){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n+1;j++)
				a[i][j]=read<int>();
		init(),Out();
		while(m--)work();
	}

}

bool Med;

int main(){
	double Mb=((&Mbg)-(&Med))/1e6;
	fprintf(stderr,"%.2lfMB\n",Mb=Mb<0?-Mb:Mb);
	if(Mb>200)fprintf(stderr,"MLE!!!\n");
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	n=read<int>();
	m=read<int>();
	if(1ll*n*n*n*m<=1e9)
		return bf::solve(),0;
	if(m<=100)return luangao::work(),0;
	return Luangao::solve(),0;
	return 0;
}
