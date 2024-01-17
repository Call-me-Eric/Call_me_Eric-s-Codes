#include<bits/stdc++.h>
using namespace std;

const double pi=acos(-1);

int main()
{
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);

    int n,k;
    cin>>n>>k;
    if(n==k)
    {
        cout<<n<<endl;
        return 0;
    }
    if(n<=20)
    {
        int res=0;
        for(int s=0;s<(1<<n);s++)
        {
            if(__builtin_popcount(s)>k) continue;

            // cout<<"Checking ";
            // for(int i=0;i<n;i++) cout<<((s>>i)&1);
            // cout<<" : ";

            double x=0,y=0;
            for(int i=0;i<n;i++)
            {
                if((s>>i)&1)
                {
                    x+=cos(2*pi/n*i);
                    y+=sin(2*pi/n*i);
                }
            }
            // cout<<"x = "<<x<<" , y = "<<y<<endl;
            if(abs(x)<=5e-7&&abs(y)<=5e-7)
            {
                // cout<<"it is valid"<<endl;
                if(__builtin_popcount(s)>__builtin_popcount(res))
                {
                    res=s;
                }
            }
        }

        for(int i=0;i<n;i++) cout<<((res>>i)&1);
        cout<<endl;
        return 0;
    }
    
    vector<int> fac(0);
    fac.push_back(n);
    for(int i=2;i*i<=n;i++)
    {
        if(n%i!=0) continue;
        fac.push_back(i);
        if(i*i!=n) fac.push_back(n/i);
    }
    
    int f=fac[0];
    for(int i:fac)
    {
        if(k%i<k%f) f=i;
    }
    // cout<<"f = "<<f<<endl;

    for(int i=0;i<=n-1;i++)
    {
        if(i%(n/f)<k/f) cout<<1;
        else cout<<0;
    }
    cout<<endl;
}