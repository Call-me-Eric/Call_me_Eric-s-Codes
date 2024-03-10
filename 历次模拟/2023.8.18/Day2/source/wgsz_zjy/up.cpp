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
const int N=1e5+7;
pii a[N];
int n,q;
int dfs(int x,int y,int a,int b){
//	cout<<x<<' '<<y<<' '<<a<<" "<<b<<'\n';
	while(x>=a&&y>=b){
//		cout<<x<<' '<<y<<' '<<'\n';
		if((a-x)%y==0&&(b-y)%x==0){
//			cout<<x<<' '<<y<<" "<<a<<' '<<b<<'\n';
			return 1;	
		}
		if(x<y){
			if(y%x==0)y=x;
			else y=y%x;
		}
		else if(x>y){
			if(x%y==0)x=y;
			else x=x%y;
		}
		else if(x==y){
			if(a<b)x-=y;
			else y-=x;
		}
	}
//	cout<<x<<' '<<y<<" "<<a<<' '<<b<<'\n';
	return 0;
}
int solve(int x,int y){
	int cnt=0;
	F(i,1,n){
		cnt+=dfs(a[i].fr,a[i].sc,x,y);
	}
	return cnt;
}
signed main(){
	freopen("up.in","r",stdin);
	freopen("up.out","w",stdout);
	n=rd(),q=rd();
	F(i,1,n)a[i].fr=rd(),a[i].sc=rd();
	F(i,1,q){
		int x=rd(),y=rd();
		cout<<solve(x,y)<<'\n';
	}
	return 0;
}


