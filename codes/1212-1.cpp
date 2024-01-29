#include<iostream>
#include<cstdio>
using namespace std;

int r,s;//行数&列数
char map [21][21];

bool letter [26], book[21][21];//走过
int maxa = 1;//设置最大可走路径 
int way [4][2] = { {1,0},{0,-1},{-1,0},{0,1}};

void dfs (int x,int y,int step){ 
	if ( step > maxa ) maxa = step;
	for (int i = 0; i<4; i++){
		int xn = x + way [i][0];
		int yn = y + way [i][1];
		if (xn >= 0 && xn < r) { 
			if (yn >= 0 && yn < s) {//出界判断
				char nl = map [xn][yn] ;
				int  now = nl-65; //ASCII
				if (!letter [now] && book[xn][yn] == 0) { //未走过 
					letter [now] = true; //占领此点 
					book[xn][yn] = 1;
					dfs (xn, yn, step + 1/*再走一步*/);
					book[xn][yn] = 0;
					letter [now] = false;//回收
				}
				else 
					continue ;
			
			}
		}
	}
}

int main () {
	cin >>r>>s;
	for (int i = 0 ; i < r ; i++){ 
		scanf ("%s",map [i]);
	} //已确定初始化无异常！ 
	book[0][0] = 1;
	letter[map[0][0] - 65] = 1;
	dfs (0,0,1);
	cout <<maxa<<endl;
	return 0;
}

