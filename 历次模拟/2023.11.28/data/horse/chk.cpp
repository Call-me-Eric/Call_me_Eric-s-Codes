#include<bits/stdc++.h>
#include"testlib.h"

#define y1 dmytxdy
#define pb push_back
#define fi first
#define se second
#define mp make_pair

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;

template <typename T> bool chkmin(T &x,T y){return x>y?x=y,1:0;}
template <typename T> bool chkmax(T &x,T y){return x<y?x=y,1:0;}

int readint(){
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

bool vis[5][100005];

int main(int argc,char *argv[]){
	registerTestlibCmd(argc,argv);
	int T=inf.readInt(1,5,"T");
	while(T--){
		int n=inf.readInt(1,100000,"n");
		string str=ouf.readToken();
		if(n==1||n==2||n==4){
			if(str!="No") quitf(_wa,"Wrong Answer.");
			continue;
		}
		if(str!="Yes") quitf(_wa,"Wrong Answer.");
		for(int i=1;i<=4;i++) for(int j=1;j<=n;j++) vis[i][j]=0;
		int lx=-1,ly=-1;
		for(int i=1;i<=4*n;i++){
			int x=ouf.readInt(1,4,"x"),y=ouf.readInt(1,n,"y");
			if(lx<0){
				lx=x,ly=y;
			}
			else{
				if(abs(lx-x)==1&&abs(ly-y)==2);
				else if(abs(lx-x)==2&&abs(ly-y)==1);
				else quitf(_wa,"Wrong Answer");
				lx=x,ly=y;
			}
			if(vis[x][y]) quitf(_wa,"Wrong Answer");
			vis[x][y]=1;
		}
	}
	quitf(_ok,"Correct.");
	return 0;
}
