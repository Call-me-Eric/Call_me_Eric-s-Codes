#include<bits/stdc++.h>
#include<random>

#define int long long

using namespace std;

mt19937 rd;

const int B=1e9,T0=4,T1=5;
const string Name="segment";

int ex_nm[T0]={1,1,1,1};
int ex_N[T0]={5,18,300,2000};

int da_nm[T1]={4,4,4,4,4};
int da_N[T1]={18,300,2000,200000,200000};
int da_SP[T1]={0,0,0,1,0};

inline int random(int x,int y);

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
					fprintf(file,"%lld\n",n);
					for(int i=1;i<=n;++i)
						fprintf(file,"%lld%c",random(1,n),(i==n?'\n':' '));
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
					int n=da_N[I],m=1000000000;
					if(da_SP[I]) m=10;
					fprintf(file,"%lld\n",n);
					int tg=-1,qwq=random(4,7);
					for(int i=1;i<=n;++i)
					{
						int x=random(1,m);
						if(da_SP[I])
						{
							if(tg!=-1) x=9-tg,tg=-1;
							else
							{
								if(random(0,3))
									x=random(qwq,9);
								else x=random(0,9),tg=x;
							}	
						}
						
						fprintf(file,"%lld%c",x,(i==n?'\n':' '));
					}
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
