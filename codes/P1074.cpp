#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 9;
int a[100][100];
int cnt[100];
int x[100][100], y[100][100], z[100][100];
int nextline[100];
struct cntt{
	int cnt0,line;
}node[100];
struct cmp{
	bool operator ()(cntt a,cntt b){
		return a.cnt0 < b.cnt0;
	}
};
int ans = -1;
int u;
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
int score[10][10] = {
0,0,0,0,0,0 ,0,0,0,0,
0,6,6,6,6,6 ,6,6,6,6,
0,6,7,7,7,7 ,7,7,7,6,
0,6,7,8,8,8 ,8,8,7,6,
0,6,7,8,9,9 ,9,8,7,6,
0,6,7,8,9,10,9,8,7,6,
0,6,7,8,9,9 ,9,8,7,6,
0,6,7,8,8,8 ,8,8,7,6,
0,6,7,7,7,7 ,7,7,7,6,
0,6,6,6,6,6 ,6,6,6,6
};
int sum(){
    int tmp = 0;
    for (int i = 1;i <= 9;i++){
        for (int j = 1;j <= 9;j++){
            tmp += score[i][j] * a[i][j];
		}
	}
    return tmp;
}
void dfs(int i,int j,int cnt){
	if(cnt > u){
		ans = max(ans,sum());
		return;
	}
	if(j > 9){
		dfs(nextline[i],1,cnt);
		return;
	}
	if(a[i][j]){
		dfs(i,j + 1,cnt);
		return;
	}
	for(int k = 1;k <= N;k++){
		if(!(x[i][k] || y[j][k] || z[gong[i][j]][k])){
			x[i][k] = y[j][k] = z[gong[i][j]][k] = 1;
			a[i][j] = k;
			dfs(i, j + 1, cnt + 1);
			x[i][k] = y[j][k] = z[gong[i][j]][k] = 0;
			a[i][j] = 0;
		}
	}
	return;
}
int main(){
	for(int i = 1;i <= N;i++){
		node[i].line = i;
		for(int j = 1;j <= N;j++){
			scanf("%d",&a[i][j]);
			if(a[i][j] > 0){
				x[i][a[i][j]] = y[j][a[i][j]] = z[gong[i][j]][a[i][j]] = 1;
			}
			else{
				node[i].cnt0++;
				u++;
			}
		}
	}
	sort(node + 1,node + 10, cmp());
	for(int i = 1;i < N;i++){
		nextline[node[i].line] = node[i + 1].line;
	}
	dfs(node[1].line,1,1);
	printf("%d",ans);
	return 0;
}
