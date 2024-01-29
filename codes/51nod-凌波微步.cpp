//http://class.51nod.com/Classes/Problem.html#courseProblemId=1725&classId=129
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
long long nether[10][2];
long long e[10][10];
int main(){
	for(int i = 1;i <= 8;i++){
		scanf("%lld%lld",&nether[i][0],&nether[i][1]);
	}
	for(int i = 1;i <= 8;i++){
		for(int j = 1;j <= 8;j++){
			e[i][j] = abs(nether[i][0] - nether[j][0]) + abs(nether[i][1] - nether[j][1]);
		}
	}
	if(e[3][4] > 10)
		e[3][4] = e[4][3] = 10;
	if(e[5][6] > 10)
		e[5][6] = e[6][5] = 10;
	if(e[7][8] > 10)
		e[7][8] = e[8][7] = 10;
	for(int k = 1;k <= 8;k++){
		for(int i = 1;i <= 8;i++){
			for(int j = 1;j <= 8;j++){
				if(e[i][j] > e[i][k] + e[k][j])
					e[i][j] = e[i][k] + e[k][j];
			} 
		}
	}
	printf("%lld",e[1][2]);
	return 0;
}

