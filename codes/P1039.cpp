#include<map>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
using namespace std;
string name[10001];
string speaker[20001], words[20001];
int TF[10001];
string weeks[10];
map<string,int>id;
int n, m, p;
int ans = 0;
	int T = 0, F = 0;
bool judgeTF(int i,bool flag){
	if(TF[i] == -1){
		TF[i] = flag;
		if(flag) 
			++T;
		else 
			++F;
	}
	else
		return TF[i] != flag; 
	if(F > n || T > m - n)
		return 1;
	return 0;
}
void check(int killer,int day){
	T = F = 0;
	for(int i = 1;i <= p;i++){
		string tmp;
		int pos = words[i].find("I am guilty.");
		if(~pos){
			if(judgeTF(id[speaker[i]],id[speaker[i]] == killer))
				return;
		}
		pos = words[i].find("I am not guilty.");
		if(~pos){
			if(judgeTF(id[speaker[i]],id[speaker[i]] != killer))
				return;
		}
		pos = words[i].find(" is guilty.");
		if(~pos){
			tmp = words[i];
			tmp.erase(pos,11);
			if(judgeTF(id[speaker[i]],id[tmp] == killer))
				return;
		}
		pos = words[i].find(" is not guilty.");
		if(~pos){
			tmp = words[i];
			tmp.erase(pos,15);
			if(judgeTF(id[speaker[i]],id[tmp] != killer))
				return;
		}
		pos = words[i].find("Today is ");
		if(~pos){
			if(judgeTF(id[speaker[i]],words[i] == weeks[day]))
				return;
		}		
	}
	if(ans && ans != killer){
		cout << "Cannot Determine" << endl;
		exit(0);
	}
	ans = killer;
}
int main(){
	weeks[1] = "Today is Monday.";
	weeks[2] = "Today is Tuesday.";
	weeks[3] = "Today is Wednesday.";
	weeks[4] = "Today is Thursday.";
	weeks[5] = "Today is Friday.";
	weeks[6] = "Today is Saturday.";
	weeks[7] = "Today is Sunday.";
	scanf("%d%d%d",&m,&n,&p);
	getchar();
	for(int i = 1;i <= m;i++){
		getline(cin,name[i]);
		id[name[i]] = i;
	}
	name[0] = "Impossible";
	for(int i = 1;i <= p;i++){
		cin >> speaker[i];
		speaker[i].erase(speaker[i].length() - 1,1);//È¥Ã°ºÅ
		getline(cin,words[i]);
		words[i].erase(0,1); 
		if(words[i][words[i].length() - 1] == '\n' || words[i][words[i].length() - 1] == '\r'){
			words[i].erase(words[i].end() - 1);//È¥\n»ò\r 
		}
	}
	for(int i = 1;i <= m;i++){
		for(int j = 1;j <= 7;j++){
			for(int k = 1;k <= m;k++)TF[k] = -1;
			check(i,j);
		}
	}
	cout << name[ans] << endl;
	return 0;
} 
