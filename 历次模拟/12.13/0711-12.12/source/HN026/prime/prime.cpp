#include <cstdio>
#include <algorithm>
#include <cstring>
#include <bitset>
#define bset vis[p][c1][c2][c3]
using namespace std;
const int N=100003;
char sl[N],sr[N];
namespace Trie{
	const int O=60;
	int tr[O][10],cnt=1;
	int stk[10],tp;
	bool ed[O];
	void ins(int x){
		int p=1;
		tp=0;
		while(x) stk[++tp]=x%10,x/=10;
		while(tp){
			int c=stk[tp--];
			if(!tr[p][c]) tr[p][c]=++cnt;
			p=tr[p][c];
		}
		ed[p]=1;
	}
}
const int P=998244353;
int f[N][60][2][2][2];
bitset<N> vis[60][2][2][2];
int n,tc;char *s;
void inc(int &x,int v){if((x+=v)>=P) x-=P;}
int dfs(int x,int p,bool c1,bool c2,bool c3){
	//printf("%d %d %d %d %d\n",x,p,c1,c2,c3);fflush(stdout);
	if(x<0) return c2;
	if(bset[x]) return f[x][p][c1][c2][c3];
	bset.set(x);
	int res=0;
	for(int c=0;c<10;++c){
		if(c1&&c>(s[x]^48)) continue;
		if(c==2||c==3||c==5||c==7) continue;
		int np=Trie::tr[p][c];
		bool nc3=c3&&(c%3==0);
		inc(res,dfs(x-1,np,c1&&(c==(s[x]^48)),(c2&&(c%2==0))||Trie::ed[np]||nc3,nc3));
	}
	return f[x][p][c1][c2][c3]=res;
}
int solve(){
	int ans=dfs(n-1,1,1,1,1);
	for(int p=0;p<=Trie::cnt;++p)
		for(int c1=0;c1<2;++c1)
			for(int c2=0;c2<2;++c2)
				for(int c3=0;c3<2;++c3){
					for(int i=bset._Find_first();i<n;i=bset._Find_next(i))
						f[i][p][c1][c2][c3]=0;
					bset.reset();
				}
	return ans;
}
int main(){
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	Trie::ins(1);Trie::ins(91);Trie::ins(649);Trie::ins(901);
	Trie::ins(949);Trie::ins(981);Trie::ins(6049);Trie::ins(6649);
	Trie::ins(9081);Trie::ins(9469);Trie::ins(9801);
	Trie::ins(60049);Trie::ins(66049);Trie::ins(66649);Trie::ins(94669);
	Trie::ins(600049);Trie::ins(660049);Trie::ins(666049);
	Trie::ins(6000049);Trie::ins(6600049);Trie::ins(6660049);Trie::tr[1][0]=1;
	Trie::ins(49);Trie::ins(81);
	Trie::tr[Trie::tr[1][4]][6]=Trie::tr[1][4];
	Trie::tr[Trie::tr[1][8]][0]=Trie::tr[1][8];
	scanf("%d",&tc);
	while(tc--){
		scanf("%s%s",sl,sr);
		int nl=strlen(sl);
		int nr=strlen(sr);
		reverse(sl,sl+nl);
		reverse(sr,sr+nr);
		n=nr;s=sr;
		int res=solve();
		int p=0;
		while(sl[p]=='0') sl[p++]='9';
		--sl[p];
		while(nl&&sl[nl-1]=='0') --nl;
		n=nl;s=sl;
		res-=solve();
		if(res<0) res+=P;
		printf("%d\n",res);
	}
	return 0;
}
