#include<bits/stdc++.h>
using namespace std;

const double pi=acos(-1);
int res[110];

int main()
{
    for(int n=0;n<=36;n++)
    {
        fill(res,res+n+1,-1);
        for(int s=0;s<(1<<n);s++)
        {
            if(s!=0&&(s&1)==0) continue;
            if(res[__builtin_popcount(s)]!=-1) continue;

            double x=0,y=0;
            for(int i=0;i<n;i++)
            {
                if((s>>i)&1)
                {
                    x+=cos(2*pi/n*i);
                    y+=sin(2*pi/n*i);
                }
            }
            if(abs(x)<=1e-8*(1<<n)&&abs(y)<=1e-8*(1<<n))
            {
                res[__builtin_popcount(s)]=s;
            }
        }
        
        cout<<"{";
        for(int i=0;i<=n;i++)
        {
            cout<<res[i];
            if(i<n) cout<<",";
        }
        cout<<"},";
        cout<<endl;
    }
}