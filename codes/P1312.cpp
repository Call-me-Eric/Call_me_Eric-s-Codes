#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;
int chess_map[10][10];
int ans[10][10];
int mem[10][10][10];
int erasee[10][10];
int n;
void dfs(int);
bool check();
void memory(int);
bool erased();
void fall();
void moved(int,int,int);
//TODO main()
int main(){
	scanf("%d",&n);
	for(int i = 0;i < 5;i++){
		for(int j = 0;j < 8;j++){
			scanf("%d",&chess_map[i][j]);
			if(chess_map[i][j] == 0)break;
		}
	}
	memset(ans,-1,sizeof(ans));
	dfs(0);
	puts("-1");
	return 0;
}
//TODO dfs(int)
void dfs(int x){//ö�ٵ�x�� 
	if(check()){//�ҵ��� 
		for(int i = 0;i < n;i++){
			if(i != 0)putchar('\n');
			for(int j = 0;j < 3;j++){
				printf("%d ",ans[i][j]);
			}
		}
		exit(0);
	}
	
	if(x == n)return;//Խ�� 
	
	memory(x);
	for(int i = 0;i < 5;i++){
		
		for(int j = 0;j < 7;j++){
			
			if(chess_map[i][j]){
			
				if(i + 1 < 5 && chess_map[i][j] != chess_map[i + 1][j]){
					moved(i,j,1);
					ans[x][0] = i;
					ans[x][1] = j;
					ans[x][2] = 1;//��¼��
					dfs(x + 1);
					for(int i = 0;i < 5;i ++){
						for(int j = 0;j < 7;j++){
							chess_map[i][j] = mem[x][i][j];
						}
					}
					ans[x][0] = -1;
					ans[x][1] = -1;
					ans[x][2] = -1;
					//����
				}if(i - 1 >= 0 && chess_map[i - 1][j] == 0){
					moved(i,j,-1);
					ans[x][0] = i;
					ans[x][1] = j;
					ans[x][2] = -1;//��¼��
					dfs(x + 1);
					for(int i = 0;i < 5;i ++){
						for(int j = 0;j < 7;j++){
							chess_map[i][j] = mem[x][i][j];
						}
					}
					ans[x][0] = -1;
					ans[x][1] = -1;
					ans[x][2] = -1;
					//����
				}
			
			}//if(chess_map[i][j]).end
			
		}//for(int j = 0;j < 7;j++).end
		
	}//for(int i = 0;i < 5;i++).end
	
}//void dfs(int x).end
//TODO moved(int,int,int)
void moved(int i,int j,int dir){
	int tmp = chess_map[i][j];
	chess_map[i][j] = chess_map[i + dir][j];
	chess_map[i + dir][j] = tmp;
	fall();
	while(erased())fall();
}
//TODO fall()
void fall(){
	for(int i = 0;i < 5;i++){
		int x = 0;
		for(int j = 0;j < 7;j++){
			if(!chess_map[i][j])x++;
			else{
				if(!x)continue;
				chess_map[i][j - x] = chess_map[i][j];
				chess_map[i][j] = 0;
			}
		}
	}
}
//TODO erased()
bool erased(){
	bool flag = 0;
	for(int i = 0;i < 5;i++){
		for(int j = 0;j < 7;j++){
			if(i - 1 >= 0 && i + 1 < 5 && chess_map[i][j] == chess_map[i - 1][j]
			&& chess_map[i][j] == chess_map[i + 1][j] && chess_map[i][j]){
				erasee[i][j] = erasee[i + 1][j] = erasee[i - 1][j] = 1;
				flag = 1;
			}
			if(j - 1 >= 0 && j + 1 < 7 && chess_map[i][j] == chess_map[i][j - 1]
			&& chess_map[i][j] == chess_map[i][j + 1] && chess_map[i][j]){
				erasee[i][j] = erasee[i][j + 1] = erasee[i][j - 1] = 1;
				flag = 1;
			}
		}
	}
	if(flag == 0)return false;
	for(int i = 0;i < 5;i++){
		for(int j = 0;j < 7;j++){
			if(erasee[i][j]){
				erasee[i][j] = 0;
				chess_map[i][j] = 0;
			}
		}
	}
	return 1;
}
//TODO check()
bool check(){
	for(int i = 0;i < 5;i++){
		if(chess_map[i][0] != 0)return 0;
	}
	return 1;
}
//TODO memory(int)
void memory(int x){
	for(int i = 0;i < 5;i++){
		for(int j = 0;j < 7;j++){
			mem[x][i][j] = chess_map[i][j];
		}
	}
}
