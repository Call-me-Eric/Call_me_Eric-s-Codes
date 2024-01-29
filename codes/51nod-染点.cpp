#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
vector<int> e[51];
int ans;
int n;
bool book[51];
char c;
char s[51][51];
int que[100001];
int head, tail;
int main(){
	scanf("%d",&n);
	for(int i = 0;i < n;i++){
		scanf("%s",s[i]);
		for(int j = 0;j < n;j++){
			c = s[i][j];
			if(i != j && c == 'N'){
				e[i].push_back(j);
			}
		}
	}
	for(int i = 0;i < n;i++){
		if(book[i])continue;
		if(e[i].size() == 0){
			book[i] = 1;
			ans++;
		}
		else if(e[i].size() == 1){
			book[e[i][0]] = 1;
			book[i] = 1;
			ans++;
		}
		else{
			int u = e[i][0],v = e[i][1];
			if(s[u][v] == 'N'){
				book[i] = book[u] = book[v] = 1;
				ans++;
			}
			else {
				if(book[u] == 0){
					book[u] = book[i] = 1;
					ans++;
				}
				else if(book[v] == 0){
					book[v] = book[i] = 1;
					ans++;
				}
				else {
					book[i] = 1;
					ans++;
				}
			}
		}
	}
	printf("%d",ans);
	return 0;
}

