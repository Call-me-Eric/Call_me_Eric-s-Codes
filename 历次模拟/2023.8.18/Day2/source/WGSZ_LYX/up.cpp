#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fr first
#define sc second
inline int rd(){
	int f=1,tmp=0;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		tmp=tmp*10+(ch-'0');
		ch=getchar();
	}
	return tmp*f;
}
const int N=5e4+10,M=1e6+10;
int n,q;
int a[N],b[N],cnt;
multiset<pii> st[M];
map<pii,int> mp1,mp2;
bitset<N> flg;
signed main(){
	freopen("up.in","r",stdin);
	freopen("up.out","w",stdout);
	n=rd();q=rd();
	for(int i=1;i<=n;i++){
		a[i]=rd();b[i]=rd();
		while(a[i]&&b[i]){
			if(a[i]<=b[i]){
				if(!mp1.count({a[i],b[i]%a[i]}))mp1[{a[i],b[i]%a[i]}]=++cnt;
				int res=mp1[{a[i],b[i]%a[i]}];
				st[res].insert({b[i],i});
				b[i]%=a[i];
			}else{
				if(!mp2.count({b[i],a[i]%b[i]}))mp2[{b[i],a[i]%b[i]}]=++cnt;
				int res=mp2[{b[i],a[i]%b[i]}];
				st[res].insert({a[i],i});
				a[i]%=b[i];
			}
		}
	}
	while(q--){
		int x=rd(),y=rd(),ans=0;
		flg.reset();
		if(mp1.count({x,y%x})){
			int res=mp1[{x,y%x}];
			for(pii i:st[res]){
				if(i.fr>=y){
					if(!flg[i.sc]){
						flg.set(i.sc);
						ans++;
					}
				}
			}
		}
		if(mp2.count({y,x%y})){
			int res=mp2[{y,x%y}];
			for(pii i:st[res]){
				if(i.fr>=x){
					if(!flg[i.sc]){
						flg.set(i.sc);
						ans++;
					}
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}

