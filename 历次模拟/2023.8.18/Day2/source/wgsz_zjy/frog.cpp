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
const int N=5e3;
struct Node{
	int a,b,c,d,e,f,id,ord;
	bool operator>=(const Node &_)const{
		return a>=_.a&&b>=_.b&&c>=_.c&&d>=_.d&&e>=_.e;
	}
}a[N];
int n;
int dp[N];
void Dp(){
	F(i,1,n)dp[i]=a[i].f;
	for(int i=1;i<=n;i++){
		int tmp=0;
		for(int j=i-1;j>=1;j--){
			if(a[i]>=a[j]){
//				cout<<i<<" "<<j<<'\n';
				tmp=max(tmp,dp[j]);
			}
		}
		dp[i]+=tmp;
	}
}
signed main(){
	freopen("frog.in","r",stdin);
	freopen("frog.out","w",stdout);
	n=rd();
	F(i,1,n){
		a[i].a=rd(),a[i].b=rd(),a[i].c=rd(),a[i].d=rd(),a[i].e=rd(),a[i].f=rd();
		a[i].id=i;
	}
	Dp();
	F(i,1,n)cout<<dp[i]<<'\n';
	return 0;
}
