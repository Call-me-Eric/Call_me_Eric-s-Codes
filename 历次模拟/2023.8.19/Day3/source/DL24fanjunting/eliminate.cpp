#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
vector<int>vec[maxn];
int c[maxn];
int maxx=0;
int maxid;
signed main(){
	freopen("eliminate.in","r",stdin);
	freopen("eliminate.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c[i];
		if(c[i]>maxx){
			maxid=i;
			maxx=c[i];
		}
		for(int j=1;j<=c[i];j++){
			int y;
			cin>>y;
			vec[i].push_back(y);
		}
	}
	for(int i=1;i<=n;i++){
		sort(vec[i].begin(),vec[i].end());
//		for(int j=0;j<c[i];j++){
//			cout<<vec[i][j]<<" ";
//		}
//		cout<<'\n';
	}
//	return 0;
	int jicha=0;
	int ans=0x7fffffff;
	int minn=0,maxx=0;
	for(int i=0;i<c[maxid];i++){
		minn=vec[maxid][i];
		maxx=vec[maxid][i];
		for(int j=1;j<=n;j++){
			if(j==maxid) continue;
			int l=0,r=c[j]-1;
			while(l<=r){
				int mid=(l+r)>>1;
				if(vec[j][mid]>vec[maxid][i]){
					r=mid-1;
				}
				else{
					l=mid+1;
				}
			}
			cout<<r<<'\n';	
			if(r==-1){
				jicha=max(jicha,vec[j][0]-vec[maxid][i]);
				continue;
			}
			if(r==c[j]-1){
				jicha=max(jicha,vec[j][r]-vec[maxid][i]);
				continue;
			}
			jicha=max(jicha,max(abs(vec[j][r]-vec[maxid][i]),abs(vec[j][r+1]-vec[maxid][i])));
		}
		ans=min(jicha,ans); 
	}
	cout<<ans;
	return 0;
}

