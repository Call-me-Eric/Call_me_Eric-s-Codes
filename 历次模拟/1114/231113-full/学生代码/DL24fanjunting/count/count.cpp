#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define ob pop_back
#define mkp make_pair 
using namespace std;
int ans=0;
int n;
int a[20];
int b[20];
vector<int>g;
const int mod=998244353;
int cnt[20];
int ksm(int x,int k){
	int base=x,res=1;
	while(k){
		if(k&1) res=res*base%mod;
		base=base*base%mod;
		k>>=1;
	}
	return res;
}
bool check(){
	unordered_map<int,int>mp;
	map<pair<int,int>,int>mp2;
	map<pair<int,int>,int>mp3;
//	if(g[0]!=1||g[1]!=1||g[2]!=3) return 0;
//	cout<<mp[1]<<" "<<mp[2]<<" "<<mp[3]<<'\n';
	for(int i=1;i<=g.size();i++){
		if(mp3[mkp(min(a[i],b[i]),max(a[i],b[i]))]&&(mp[a[i]]||mp[b[i]])) return 1;
		if(mp3[mkp(min(a[i],g[i-1]),max(a[i],g[i-1]))]&&(mp[a[i]]||mp[g[i-1]])) return 1;
		if(mp3[mkp(min(b[i],g[i-1]),max(b[i],g[i-1]))]&&(mp[b[i]]||mp[g[i-1]])) return 1;	
//		if(g[0]==1&&g[1]==1&&g[2]==3) cout<<"yes"<<'\n';
		if(a[i]==b[i]){
//			cout<<"yes1";
//			if(a[i]!=g[i-1]) mp3[mkp(min(a[i],g[i-1]),max(a[i],g[i-1]))]=1;
			
//			if(mp2[mkp(g[i-1],a[i])]) return 1;
			mp[a[i]]++;
			
			if(a[i]!=g[i-1]) mp2[mkp(a[i],g[i-1])]=1;
			
			if(mp[a[i]]>=2) return 1;
			
			continue;
		}
		
		if(b[i]==g[i-1]){
//			cout<<"yes2";
//			if(a[i]!=b[i]) mp3[mkp(min(b[i],g[i-1]),max(b[i],g[i-1]))]=1;
//			if(mp2[mkp(a[i],b[i])]) return 1;
			mp[b[i]]++;
			if(b[i]!=a[i]) mp2[mkp(b[i],a[i])]=1;
			if(mp[b[i]]>=2) return 1;
			continue;
		}
	
		if(a[i]==g[i-1]){
//			cout<<"yes3";
//			if(a[i]!=b[i]) mp3[mkp(min(a[i],b[i]),max(a[i],b[i]))]=1;
//			if(mp2[mkp(b[i],a[i])]) return 1;
			mp[g[i-1]]++;
			if(a[i]!=b[i]) mp2[mkp(a[i],b[i])]=1;
			if(mp[g[i-1]]>=2) return 1;
			continue;
		}	
//		if(mp3[mkp(min(a[i],b[i]),max(a[i],b[i]))]) return 1;
//		if(mp3[mkp(min(a[i],g[i-1]),max(a[i],g[i-1]))]) return 1;
//		if(mp3[mkp(min(b[i],g[i-1]),max(b[i],g[i-1]))]) return 1;
		mp3[mkp(min(a[i],b[i]),max(a[i],b[i]))]=1;
		mp3[mkp(min(b[i],g[i-1]),max(b[i],g[i-1]))]=1;
		mp3[mkp(min(a[i],g[i-1]),max(a[i],g[i-1]))]=1;
		int now=0;
		if(mp[a[i]]>=1) now++;
		if(mp[b[i]]>=1) now++;
		if(mp[g[i-1]]>=1) now++;

//		cout<<now<<'\n';
		if(now>=2) return 1;
	}
	if(mp3[mkp(min(a[n],b[n]),max(a[n],b[n]))]&&(mp[a[n]||mp[b[n]]])) return 1;
	if(mp3[mkp(min(a[n],g[n-1]),max(a[n],g[n-1]))]&&(mp[a[n]]||mp[g[n-1]])) return 1;
	if(mp3[mkp(min(b[n],g[n-1]),max(b[n],g[n-1]))]&&(mp[b[n]]||mp[g[n-1]])) return 1;
//	cout<<g[0]<<" "<<g[1]<<" "<<g[2]<<'\n';
//	cout<<mp[1]<<" "<<mp[2]<<" "<<mp[3]<<'\n';
//	exit(0);
	return 0;
}
void dfs(int x){
	if(x>n){
		if(check()) ans++;
		return;
	}
	for(int i=1;i<=n;i++){
//		if(a[x]==i||b[x]==i){
//			if(cnt[i]){
//				ans+=ksm(n,n-x);
//				continue;
//			}
//			else{
//				cnt[i]++;
//				g.pb(i);
//				dfs(x+1);
//				g.ob();
//				cnt[i]--;
//			}
//		}
//		else{
			g.pb(i);
			dfs(x+1);
			g.ob();
//		}
	}
}
signed main(){
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	dfs(1);
	cout<<ans;
	return 0;
}

