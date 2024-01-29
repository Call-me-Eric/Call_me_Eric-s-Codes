#include<iostream>
#include<cstdio>
#include<string>
#include<map>
#include<algorithm>
#include<stack> 
using namespace std;
int t;
int l;
const int N = 10000;
string result[3] = {"No","Yes","ERR"};
string s[10001];
int top = 1;
int stk[1001];
int maxo;
int cntE, cntF;
map<char, int>m;
bool isnum(char c){
	if(c <= '9' && c >= '0')return 1;
	else return 0;
}
int check(int time){
	int righttime = 0,x ,y;
	x = y = cntE = maxo = cntF = 0;
	top = 1;
	char c = 0;
	int flag = 0;
	m.clear();
	for(int i = 1;i <= 1000;i++)stk[i] = 0;
	for(int i = 1;i <= l;i++){
		x = y = 0;
		if(s[i][0] == 'F'){
			cntF++;
			stk[top++] = i;
			c = s[i][2];
			if(m[c] == 1){
				return 2;
			}
			else m[c] = 1;
			int j = 4;
			if(s[i][j] != 'n'){
				x = s[i][j++] - '0';
				if(isnum(s[i][j]))x = x * 10 + (s[i][j++] - '0');//因为只有两位数 
			}
			else x = N,j++;
			j++;
			if(s[i][j] != 'n'){
				y = s[i][j++] - '0';
				if(isnum(s[i][j]))y = y * 10 + (s[i][j++] - '0');//因为只有两位数 
			}
			else y = N,j++;
			j = 0; 
			if(flag == 0){
				if(y - x < 0){
					flag = top;
				}
				else if(y - x >= 1000){
					righttime++;
					maxo = max(maxo,righttime);
				}
			}
		}
		else if(s[i][0] == 'E'){
			cntE++;
			if(flag == 0 && righttime > 0){
				righttime--;
			}
			m[s[stk[top - 1] ][2] ] = 0;
			top--;
			if(top < 1)return 2;
			if(top == flag)flag = 0;
		}
	}
	if(cntF != cntE)return 2;
	else return maxo == time;
}
int main(){
	scanf("%d",&t);
	while(t){
		t--;
		for(int i = 1;i <= 10000;i++)s[i].clear();
		scanf("%d ",&l);
		int time = 0;
		getchar();getchar();
		char c = getchar();
		if(c == 'n'){
			getchar();
			c = getchar();
			time = c - '0';
			c = getchar();
			if(c != ')'){
				time = time * 10 + (c - '0');
				getchar();
			}
		}
		else {
			time = 0;
			getchar();
		}
		getchar(); 
		for(int i = 1;i <= l;i++){
			getline(cin,s[i]);
		}
		cout << result[check(time)] << endl;
	}
	return 0;
}

