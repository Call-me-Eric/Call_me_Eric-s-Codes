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
const int N=2e6+7;
int n,vis[N],num[N];
vector<int>own[N],a[N];
int ord[N],orl,len;
int loc(int x){return lower_bound(ord+1,ord+1+len,x)-ord;}
int solve(){
	int l=0;
	int cnt=0;
	int ans=LONG_LONG_MAX;
	F(r,1,len){
		for(int v:a[r]){
			num[v]++;
			if(!vis[v])cnt++,vis[v]=1;	
		}
		if(cnt==n){
			int flag=1;
			while(flag){
				for(int k:a[l]){
					if(num[k]==1){
						flag=0;
						break;
					}	
				}
				if(flag){
					for(int k:a[l])num[k]--;
					l++;
				}
			}	
		}
		if(cnt==n)ans=min(ans,ord[r]-ord[l]);
	}
	return ans;
}
signed main(){
	freopen("eliminate.in","r",stdin);
	freopen("eliminate.out","w",stdout);
	n=rd();
	F(i,1,n){
		int k=rd();
		F(j,1,k){
			int x=rd();
			own[i].push_back(x);
			ord[++orl]=x;
		}
//		cout<<"OK"<<'\n';
	}
//	cout<<"OK"<<'\n';
	sort(ord+1,ord+1+orl);
	len=unique(ord+1,ord+1+orl)-ord-1;
	F(i,1,n){
		for(int k:own[i]){
			a[loc(k)].push_back(i);
		}
	}
//	cout<<ord[i]<<" ";cout<<'\n';
//	F(i,1,len){
//		for(int v:a[i])cout<<v<<" ";
//		cout<<'\n';
//	}
	cout<<solve()<<'\n';
	return 0;
}


