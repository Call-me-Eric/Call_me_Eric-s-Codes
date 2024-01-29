#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,endline;
int ans = -1;
int gong[10][10] = {
0,0,0,0,0,0,0,0,0,0,
0,1,1,1,2,2,2,3,3,3,
0,1,1,1,2,2,2,3,3,3,
0,1,1,1,2,2,2,3,3,3,
0,4,4,4,5,5,5,6,6,6,
0,4,4,4,5,5,5,6,6,6,
0,4,4,4,5,5,5,6,6,6,
0,7,7,7,8,8,8,9,9,9,
0,7,7,7,8,8,8,9,9,9,
0,7,7,7,8,8,8,9,9,9
};
int score[10][10] ={
{0},
{0,6,6,6,6,6,6,6,6,6},
{0,6,7,7,7,7,7,7,7,6},
{0,6,7,8,8,8,8,8,7,6},
{0,6,7,8,9,9,9,8,7,6},
{0,6,7,8,9,10,9,8,7,6},
{0,6,7,8,9,9,9,8,7,6},
{0,6,7,8,8,8,8,8,7,6},
{0,6,7,7,7,7,7,7,7,6},
{0,6,6,6,6,6,6,6,6,6},};
bool book[10][10],a[10][10],b[10][10],c[10][10];//a=ÐÐ,b=ÁÐ,c=¹¬ 
void dfs(int,int,int,int);
int m[10][10];
struct WAW{
	int sum0;
	int num;
}lll[10];
int k[10];
struct cmp{
	bool operator ()(WAW x,WAW y){
		return x.sum0 < y.sum0;
	}
};
int main(){
	n = 9;
	for(int i = 1;i <= n;i++){
		lll[i].num = i;
		for(int j = 1;j <= n;j++){
			scanf("%d",&m[i][j]);
			int tmp = m[i][j];
			if(m[i][j] == 0){
				lll[i].sum0++;
			}
			else {
				a[i][tmp] = b[j][tmp] = c[gong[i][j]][tmp] = 1;
			}
		}
	}
	sort(lll + 1,lll + 1 + n, cmp());
	k[0] = lll[1].num;
	for(int i = 2;i <= n;i++){
		k[lll[i - 1].num] = lll[i].num;
	}
	endline = lll[n].num;
	dfs(k[0],1,0,0);
	printf("%d",ans);
	return 0;
}
void dfs(int x,int y,int tot,int sum){
	if(tot > 81){
		if(sum > ans)ans = sum;
		return;
	}
	if(y == 10){
		x = k[x];
		y = 1;
	}
	if(book[x][y] == 1 || m[x][y] != 0){
		dfs(x,y + 1,tot + 1,sum);
	}
	for(int i = 1;i <= n;i++){
		if(a[x][i] == 1 || b[y][i] || c[gong[x][y]][i])continue;
		book[x][y] = 1;
		m[x][y] = i;
		dfs(x,y + 1,tot + 1,sum + score[x][y] * i);
		m[x][y] = 0;
		book[x][y] = 0;
	}
	return;
}
