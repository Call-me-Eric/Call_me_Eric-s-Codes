#include<bits/stdc++.h>
using namespace std;
const int N=255,M=62505;
int n,m,r,g,b,nw,cnt=0;
bool us[M],vis[55][35][35][35],v2[N];
struct stu{int u,v,op;}E[M];
void add(int u,int v,char op){E[++cnt]=(stu){u,v,op=='r'?0:(op=='g'?1:2)};}
void dfs(int x,int rn,int gn,int bn){
	if(x==n){
		cout<<"YES\n";
		for(int i=1;i<=m;i++)
			cout<<us[i];
		exit(0);
	}
	for(int i=1;i<=m;i++){
		bool u=v2[E[i].u],v=v2[E[i].v];
		if((u&&(!v))||((!u)&&v)){
			int k=(!v)?E[i].v:E[i].u;
			int rt=rn,gt=gn,bt=bn;
			if(E[i].op==0)rt++;
			else if(E[i].op==1)gt++;
			else bt++;
			if(rt>r||gt>g||bt>b)continue;
			if(!vis[nw][rt][gt][bt])
				us[i]=1,v2[k]=1,vis[nw][rt][gt][bt]=1,nw|=(1<<(k-2)),
				dfs(x+1,rt,gt,bt),
				us[i]=0,v2[k]=0,vis[nw][rt][gt][bt]=0,nw^=(1<<(k-2));
		}
	}
}
int main(){
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	cin>>r>>g>>b>>m,n=r+g+b+1;
	for(int i=1;i<=m;i++){
		int u,v;char ch;
		cin>>u>>v>>ch,add(u,v,ch);
	}
	v2[1]=1,vis[1][0][0][0]=1,dfs(1,0,0,0);
	cout<<"NO";
	return 0;
}
