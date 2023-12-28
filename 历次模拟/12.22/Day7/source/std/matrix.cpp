#include<bits/stdc++.h>

using namespace std;

const int N=1010;

int n,m;
bitset<N> A[N],x[N];

bitset<N> B[N],C[N],cy;
int cyc;

bool add(int t)
{
	bitset<N> tx(x[t]),tc;
	tc[t]=1;
	for(int i=n;i>=0;i--)
		if(tx[i])
		{
			if(B[i]==0)
			{
				B[i]=tx;
				C[i]=tc;
				return true;
			}
			tx^=B[i];
			tc^=C[i];
		}
	cy=tc;
	return false;
}

void mul(bitset<2*N> &a,bitset<2*N> &b)
{
	bitset<2*N> tmp,tc;
	for(int i=0;i<=cyc;i++)
		tc[i]=cy[i];
	for(int i=0;i<cyc;i++)
		if(b[i])
			tmp=tmp^(a<<i);
	for(int i=2*cyc;i>=cyc;i--)
		if(tmp[i])
			tmp=tmp^(tc<<(i-cyc));
	for(int i=0;i<cyc;i++)
		a[i]=tmp[i];
}

void pw(int k)
{
	int tk=k;
	if(k<=cyc)
	{
		for(int i=0;i<n;i++)
			cout<<x[k][i];
		cout<<endl;
		return ;
	}
	bitset<2*N> tmp,res;
	tmp[1]=1;res[0]=1;
	while(k>0)
	{
		if(k&1) mul(res,tmp);
		mul(tmp,tmp);
		k>>=1;
	}
	bitset<N> ans;
	for(int i=0;i<cyc;i++)
		if(res[i])
			ans=ans^x[i];
	for(int i=0;i<n;i++)
		cout<<ans[i];
	cout<<endl;
}

int main()
{
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);

	cin.sync_with_stdio(false); 
	cin>>n;
	bitset<N> tin;
	for(int i=0;i<n;i++)
	{
		cin>>tin;
		for(int j=0;j<n;j++)
			A[i][j]=tin[n-j-1];
	}
	cin>>tin;
	for(int i=0;i<n;i++)
		x[0][i]=tin[n-i-1];
	
	add(0);
	for(cyc=1;;cyc++)
	{
		for(int i=0;i<n;i++)
			x[cyc][i]=(((x[cyc-1]&A[i]).count())&1);
		if(!add(cyc)) break;
	}
	
	int m;
	cin>>m;
	for(int i=0;i<m;i++)
	{
		int k;
		cin>>k;
		pw(k);
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
