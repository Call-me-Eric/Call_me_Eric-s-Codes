#include<bits/stdc++.h>
using namespace std;
int n, m, k;
const int maxn = 510;
int a[maxn][maxn];
bool revnm = false;
queue<pair<int,int> > firsthand, secondhand;
void printans(){
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++){
			if(a[i][j] == 1){firsthand.push(make_pair(i,j));}
			else secondhand.push(make_pair(i,j));
		}
	for(int cnt = 1, now = 0;cnt <= n * m;cnt++,now ^= 1){
		if(!now){
			int u = firsthand.front().first,v = firsthand.front().second;firsthand.pop();
			if(revnm)swap(u, v);
			printf("%d %d\n",u,v);
		}
		else{
			int u = secondhand.front().first,v = secondhand.front().second;secondhand.pop();
			if(revnm)swap(u, v);
			printf("%d %d\n",u,v);
		}
	}
	exit(0);
}
signed main(){
	freopen("gomoku.in","r",stdin);
	freopen("gomoku.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	if(n > m){revnm = true;swap(n, m);}
	if(k == 1){puts("-1");exit(0);}
	if(n == 1){
		for(int i = 1,hand = 1;i <= m;i++,hand = 3 - hand){a[1][i] = hand;}
		printans();
	}
	if(k == 2){puts("-1");exit(0);}
	if(k > n){
		if(m & 1){
			for(int i = 1,hand = 1;i < m;i++,hand = 3 - hand)
				for(int j = 1;j <= n;j++){a[j][i] = hand;}
			for(int j = 1,hand = 1;j <= n;j++,hand = 3 - hand)a[j][m] = hand;
		}
		else{
			for(int i = 1,hand = 1;i <= m;i++,hand = 3 - hand)
				for(int j = 1;j <= n;j++){a[j][i] = hand;}
		}
		printans();
	}
	for(int i = 1;i <= m;i += 4){
		for(int j = 1,hand = 1;j <= n;j++,hand = 3 - hand){
			a[j][i] = a[j][i + 1] = hand;
			a[j][i + 2] = a[j][i + 3] = 3 - hand;
		}
	}
	if((n & 1) && (m % 4 == 2)){a[n][m - 1] = 2;}
	printans();
	return 0;
}
