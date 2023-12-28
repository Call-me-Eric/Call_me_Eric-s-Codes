#include<cstdio>
#include<fstream>
using namespace std;
ifstream fin,fout,fstd;
ofstream fscore,freport;
int f[100010][22],s1[22],s2[22];
void check(int w,int a)
{
	if(s1[w]<a) s2[w]=s1[w],s1[w]=a;
	else if(s2[w]<a) s2[w]=a;
}
void close_all()
{
	fin.close();
	fout.close();
	fstd.close();
	fscore.close();
	freport.close();
}
int n,k,X,ans,ans1,ans2,a;
int main(int argc,char **argv)
{
	fin.open(argv[1]);
	fout.open(argv[2]);
	fstd.open(argv[3]);
	fscore.open(argv[5]);
	freport.open(argv[6]);
	fin>>n>>k>>X;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=k;j++)
			fin>>f[i][j];
	fout>>ans1;
	fstd>>ans2;
	if(ans1!=ans2)
	{
		fscore<<0;
		freport<<"Your answer is bigger than the correct answer.";
		close_all();
		return 0;
	}
	for(int i=1;i<=n;i++)
		fout>>a,check(a,f[i][a]);
	for(int i=1;i<=k;i++)
		for(int j=i+1;j<=k;j++)
			if(s1[i]&&s1[j]&&1ll*X*(j-i)+s1[i]+s1[j]<=2147483647)
				ans=max(ans,s1[i]+s1[j]+X*(j-i));
	for(int i=1;i<=k;i++) ans=max(ans,s1[i]+s2[i]);
	if(ans!=ans1)
	{
		fscore<<0;
		freport<<"No optimal solution was found.";
	}
	else
	{
		fscore<<5;
		freport<<"You answer is correct.";
	}
	close_all();
	return 0;
}
