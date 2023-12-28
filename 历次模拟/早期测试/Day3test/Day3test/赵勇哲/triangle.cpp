#include<bits/stdc++.h>
#define ll double
using namespace std;
inline ll read(){
	ll x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 1e6 + 10;
int n, K = 10;
ll ans = 1e9 * 4;
struct NODE{
	ll x, y;
}node[maxn];
struct cmp{
	bool operator () (NODE a, NODE b){
		if(a.x != b.x)return a.x < b.x;
		else return a.y < b.y;
	}
};
ll tri(int i,int j,int k){
	return sqrt( (node[i].x - node[j].x) * (node[i].x - node[j].x) + (node[i].y - node[j].y) * (node[i].y - node[j].y) )
		  +sqrt( (node[k].x - node[j].x) * (node[k].x - node[j].x) + (node[k].y - node[j].y) * (node[k].y - node[j].y) )
		  +sqrt( (node[i].x - node[k].x) * (node[i].x - node[k].x) + (node[i].y - node[k].y) * (node[i].y - node[k].y) );
}
void calc(int arg){
	for(int i = 1;i <= n;i++){
		const double x = node[i].x,y = node[i].y;
		node[i].x = cos(arg) * x - sin(arg) * y;
		node[i].y = sin(arg) * x + cos(arg) * y;
	}
	sort(node + 1,node + 1 + n,cmp());
	for(int i = 1;i <= n;i++){
		for(int j = i + 1;j <= n && j <= i + K;j++){
			if(node[j].y - node[i].y > ans)break;
			for(int k = j + 1;k <= n && k <= j + K;k++){
				if(node[k].y - node[j].y > ans)break;
				ans = min(ans,tri(i,j,k));
			}
		}
	}
}
signed main(){
//	freopen("triangle.in","r",stdin);
//	freopen("triangle.out","w",stdout);
	srand(time(0));
	scanf("%d",&n);
	for(int i  = 1;i <= n;i++){
		node[i].x = read();
		node[i].y = read();
	}
	calc(rand() % 360);
	calc(rand() % 360);
	printf("%.6lf\n",ans);
	return 0;
}

