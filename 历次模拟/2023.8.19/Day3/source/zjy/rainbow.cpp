#include<bits/stdc++.h>
#define F(i0,i1,i2) for(int i0=(i1);i0<=(i2);++i0)
#define int long long
#define pii pair<int,int>
#define fr first
#define sc second
using namespace std;
inline int rd(){
	int f=0,x=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return f?-x:x;
}
const int N=2e3+7;
int n,m,a[N][N],l[N][N];
int solve(){
	int cnt=0;
	F(i,1,n){
		F(j,1,m){
		    if(i==1||j==1){
		    	l[i][j]=1;	
		    	cnt+=1;
//		    	cout<<l[i][j]<<' ';
		    	continue;
			}
			if(a[i][j]==a[i-1][j-1]&&a[i][j-1]!=a[i-1][j]&&a[i][j]!=a[i][j-1]&&a[i][j]!=a[i-1][j]){
				l[i][j]=min({l[i-1][j-1],l[i-1][j],l[i][j-1]})+1;
				cnt+=l[i][j];
			}
			else l[i][j]=1,cnt+=1;
//				cout<<l[i][j]<<' ';
		}
//		cout<<'\n';
	}
	return cnt;
}
signed main(){
	freopen("rainbow.in","r",stdin);
	freopen("rainbow.out","w",stdout);
	n=rd(),m=rd();
	F(i,1,n)F(j,1,m)a[i][j]=rd();
	cout<<solve();	
	return 0;
}
/*
10 10
2000 2001 2002 2003 2004 2005 2006 2007 2008 2009
2010 2011 2012 2013 2014 2015 2016 2017 2018 2019
2020 2021 2022 2023 2024 2025 2026 2027 2028 2029
2030 2031 2032 2033 2034 2035 2036 2037 2038 2039
2040 2041 2042 2043 2044 2045 2046 2047 2048 2049
2050 2051 2052 2053 2054 2055 2056 2057 2058 2059
2060 2061 2062 2063 2064 2065 2066 2067 2068 2069
2070 2071 2072 2073 2074 2075 2076 2077 2078 2079
2080 2081 2082 2083 2084 2085 2086 2087 2088 2089
2090 2091 2092 2093 2094 2095 2096 2097 2098 2099


*/

