# include <bits/stdc++.h>

using namespace std;

int read()
{
# define C ch = getchar()
	int x = 0 , f = 1; char C;
	for(; ch > '9' || ch < '0'; C) if(ch == '-') f = -1; for(; ch >= '0' && ch <= '9'; C) x = (x << 3) + (x << 1) + (ch ^ 48);
	return x * f;
}

const int N = 1e5 + 5;
int n , m , Q;

set< int > s[N] , T;

int main()
{
	freopen("approx.in" , "r" , stdin);
	freopen("approx.out" , "w" , stdout);
	n = read() , m = read() , Q = read();
	for(int i = 1 , k; i <= n; i++)
	{
		k = read();
		for(int j = 1 , x; j <= k; j++)
		{
			x = read();
			if(x > 0) 
			{
				for(auto y : s[x]) 
				{
					if(s[i].find(y) != s[i].end()) s[i].erase(y);
					else s[i].insert(y);
				}
			}
			else 
			{
				if(s[i].find(-x) != s[i].end()) s[i].erase(-x);
				else s[i].insert(-x);
			}
		}
	}
	for(int i = 1 , x; i <= Q; i++)
	{
		x = read();
		for(auto y : s[x])
		{
			if(T.find(y) != T.end()) T.erase(y);
			else T.insert(y);
		}
		cout << T.size() << '\n';
	}
	return 0;
}

