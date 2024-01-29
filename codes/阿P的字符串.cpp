#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
string A,B;
string from[11],to[11];
string book[100001];
int tot = 1,len = 0;
int ans = -1;
int head, tail = -1;
struct queueue{
	int step;
	string s;
}que[100001];
string check(string a,int i,int j){
	if(i + from[j].length() > a.length()){
		return "";
	}
	for(int k = 0;k < a.length();k++){
		if(a[i + k] != from[j][k])return "";
	}
	string tmp = a.substr(0,i);
	tmp.append(to[j] + a.substr(i + from[j].length()));
	return tmp;
}
bool finding(string a){
	for(int i = 1;i <= len;i++){
		if(a[0] == book[i][0]){
			if(a[1] == book[i][1]){
				if(a == book[i]){
					return 1;
				}
				continue;
			}
			continue;
		}
	}
	return 0; 
}
void bfs(){
	que[head].step = 0;
	que[head].s = A;
	while(head > tail){
		queueue temp;
		temp = que[++tail];
		if(finding(temp.s) == 1)continue;
		if(temp.step > 10){
			return;
		}
		if(temp.s == B){
			cout << temp.step << endl;
			exit(0);
		}
		book[++len] = temp.s;
		for(int i = 0;i < temp.s.length() ;i++){
			for(int j = 1;j <= tot;j++){
				string tmp = check(temp.s,i,j);
				if(!tmp.empty()){
					head++;
					que[head].s = tmp;
					que[head].step = temp.step + 1;
				}
			}
		}
	}
	return;
}
int main(){
	cin >> A >> B;
	getchar();
	while(cin >> from[tot] >> to[tot])getchar(),tot++;
	tot--;
	bfs();
	puts("NO ANSWER!");
	cout << A;
	cout << B;
	for(int i = 1;i <= tot;i++){
		cout << from[i] << endl << to[i] << endl;
	}
	return 0;
}

