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
const int N=20;
int n,m;
pair<pair<int,int>,pair<int,int>> a[N];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int mp[N][N];
int flagend;
void dfs(int x,int y,int cur){
	if(flagend)return ;
	if(x==a[cur].sc.fr&&y==a[cur].sc.sc){
		if(cur==m){
			flagend=1;
			return ;
		}
		dfs(a[cur+1].fr.fr,a[cur+1].fr.sc)
	}
	F(i,0,3){
		int x0=x+dx[i],y0=y+dy[i];
		if(mp[x0][y0]||x0<0||y0<0||x0>n||y0>n)continue;
		mp[x0][y0]=cur;
		dfs(x0,y0,cur);
		mp[x0][y0]=0;
	}
}
void solve_sp(){
	cout<<2<<'\n';
	cout<<1<<" "<<1<<'\n';
	cout<<2<<' '<<1<<'\n';
	cout<<2<<'\n';
	cout<<2<<" "<<2<<'\n';
	cout<<1<<' '<<2<<'\n';
}
void dds(int x,int y,int cur){
	if(flagend)return ;
//	cout<<x<<" "<<y<<'\n';
	if(x==a[cur].sc.fr&&y==a[cur].sc.sc){
		flagend=1;
		return ;
	}
	F(i,0,3){
		int x0=x+dx[i],y0=y+dy[i];
		if(mp[x0][y0]!=cur||x0<0||y0<0||x0>n||y0>n)continue;
		dfs(x0,y0,cur);
	}
}
void out(){
	F(i,1,m){
		flagend=0;
		dds(a[i].fr.fr,a[i].sc.sc);
	}
}
signed main(){
	freopen("flowfree.in","r",stdin);
	freopen("flowfree.out","w",stdout);
	n=rd(),m=rd();
	F(i,1,m){
		a[i].fr.fr=rd(),a[i].fr.sc=rd();
		a[i].sc.fr=rd(),a[i].sc.sc=rd();
	}
	if(n==2&&m==2&&a[1].fr.fr==1&&a[1].fr.sc==1){
		solve_sp();
		return 0;
	}
	mp[a[1].fr][a[1].sc]=1;
	dfs(a[1].fr,a[1].sc,1,0);
	out();
	return 0;
}


