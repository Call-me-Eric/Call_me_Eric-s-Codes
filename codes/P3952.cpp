#include<algorithm>
#include<stack>
#include<cstring>
#include<iostream>
#include<sstream>
#include<string>
#include<cstdio>
#include<map>
using namespace std;
const int N = 9999999;
int n;
string s;
string d[101];
int T;
string result[3] = {"No","Yes","ERR"};
int tonum(string a){
	if(a == "n")return N;
	int k = 0;
	for(int i = 1, n = a.size();i <= n;i++){
		k = k * 10 + (a[i] - '0');
	}
	return k;
}

int cmp(string x, string y){
	int tx = tonum(x), ty = tonum(y);
	if(tx == N)return -1;
	if(tx >= ty)return -1;
	if(y != "n")return 0;
	return 1;
}

int check(int w){
	map<string, int>book;
	book.clear();
	int z = 0, ans = 0, a = 0;
	string F, i, x, y;
	stack<string> k;
	for(int q = 1;q <= n;q++){
		if(d[q][0] == 'E'){
			if(k.empty())return 2;
			else{
				z--;
				book[k.top()] = 0;
				k.pop();
			}
		}
		if(d[q][0] == 'F'){
			stringstream ss(d[q]);
			ss >> F >> i >> x >> y;
			if(book[i] == 1)return 2;
			else{
				k.push(i);
				book[k.top()] = 1;
				if(cmp(x, y) == -1) {
					a++;
					while(a != 0){
						q++;
						if(q > n)return 2;
						if(d[q][0] == 'F'){
							stringstream ss(d[q]);
							ss >> F >> i >> x >> y;
							if(book[i] == 1)return 2;
							else{
								k.push(i);
								book[k.top()] = 1;
							}
							a++;
						}
						else if(d[q][0] == 'E')a--;
					}
					a = 0;
				}
				else if(cmp(x, y) == 1)z++;
			}
		}
		ans = max(z, ans);
	}
	if(k.empty()) return ans == w ? 1 : 0;
	else return 2;
}

int gettime(string t){
	if(t[2] == '1')return 0;
	int w = 0;
	for(int i = 4;t[i] != ')';i++){
		w = w * 10 + (t[i] - '0');
	}
	return w;
}

int main(){
	scanf("%d",&T);
	while(T--){
		s.clear();
		for(int i = 1;i <= 100;i++)d[i].clear();
		string res;
		scanf("%d ",&n);
		getline(cin, s);
		int w = gettime(s);
		for(int i = 1;i <= n;i++){
			getline(cin, d[i]);
		}
//		cout << n << ' ' << s << w << endl;
		if(n % 2 == 0) res = result[check(w)];
		else res = result[2];
		cout << res << endl;
		res.clear();
	}
	return 0;
}
