#include <list>
#include <cstdio>

using namespace std;
list<int> l;
int main(){
	l.push_back(9);
	l.push_back(8);
	l.push_back(7);
	l.push_back(6);
	l.sort();
	for(list<int>::iterator it = l.begin(); it != l.end(); it++)printf("%d ",*it);
	return 0;
}

