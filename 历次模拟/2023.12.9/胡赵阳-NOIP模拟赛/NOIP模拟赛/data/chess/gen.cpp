#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
unsigned int seed;
const int T[10]={1,2,3,4,5,5,6,6,7,7};
char s[15][15];
int main(){
	scanf("%u",&seed);
	mt19937 rng(seed);
	for(int ID=0;ID<10;ID++){
		FILE *I=fopen((to_string(ID)+".in").c_str(),"w");
		int t=100,x=rng()%t,y=rng()%t,z=rng()%t;
		fprintf(I,"%d\n",t);
		while (t--){
			for(int i=1;i<=10;i++)
				for(int j=1;j<=9;j++)s[i][j]='*';
			if (T[ID]>6){
				for(int i=0;i<5;i++)s[rng()%10+1][rng()%9+1]='b';
				for(int i=0;i<5;i++)s[rng()%10+1][rng()%9+1]='B';
			}
			if (T[ID]>5){
				for(int i=0;i<2;i++)s[rng()%10+1][rng()%9+1]='p';
				for(int i=0;i<2;i++)s[rng()%10+1][rng()%9+1]='P';
			}
			if (T[ID]>4){
				for(int i=0;i<2;i++)s[rng()%10+1][rng()%9+1]='m';
				for(int i=0;i<2;i++)s[rng()%10+1][rng()%9+1]='M';
			}
			if (T[ID]>3){
				for(int i=0;i<2;i++)s[rng()%10+1][rng()%9+1]='c';
				for(int i=0;i<2;i++)s[rng()%10+1][rng()%9+1]='C';
			}
			if (T[ID]>2){
				for(int i=0;i<2;i++)s[rng()%5+1][rng()%9+1]='x';
				for(int i=0;i<2;i++)s[rng()%5+6][rng()%9+1]='X';
			}
			if (T[ID]>1){
				for(int i=0;i<2;i++)s[rng()%3+1][rng()%3+4]='s';
				for(int i=0;i<2;i++)s[rng()%3+8][rng()%3+4]='S';
			}
			if ((t!=x)&&(t!=y)&&(t!=z)){
				s[rng()%3+1][rng()%3+4]='j';
				s[rng()%3+8][rng()%3+4]='J';
			}
			else{
				int j=rng()%3+4,l=rng()%3+1,r=rng()%3+8;
				s[l][j]='j',s[r][j]='J';
				for(int i=l+1;i<r;i++)s[i][j]='*';
			}
			for(int i=1;i<=10;i++)fprintf(I,"%s\n",s[i]+1);
		}
		fclose(I);
		system(("chess < "+to_string(ID)+".in > "+to_string(ID)+".ans").c_str());
	}
	return 0;
}
