#include<bits/stdc++.h>
#define F(i0,i1,i2) for(int i0=(i1);i0<=(i2);++i0)
#define int long long
#define pii pair<int,int>
#define fr first
#define sc second
using namespace std;
inline int rd(){
	int f=0,x=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return f?-x:x;
}
const int N=5e4+7;
int n,k;
int w[N];
int loc(int x,int y){return (x-1)*n+y;}
struct Id{
	int v,nt;
}e[N<<1];
int p[N],id=1;
void add(int x,int y){e[++id]={y,p[x]};p[x]=id;}
#define vec vector<int>
vec z[N];
int vis[N];
vec dfs(int x){
	if(vis[x])return z[x];
	vis[x]=1;
	for(int i=p[x];i;i=e[i].nt){
		int v=e[i].v;
		vector<int>t;
		t=dfs(v);
		for(int j:t)z[x].push_back(j);
	}
	if(z[x].size())sort(z[x].begin(),z[x].end(),greater<int>());
	while(z[x].size()&&z[x].size()>k)z[x].pop_back();
	if(!p[x])z[x].push_back(w[x]);
	else for(int &i:z[x])i+=w[x];
	return z[x];
}
signed main(){
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
	n=rd(),k=rd();
	F(i,1,n)F(j,1,i){
		w[loc(i,j)]=rd();
		if(i!=n)add(loc(i,j),loc(i+1,j));
		if(i!=n)add(loc(i,j),loc(i+1,j+1));
	}
	dfs(1);
	cout<<z[1][k-1]<<'\n';
	return 0;
}
/*
3 4
1
2 3
3 3 1

*/

