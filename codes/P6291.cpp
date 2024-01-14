#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 1e3 + 10;
const int dx[8] = {-3,-2, 0, 2, 3, 2, 0,-2};
const int dy[8] = { 0, 2, 3, 2, 0,-2,-3,-2};
int a[10][10];
void dfs(int x,int y,int cnt){
	if(cnt == 26){
		if(a[3][3] != 25)return;
		for(int i = 1;i <= 5;i++)
			for(int j = 1;j <= 5;j++)
				printf("%c%2d%s",",{"[j == 1],a[i][j],j == 5 ? "},\n" : "");
		puts("");
		exit(0);
	}
	for(int i = 0;i < 8;i++){
		int nx = x + dx[i], ny = y + dy[i];
		if(nx < 1 || nx > 5 || ny < 1 || ny > 5 || a[nx][ny])continue;
		a[nx][ny] = cnt;
		dfs(nx,ny,cnt + 1);
		a[nx][ny] = 0;
	}
}
void preworkfunction(){
	freopen("tmp.out","w",stdout);
	a[1][1] = 1;dfs(1,1,2);
	fclose(stdout);
}
int table[8][6][6] = {
	{//出发点（右上in中下out）
		{ 1, 8, 5, 2, 9},
		{16,13,22,19,14},
		{ 6, 3,10, 7, 4},
		{ 0,20,15, 0,21},
		{17,12,23,18,11}
	},
	{//奇数结束点（中左上in中心out）
		{25,12,19,24, 2},
		{17, 7, 4,14, 8},
		{20,23, 1,11,22},
		{ 5,13,18, 6, 3},
		{16,10,21,15, 9}
	},
	{//中心in左方out
		{ 9,17,24, 8, 2},
		{22,12, 4,19,13},
		{25, 7, 1,16, 6},
		{10,18,23,11, 3},
		{21,15, 5,20,14}
	},
	{//中心in上方out
		{ 9,22,25, 8, 2},
		{17,12, 4,20,15},
		{24, 7, 1,23, 6},
		{10,21,16,11, 3},
		{18,13, 5,19,14}
	},
	{//中心in右方out
		{22,14, 7,23, 2},
		{ 9,19, 4,12,18},
		{ 6,24, 1,15,25},
		{21,13, 8,20, 3},
		{10,16, 5,11,17}
	},
	{//中心in下方out
		{ 6,22,14, 7, 2},
		{19, 9, 4,20,12},
		{24,16, 1,23,15},
		{ 5,21,13, 8, 3},
		{18,10,25,17,11}
	},
	{//n=5特判
		{ 1,16,19, 2,15},
		{11,22, 5,12,21},
		{18, 8,25,17, 7},
		{ 4,13,20, 3,14},
		{10,23, 6, 9,24}
	},
	{//偶数结束点
		{15, 5,11,14, 6},
		{21,18, 8,24,19},
		{10,13, 1, 4,12},
		{16,25,20,17, 7},
		{22, 3, 9,23, 2}
	}
};

//0特殊st，1特殊ed，2左，3上，4右，5下
int n, m;
int res[maxn / 5][maxn / 5][2];//[0]=typ,[1] = id
void DEBUG(){
	for(int i = 1;i <= m;i++)
		for(int j = 1;j <= m;j++)
			printf("%d%c",res[i][j][0]," \n"[j == m]);
	
	for(int i = 1;i <= m;i++)
		for(int j = 1;j <= m;j++)
			printf("%d%c",res[i][j][1]," \n"[j == m]);
}
int ans[maxn][maxn];
signed main(){
#ifndef ONLINE_JUDGE
	freopen("out.out","w",stdout);
#endif
//	preworkfunction();
	n = read();m = n / 5;int add1 = 0;
	if(m & 1){
		if(m == 1){
			for(int i = 1;i <= n;i++)
				for(int j = 1;j <= n;j++)
					printf("%d%c",table[6][i - 1][j - 1]," \n"[j == n]);
			return 0;
		}
		int x = 1, y = 1, id = 1;
		while(x <= m){res[x][y][0] = 5;res[x][y][1] = id;id++;x++;}
		id--;x--;
		while(1){
			while(y <= m){res[x][y][0] = 4;res[x][y][1] = id;id++;y++;}
			y--;res[x][y][0] = 3;x--;
			if(x == 2)break;
			while(y >= 2){res[x][y][0] = 2;res[x][y][1] = id;id++;y--;}
			y++;res[x][y][0] = 3;x--;
		}
		for(int i = m;i >= 2;i--){
			if(i & 1){
				res[2][i][0] = 3;
				res[1][i][0] = 2;
			}
			else{
				res[2][i][0] = 2;
				res[1][i][0] = 5;
			}
			res[2][i][1] = id + !(i & 1);
			res[1][i][1] = id + (i & 1);
			id += 2;
		}
		res[1][1][0] = 0;res[2][2][0] = 1;
		add1 = -2;
//		DEBUG();
	}
	else{
		int x = 1, y = 1, id = 1;
		while(x <= m){res[x][y][0] = 5;res[x][y][1] = id;id++;x++;}
		id--;x--;
		while(1){
			while(y <= m){res[x][y][0] = 4;res[x][y][1] = id;id++;y++;}
			y--;res[x][y][0] = 3;x--;
			while(y >= 2){res[x][y][0] = 2;res[x][y][1] = id;id++;y--;}
			y++;res[x][y][0] = 3;x--;
			if(x == 0)break;
		}
		res[1][2][0] = 7;res[1][1][0] = 0;
		add1 = -2;
	}
	for(int i = 1;i <= m;i++){
		for(int j = 1;j <= m;j++){
			int x = (i - 1) * 5 + 1, y = (j - 1) * 5 + 1, add = (res[i][j][1] - 1) * 25;
			if(i != 1 || j != 1)add += add1;
			for(int q = 0;q < 5;q++){
				for(int p = 0;p < 5;p++){
					ans[x + q][y + p] = add + table[res[i][j][0]][q][p];
				}
			}
		}
	}
	ans[4][1] = n * n;ans[4][4] = n * n - 1;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++)
			printf("%d%c",ans[i][j]," \n"[j == n]);
	return 0;
}
