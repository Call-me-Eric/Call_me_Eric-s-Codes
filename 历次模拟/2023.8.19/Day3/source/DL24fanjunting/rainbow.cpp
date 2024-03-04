#include<bits/stdc++.h>
using namespace std;
int n,m;
const int maxn=2e3+5;
int p[maxn][maxn];
bool checkk[maxn];
bool check(int xl,int yl,int xr,int yr){
//	cout<<"yes0"<<'\n';
	if((xl==xr)&(yl==yr)) return 0;
	if((xl>n)|(yl>m)|(xr>n)|(yr>m)){
		return 0;
	}
	int now=p[xl][yl];
	for(int i=xl;i<=xr;i++){
		for(int j=yl;j<=yr;j++){
			now=p[i][j];
			for(int k=1;k<=min(xr-xl,yr-yl);k++){
				if((i+k>xr)|(j+k>yr)) continue;
				if(p[i+k][j+k]!=now){
//					cout<<"yes1"<<'\n';
					return 0;
				}
			}	
		}
		
	}
	
	for(int i=xl;i<=xr;i++){
		int noww=p[i][yl];
		for(int j=yl;j<=yr;j++){
			if(j==yl) continue;
//			cout<<"hhh"<<" "<<yl<<" "<<yr<<" "<<i<<" "<<j<<" "<<noww<<" "<<p[i][yl]<<" "<<p[i][j]<<'\n';
			if(p[i][j]==noww) 
			{
//				cout<<"yes2"<<'\n';
			return 0;
			}
		}	
	}
	for(int i=yl;i<=yr;i++){
		int noww=p[xl][i];
		for(int j=xl;j<=xr;j++){
			if(j==xl) continue;
			if(p[j][i]==noww){
//				cout<<"yes3"<<'\n';
				return 0;
			} 
		}	
	}
//	cout<<xl<<" "<<yl<<" "<<xr<<" "<<yr<<'\n';
	return 1;
}
signed main(){
	freopen("rainbow.in","r",stdin);
	freopen("rainbow.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>p[i][j];
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=0;k<n;k++){
				for(int l=0;l<m;l++){
//					cout<<i<<" "<<j<<" "<<k+i<<" "<<l+j<<'\n';
					ans+=check(i,j,k+i,l+j);
				}
			}
		}
	}
	cout<<ans;
	return 0;
}

