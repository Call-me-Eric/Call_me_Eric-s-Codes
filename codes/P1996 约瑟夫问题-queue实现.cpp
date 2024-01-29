#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

int main(){
	queue<int> q;
	int n, m, nownum = 1;
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		q.push(i);
	while(!q.empty()){
		if(nownum == m){
			cout << q.front() <<' ';
			q.pop();
			nownum = 1;
		}
		else{
			nownum ++;
			q.push(q.front());
			q.pop();
		}
	}
	cout << endl;
	return 0;
}

