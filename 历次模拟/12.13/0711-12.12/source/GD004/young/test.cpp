#include<bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define drep(i,a,b) for (int i=(a);i>=(b);i--)
typedef long long ll;
using namespace std;
inline void setfile()
{
	#ifndef pbtxdy
	freopen("young.in","r",stdin);
	freopen("young.out","w",stdout);
	#endif
}

#define fir first
#define sec second

const int mod=998244353;
inline int qmo(int x){return x+((x>>31)&mod);}
inline int add(int x,int y){return qmo(x+y-mod);}
inline int sub(int x,int y){return qmo(x-y);}
inline void inc(int &x,int y){x=add(x,y);}
inline void dec(int &x,int y){x=sub(x,y);}


int main()
{
	ios::sync_with_stdio(false),cin.tie(0);

	vector<int> a={1,3,5};
	a.insert(a.begin(),-111);
	for (auto x:a) printf("%d ",x);
	printf("\n");


	a.insert(a.begin()+2,-111);
	for (auto x:a) printf("%d ",x);
	printf("\n");

	a.erase(a.begin()+2);
	for (auto x:a) printf("%d ",x);
	printf("\n");

	return 0;
}