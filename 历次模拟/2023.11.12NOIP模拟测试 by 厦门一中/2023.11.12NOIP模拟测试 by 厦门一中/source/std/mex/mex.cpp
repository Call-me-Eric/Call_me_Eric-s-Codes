#include<bits/stdc++.h>
using namespace std;
const int inf=1000002;
int n,m,zzp1,zzp2,p;
int fa[1000006];
int mx[1000006];
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}

priority_queue<int,vector<int>,greater<int> >q;
int tag[1000006];
unsigned long long ans=0;

int main(){
	freopen("mex.in","r",stdin);
	freopen("mex.out","w",stdout);
	scanf("%d %d %d %d %d",&n,&m,&zzp1,&zzp2,&p);
	for (int i=1;i<=inf;i++) tag[i]=1,fa[i]=mx[i]=i,q.push(i);
	for (int i=1;i<=n;i++){
		int u,v; 
		if (i<=m) scanf("%d %d",&u,&v);
		else u=(ans*i^zzp1)%p+1, v=(ans*i^zzp2)%p+1;
		u=min(u,inf),v=min(v,inf);
		int _u=find(u),_v=find(v);
		if (_u==_v){
			tag[mx[_u]]^=1;
			if (tag[mx[_u]]) q.push(mx[_u]);
		}else{
			if (mx[_u]<mx[_v]) swap(mx[_u],mx[_v]);
			tag[mx[_u]]^=(tag[mx[_v]]^1);
			tag[mx[_v]]=0;
			fa[_v]=_u;
			if (tag[mx[_u]]) q.push(mx[_u]);
		}
		while (!tag[q.top()]) q.pop();
		ans=(ans^(1ll*q.top()*i));
	}
	printf("%llu",ans);
	return 0;
}
