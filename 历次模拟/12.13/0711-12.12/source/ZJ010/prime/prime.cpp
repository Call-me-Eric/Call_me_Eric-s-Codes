#include <bits/stdc++.h>
#define rep(i,j,k) for(int i = (j);i <= (k);i++)
#define per(i,j,k) for(int i = (j);i >= (k);i--)
#define ll __int128
#define ull unsigned long long
#define mod 998244353
#define mkp make_pair
#define eb emplace_back
using namespace std;
int a[25] = {11,19,41,61,89,449,499,409,881,991,6469,6949,9649,9949,9049,9001,60649,666649,946669,66600049,66000049,60000049};
int tab[6] = {0,1,4,6,8,9},fr[10] = {0,1,-1,-1,2,-1,3,-1,4,5};

int cnt;
int nxt[105][6];
ll msk,P[70];
map <ll,int> I;
int N;
queue <ll> Q;

int k;
int b[15];
void insert(int x){
	k = 0;
	while(x){
		b[++k] = x % 10;
		x /= 10;
	}
	reverse(b + 1,b + k + 1);
	int u = 0;
	rep(i,1,k){
		if(!nxt[u][fr[b[i]]]) nxt[u][fr[b[i]]] = ++cnt;
		u = nxt[u][fr[b[i]]];
	}	
	msk |= P[u];
}
int trans[150005][6];
int spcheck(int val){
	int u = 1;
	k = 0;
	while(val){
		b[++k] = val % 10;
		val /= 10;
	}
	per(i,k,1){
		if(fr[b[i]] == -1 || !trans[u][fr[b[i]]]) return 0;
		u = trans[u][fr[b[i]]];
	}
	return 1;
}


mt19937_64 rnd(0);
map <ull,int> buc;
int m,label[150005],strans[150005][6];
ull val[150005];

int TEST,n;
char s[100005];

int f[150005],g[150005];
inline void add(int &x,int y){
	x += y;
	if(x >= mod) x -= mod;
}

int calc(){
	memset(g,0,sizeof(g));
	int cur = label[1];
	rep(pos,1,n){
		rep(u,1,N){
			rep(c,0,5){
				if(trans[u][c]) add(f[trans[u][c]],g[u]);
			}
		}
		if(cur){
			rep(c,0,5) if(tab[c] < s[pos] - '0') add(f[trans[cur][c]],1);
			if(fr[s[pos] - '0'] == -1) cur = 0;
			else cur = trans[cur][fr[s[pos] - '0']];
		}
		copy(f,f + N + 1,g);
		fill(f,f + N + 1,0);
	}
	int res = (cur != 0);
	rep(u,1,N) add(res,g[u]);
//	printf("calc %d\n",res);
	return res;
}

void solve(){
	scanf("%s",s + 1);
	n = strlen(s + 1);
	int ret = -calc();
	int u = label[1],flg = 1;
	rep(i,1,n){
		if(fr[s[i] - '0'] == -1 || !trans[u][fr[s[i] - '0']]){
			flg = 0;
			break;
		}
		u = trans[u][fr[s[i] - '0']];
	}
	ret += flg;

	scanf("%s",s + 1);
	n = strlen(s + 1);
	ret += calc();
	ret %= mod;
	if(ret < 0) ret += mod;
	printf("%d\n",ret);
}
int deg[150005];
vector <int> G[150005];

int main(){
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	P[0] = 1;
	rep(i,1,69) P[i] = 2 * P[i - 1];
	for(int i = 0;a[i];i++) insert(a[i]);
	Q.push(1);I[1] = ++N;
//	cerr << nxt[0][0] << endl;
	while(!Q.empty()){
		ll S = Q.front();
		Q.pop();
		int id = I[S];
		rep(i,0,5){
			ll T = S;
			rep(u,0,cnt) if((S & P[u]) && nxt[u][i]) T |= P[nxt[u][i]];
			if(T & msk) continue;
			if(I[T]){
				trans[id][i] = I[T];
				continue;
			}
			I[T] = ++N;
			trans[id][i] = N;
			Q.push(T);
		}
	}
	rep(u,1,N){
		rep(i,0,5){
			if(trans[u][i] && trans[u][i] != u){
				deg[u]++;
				G[trans[u][i]].eb(u);
			}
		}
	}
	rep(u,1,N) if(!deg[u]) Q.push(u);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int v:G[u]){
			deg[v]--;
			if(!deg[v]) Q.push(v);
		}
		ull temp = 0;
		rep(i,0,5){
			if(!trans[u][i]) continue;
			if(trans[u][i] != u) temp ^= val[label[trans[u][i]]];
			else temp ^= 1;
		}
		if(!buc[temp]){
			buc[temp] = ++m;
			val[m] = rnd();
		}
		label[u] = buc[temp];		
	}

	rep(u,1,N){
		rep(i,0,5) strans[label[u]][i] = label[trans[u][i]];
	}
	rep(u,1,m){
		rep(i,0,5) trans[u][i] = strans[u][i];
	}
	N = m;
/*	rep(u,1,10){
		rep(c,0,5) printf("%d ",trans[u][c]);
		printf("\n");
	}
	cerr << N << endl;*/
		
	scanf("%d",&TEST);
	while(TEST--) solve();
	return 0;
}
//g++ prime.cpp -o prime -Wall -Wshadow -O2 -std=c++14 -Wno-unused-result