#include<bits/stdc++.h>
using namespace std;
const int maxm=1e7+5;
const int maxn=105;
int tong[maxm];
int f[maxn][maxn];
int a[maxn][maxn];
int n,k;
void dfs(int dep,int x,int now){
//	cout<<dep<<" "<<x<<" "<<now<<'\n';
	if(dep==n){
		tong[now]++;
		return;
	}
	dfs(dep+1,x,now+a[dep+1][x]);
	dfs(dep+1,x+1,now+a[dep+1][x+1]);
}
int dfs2(int dep,int x,int cha){
	if(dep==n){
		return cha;
	}
	if(a[dep+1][x]==a[dep+1][x+1]){
		return 0;
	}
	else if(a[dep+1][x]<a[dep+1][x+1]){
		return dfs2(dep+1,x+1,min(cha,a[dep+1][x+1]-a[dep+1][x]));
	}
	else{
		return dfs2(dep+1,x,cha);
	}
}
signed main(){
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			cin>>a[i][j];
		}
	}
	f[1][1]=a[1][1];
	for(int i=2;i<=n;i++){
		for(int j=1;j<=i;j++){
			f[i][j]=max(f[i-1][j-1],f[i-1][j])+a[i][j];
		}
	}
	int ans=0;
	int maxid=0;
	for(int i=1;i<=n;i++){
			if(f[n][i]>ans) maxid=i;
			ans=max(ans,f[n][i]);
	}
	if(k==1){
		
		cout<<ans;
		exit(0);
	}
	if(k==2){
		int chaa=dfs2(1,1,0x7fffffff);
		int ansss=0;
		for(int i=1;i<=n;i++){
			if(i==maxid) continue;
			ansss=max(ansss,f[n][i]);
		}
//		cout<<chaa;
		ansss=max(ansss,f[n][maxid]-chaa);
		cout<<ansss;
		exit(0);
	}
	int now=k;
	int st=n;
	while(now>0){
		st--;
		now-=n;
	}
	for(int i=1;i<=st;i++){
		
		dfs(st,i,f[st][i]);
	}
	int cnt=0;
	int anss=0;
	int noww=ans;
	while(cnt<k){
		cnt+=tong[noww];
//		cout<<noww<<" "<<tong[noww]<<'\n';
		if(tong[noww]) anss=noww;
		noww--;
	
	}
	cout<<anss;
	return 0;
}
//4 2 1 -1 1 -1 -1 1 1 5 1005

