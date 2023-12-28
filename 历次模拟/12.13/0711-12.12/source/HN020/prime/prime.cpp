//Code by juju527.
#include<bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
#define pii pair<int,int>
#define fi first
#define se second
#define vec vector<int>
#define eb emplace_back
using namespace std;
ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*y;
}
const int P[]={2,3,5,7,11,19,41,61,89,409,449,499,881,991,6469,6949,9001,9049,9649,9949,60649,666649,946669,60000049,66000049,66600049};
const int maxn=105;
int tot,t[maxn][10];
bool tag[maxn];
int cnt;
map<lll,int> mp;
const lll one=1;
const int maxs=2e5+5;
int trans[maxs][10];
int dfs(lll s){
	if(mp[s])return mp[s];
	mp[s]=++cnt;
	int id=cnt;
	for(int i=0;i<10;i++){
		lll st=s;bool op=0;
		for(int x=0;x<=tot;x++){
			if(!((s>>x)&1))continue;
			if(t[x][i])st|=(one<<t[x][i]),op|=tag[t[x][i]];
		}
		if(op){trans[id][i]=0;continue;}
		trans[id][i]=dfs(st);
	}
	return id;
}
const int mod=998244353;
inline int add(int x){return (x>=mod)?x-mod:x;}
inline void add(int &x,int y){x=add(x+y);return ;}
inline int sub(int x){return (x<0)?x+mod:x;}
int buf[25];
int f[maxs][2],g[maxs][2];
int calc(ll lim){
	if(!lim)return 1;
	ll aux=lim;int n=0;
	while(aux)buf[n++]=aux%10,aux/=10;
	for(int i=0;i<=cnt;i++)f[i][0]=f[i][1]=g[i][0]=g[i][1]=0;
	f[1][1]=1;
	for(int i=n-1;i>=0;i--){
		for(int s=1;s<=cnt;s++){
			if(!f[s][0]&&!f[s][1])continue;
			for(int c=0;c<10;c++){
				add(g[trans[s][c]][0],f[s][0]);
				if(c<buf[i])add(g[trans[s][c]][0],f[s][1]);
				else if(c==buf[i])add(g[trans[s][c]][1],f[s][1]);
			}
		}
		for(int s=1;s<=cnt;s++)f[s][0]=g[s][0],f[s][1]=g[s][1],g[s][0]=g[s][1]=0;
	}
	int res=0;
	for(int s=1;s<=cnt;s++)add(res,add(f[s][0]+f[s][1]));
	return res;
}
int main(){
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	for(int i=0;i<26;i++){
		int x=P[i],c=0;
		while(x)buf[c++]=x%10,x/=10;
		int u=0;
		for(int k=c-1;k>=0;k--){
			if(!t[u][buf[k]])t[u][buf[k]]=++tot;
			u=t[u][buf[k]];
		}
		tag[u]=1;
	}
	dfs(1);
	int T;
	T=read();
	while(T--){
		ll l,r;
		l=read(),r=read();
		printf("%d\n",sub(calc(r)-calc(l-1)));
	}
	return 0;
}
