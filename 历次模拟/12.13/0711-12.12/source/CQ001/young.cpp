#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a),i##END=(b);i<=i##END;i++)
#define Rof(i,b,a) for(int i=(b),i##END=(a);i>=i##END;i--)
#define go(u) for(int i=head[u];i;i=nxt[i])
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=15,p=998244353;
int n,m,k;
vector<int> A,B;
map<vector<int>,int> ma[N],mb[N];
inline void add(int &a,int b){((a+=b)>=p)&&(a-=p);}
void print(vector<int> o){
	for(int x:o)printf("%d ",x);puts("");
}
void dfs(int dep,vector<int> o){
	for(auto x:o)assert(x>0);
	int l=o.size();
	For(i,0,l-2)assert(o[i]>=o[i+1]);
	vector<int> t=o;
	ma[dep][o]++;
	if(dep==k)return;
	For(i,0,l-1){
		if(i==0||o[i]+1<=o[i-1])
			o[i]++,dfs(dep+1,o),o[i]--;
	}o.push_back(1),dfs(dep+1,o),o.pop_back();
	For(i,0,l-2){
		if(o[i]-1>=o[i+1]){
			o[i]--,dfs(dep+1,o),o[i]++;
		}
	}o[l-1]--;if(!o.back())o.pop_back();
	dfs(dep+1,o);
}
signed main(){
	freopen("young.in","r",stdin);
	freopen("young.out","w",stdout);
	For(i,1,n=read())A.push_back(read());
	For(i,1,m=read())B.push_back(read());
	read(),k=read();
	int ta=k/2,tb=(k+1)/2;
	assert(ta+tb==k);
	
	ma[0][A]=1,mb[0][B]=1;
	
	For(T,1,ta){
		for(auto x:ma[T-1]){
			vector<int> o=x.first;int c=x.second;
			int l=o.size();
			For(i,0,l-1){
				if(i==0||o[i]+1<=o[i-1])
					o[i]++,add(ma[T][o],c),o[i]--;
			}o.push_back(1),add(ma[T][o],c),o.pop_back();
			For(i,0,l-2){
				if(o[i]-1>=o[i+1]){
					o[i]--,add(ma[T][o],c),o[i]++;
				}
			}if(l){
				o[l-1]--;if(!o.back())o.pop_back();
				add(ma[T][o],c);
			}
		}
	}

	
	For(T,1,tb){
		for(auto x:mb[T-1]){
			vector<int> o=x.first;int c=x.second;
			int l=o.size();
			For(i,0,l-2)assert(o[i]>=o[i+1]);
			For(i,0,l-1){
				if(i==0||o[i]+1<=o[i-1])
					o[i]++,add(mb[T][o],c),o[i]--;
			}o.push_back(1),add(mb[T][o],c),o.pop_back();
			For(i,0,l-2){
				if(o[i]-1>=o[i+1]){
					o[i]--,add(mb[T][o],c),o[i]++;
				}
			}if(l){
				o[l-1]--;if(!o.back())o.pop_back();
				add(mb[T][o],c);
			}
		}
	}
	int ans=0;
	for(auto x:ma[ta]){
		add(ans,1ll*x.second*mb[tb][x.first]%p);
	}printf("%d\n",ans);
	return 0;
}
