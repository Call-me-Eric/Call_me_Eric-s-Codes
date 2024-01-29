#include<iostream>
#include<cstdio>
using namespace std;

int r,s;//����&����
char map [21][21];

bool letter [26], book[21][21];//�߹�
int maxa = 1;//����������·�� 
int way [4][2] = { {1,0},{0,-1},{-1,0},{0,1}};

void dfs (int x,int y,int step){ 
	if ( step > maxa ) maxa = step;
	for (int i = 0; i<4; i++){
		int xn = x + way [i][0];
		int yn = y + way [i][1];
		if (xn >= 0 && xn < r) { 
			if (yn >= 0 && yn < s) {//�����ж�
				char nl = map [xn][yn] ;
				int  now = nl-65; //ASCII
				if (!letter [now] && book[xn][yn] == 0) { //δ�߹� 
					letter [now] = true; //ռ��˵� 
					book[xn][yn] = 1;
					dfs (xn, yn, step + 1/*����һ��*/);
					book[xn][yn] = 0;
					letter [now] = false;//����
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
	} //��ȷ����ʼ�����쳣�� 
	book[0][0] = 1;
	letter[map[0][0] - 65] = 1;
	dfs (0,0,1);
	cout <<maxa<<endl;
	return 0;
}

