#include<bits/stdc++.h>
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=2e5+9;
const int p=998244353;
void chmn(int &x,int y){(x>y)&&(x=y);}
void chmx(int &x,int y){(x<y)&&(x=y);}
int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
int n,m,k;
int a[N],b[N];
map<vector<int>,int>mp1,mp2;
int ans=0;
void dfs(int dep){
	if(dep==k+1){
		int f=1;
		rep(i,100)f&=(a[i]==b[i]);
		ans+=f;
		return;
	}
	rep(i,100){
		a[i]++;
		if(a[i]>=0)if(a[i]<=a[i-1]&&a[i]>=a[i+1])dfs(dep+1);
		a[i]--;
		a[i]--;
		if(a[i]>=0)if(a[i]<=a[i-1]&&a[i]>=a[i+1])dfs(dep+1);
		a[i]++;
	}
}
signed main(){
	//printf("%.5lf\n",(&ppp-&pppp)/1024.0/1024.0);
	freopen("young.in","r",stdin);
	freopen("young.out","w",stdout);
	n=read();rep(i,n)a[i]=read();
	m=read();rep(i,m)b[i]=read();
	int q=read();while(q--){
		k=read();int lim=max(n,m)+k;
		vector<int>A;
		rep(i,lim)A.push_back(a[i]);
		mp1.clear();mp1[A]=1;
		rep(t,k){
			for(auto it:mp1){
				A=it.first;
				For(i,0,lim-1){
					A[i]++;
					if(A[i]>=0)if((i==0||A[i]<=A[i-1])&&(i==lim-1||A[i]>=A[i+1]))(mp2[A]+=it.second)%=p;
					A[i]--;
					
					A[i]--;
					if(A[i]>=0)if((i==0||A[i]<=A[i-1])&&(i==lim-1||A[i]>=A[i+1]))(mp2[A]+=it.second)%=p;
					A[i]++;
				}
			}
			mp1=mp2;mp2.clear();
		}
		A.clear();
		rep(i,lim)A.push_back(b[i]);
		cout<<mp1[A]<<endl;
	}
	return 0;
}
