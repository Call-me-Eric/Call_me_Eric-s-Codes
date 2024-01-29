#include<cstdio>
#include<cctype>
#include<vector>
#include<bits/extc++.h>

#define maxn 1001001

bool Mbg;

template<class T>

inline T read(){
	T r=0,f=0;
	char c;
	while(!isdigit(c=getchar()))f|=(c=='-');
	while(isdigit(c))r=(r*10)+(c^48),c=getchar();
	return f?-r:r;
}

inline std::vector<int> Fact(int x){
	std::vector<int> vec;
	for(int i=2;i*i<=x;i++){
		if(x%i)continue;
		vec.push_back(i);
		while(!(x%i))x/=i;
	}
	if(x>1)vec.push_back(x);
	return vec;
}

int n,K,ans[maxn];

std::vector<int> vec;

inline void Out(){
	for(int i=0;i<n;i++)
		putchar(ans[i]+'0');
}

namespace bf{

	__gnu_pbds::gp_hash_table<long long,bool> vis;

	long long U,staus[11][44];

	void dfs(long long S){
		auto it=vis.find(S);
		if(it!=vis.end())return;
		for(int i=0;i<n;i++)
			vis[((S<<i)&U)|(S>>(n-i))]=1;
		int now=__builtin_popcountll(S);
		for(int c=0;c<(int)vec.size();c++){
			int p=vec[c],D=n/p;
			if(p+now>K)continue;
			for(int i=0;i<D;i++){
				if(staus[c][i]&S)continue;
				dfs(S|staus[c][i]);
			}
		}
	}

	inline void work(){
		U=(1ll<<n)-1;
		for(int c=0;c<(int)vec.size();c++){
			int p=vec[c],D=n/p;
			for(int i=0;i<D;i++)
				for(int j=0;j<p;j++)
					staus[c][i]|=1ll<<((i+j*D)%n);
		}
		dfs(0);
		int Max=0;
		for(auto P:vis){
			int now=__builtin_popcountll(P.first);
			if(now<=Max)continue;
			Max=now;
			for(int i=0;i<n;i++)
				ans[i]=(P.first >>i)&1;
		}
		Out();
	}

}

bool Med;

int main(){
	double Mb=((&Mbg)-(&Med))/1e6;
	fprintf(stderr,"%.2lfMB\n",Mb=Mb<0?-Mb:Mb);
	if(Mb>100)fprintf(stderr,"MLE!!!\n");
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	n=read<int>();
	K=read<int>();
	if(K==n){
		for(int i=1;i<=n;i++)
			putchar('1');
		return 0;
	}
	vec=Fact(n);
	if(K<=1)return Out(),0;
	for(int c=0;c<(int)vec.size();c++){
		int p=vec[c];
		if(K%p)continue;
		int d=K/p,D=n/p;
		for(int i=0;i<d;i++)
			for(int j=0;j<p;j++)
				ans[(i+j*D)%n]=1;
		return Out(),0;
	}
	if((int)vec.size()==1)
		return Out(),0;
	bf::work();
	return 0;
}
