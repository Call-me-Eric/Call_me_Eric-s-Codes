#include<bits/stdc++.h>
using namespace std;
int n,m,u[1000001],v[1000001],d[1000001],k,ans,cnt,ucnt,num[1000001],p;pair<int,int>id[1000001];long long anss=0;
int main(){
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	cin>>n>>m;for(int i=1;i<=m;i++)scanf("%d%d",&u[i],&v[i]),d[u[i]]++,d[v[i]]++,id[i]={u[i],v[i]};cnt=m;num[0]=n;
	int f=1;for(int i=1;i<=n;i++){
		if(!d[i])k++;
		else if(d[i]!=2)f=0;
	}n-=k;
	if(n<m)cout<<-1,exit(0);
	if(n==m){
		if(f)cout<<1<<" "<<n<<endl;
		else cout<<-1;
		return 0;
	}
	if(n>m){
		n+=k;
		cout<<0<<" ";
		while(n!=0){
			num[++p]=n=cnt;
			for(int i=1;i<=n;i++){
				for(int j=i+1;j<=n;j++){
					if(id[i].first==id[j].second||id[j].first==id[i].second||id[i].second==id[j].second||id[i].first==id[j].first)u[++ucnt]=i,v[ucnt]=j;
				}
			}
			m=cnt=ucnt;ucnt=0;
			for(int i=1;i<=m;i++)id[i]={u[i],v[i]};
		}
		for(int i=0;i<=p;i++)anss+=num[i];
		cout<<anss;
	}
}
