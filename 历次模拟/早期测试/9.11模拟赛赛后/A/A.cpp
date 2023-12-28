#include<bits/stdc++.h>
using namespace std;
int get(){
	string s;cin>>s;
	int ans=0;
	for(int i=0;i<s.size();i++){
		ans|=(1<<(s[i]-'0'));
	}
	return ans;
}
int dp[1010][1010];
int last[1010][10];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n,k;cin>>n>>k;
		vector<int> a(n+1);
		for(int i=1;i<=n;i++){
			a[i]=get();
		}
		memset(dp,128,sizeof(dp));
		dp[0][0]=0;	
		for(int i=1;i<=n;i++){
			for(int j=0;j<10;j++){
				if(a[i]&(1<<j)){
					last[i][j]=i;
				}else{
					last[i][j]=last[i-1][j];
				}
			}
		}
		for(int i=1;i<=n;i++){
			vector<int> id(10);
			for(int j=0;j<10;j++){
				id[j]=last[i][j];
			}
			sort(id.rbegin(),id.rend());
			for(int ii=0;ii<10;ii++){
				if(id[ii]==0) break;
				for(int kk=0;kk<=k;kk++){
					dp[i][kk]=max(dp[i][kk],dp[i-1][kk]);
					if(kk)dp[i][kk]=max(dp[i][kk],dp[id[ii]-1][kk-1]+ii+1);
				}
			}
		}
		cout<<dp[n][k]<<endl;
	}
	return 0;
}
