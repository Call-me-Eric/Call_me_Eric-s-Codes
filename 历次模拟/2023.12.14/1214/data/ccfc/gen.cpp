#include<bits/stdc++.h>
#include<random>

#define int long long

using namespace std;

mt19937 rd;

const int B=1e9,T0=3,T1=5;
const string Name="ccfc";

int ex_nm[T0]={1,1,1};
int ex_N[T0]={14,300,2000};

int da_nm[T1]={3,5,3,3,6};
int da_N[T1]={50,300,2000,10000,100000};
int da_M[25]={2,3,4,2,3,4,5,6,3,4,5,3,4,5,2,3,4,5,10,12};

inline int random(int x,int y);

char s[1000005];

signed main()
{
	puts("Choose to gen what 0:example/1:data");
	int opt;
	cin>>opt;
	puts("Choose to run old or make new 0:run/1:make");
	int opt2;
	cin>>opt2;
	if(opt2==1)
	{
		puts("read seed or rand seed 0:rand/1:read");
		int opt1;
		cin>>opt1;
		if(opt1==0)
		{
			int seed=time(0);
			rd=mt19937(seed);
			printf("the seed is:%d\n",seed);
		}
		else
		{
			printf("please input the seed:");
			int seed;cin>>seed;
			rd=mt19937(seed);
		}
	}
	if(opt==0)
	{
		int tot=1;
		for(int I=0;I<T0;++I)
			for(int J=0;J<ex_nm[I];++J)
			{
				FILE *file;
				string path="ex_"+Name+to_string(tot)+".in"; 
				
				if(opt2==1)
				{
					file=fopen(path.data(),"w");
					int n=ex_N[I];
					int lim=(int)sqrt(n);
					for(int i=1;i<=lim;++i)
						s[i]=random(0,25)+'a';
					for(int i=lim+1;i<=n;)
					{
						if(random(0,1))
							s[i]=random(0,25)+'a';
						else
						{
							int r=min(i+lim-1,n);
							for(int j=i;j<=r;++j)
								s[j]=s[j-i+1];
							i=r+1;
						}
					}
					for(int i=1;i<=n;++i)
						fprintf(file,"%c",s[i]);
					fclose(file);
				}
				
				string Opera="std.exe < "+path+" > "+"ex_"+Name+to_string(tot)+".ans";
				system(Opera.data());
				printf("ok to gen example %lld\n",tot);
				++tot;
			}
	}
	else
	{
		int tot=1;
		for(int I=0;I<T1;++I)
			for(int J=0;J<da_nm[I];++J)
			{
				FILE *file;
				string path=Name+to_string(tot)+".in"; 
				
				if(opt2==1)
				{
					file=fopen(path.data(),"w");
					int n=da_N[I];
					int lim=da_M[tot-1];
					for(int i=1;i<=lim;++i)
						s[i]=random(0,25)+'a';
					for(int i=lim+1;i<=n;)
					{
						if(random(0,1))
							s[i]=random(0,25)+'a';
						else
						{
							int r=min(i+lim-1,n);
							for(int j=i;j<=r;++j)
								s[j]=s[j-i+1];
							i=r+1;
						}
					}
					for(int i=1;i<=n;++i)
						fprintf(file,"%c",s[i]);
					fclose(file);
				}
				
				string Opera="std.exe < "+path+" > "+Name+to_string(tot)+".out";
				system(Opera.data());
				printf("ok to gen data %lld\n",tot);
				++tot;
			}
	}
	return 0;
}

inline int random(int x,int y)
{
	return (rd()%B*B+rd()%B)%(y-x+1)+x;
}
