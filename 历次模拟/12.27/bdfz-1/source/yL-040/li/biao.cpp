#include <bits/stdc++.h>
using namespace std;
#define FI first
#define SE second 
const int N = 1e4 + 5; 
inline void NextG(int n,vector<pair<int,int> > E)
{
	if(n > N) return;
	if(n <= 1) return;
	vector<pair<int,int> > Ne;
	int nxtn = E.size();
	for(int i = 0;i < E.size();i++)
		for(int j = i + 1;j < E.size();j++)
			if(E[i].FI == E[j].FI || E[i].FI == E[j].SE || E[i].SE == E[j].FI || E[i].SE == E[j].SE)
				Ne.emplace_back(i + 1,j + 1);
	printf("Graph[%d]:\n",n);
	for(auto it : E) printf("%d %d\n",it.FI,it.SE);

	NextG(nxtn,Ne);
}

int main()
{
	freopen("biao.out","w",stdout);
	vector<pair<int,int> > K4 = {make_pair(1,2),make_pair(1,3),make_pair(2,3),make_pair(4,3),make_pair(5,4),make_pair(3,5)};
	NextG(5,K4);
	return 0;
}
