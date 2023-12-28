#include<bits/stdc++.h>
#define mid (l+r)/2
#define N 1000001
using namespace std;
int t;
int p[N],cnt,l,r;
int s1[N],s2[N];
int cocu(int n,int m){
    int l=1;
    for(int i=1;i<=n;i++){
        if(s1[i]==s2[l])l++;
    }
    if(l>=m+1)return 1;
    return 0;
}
int main(){
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    for(int i=11;i<=100000;i++){
        int k=i,flag=1;
        while(k!=0){
            if(k%10==2||k%10==3||k%10==5||k%10==7){
                flag=0;
                break;
            }
            k=k/10;
        }
        if(!flag)continue;
        for(int j=2;j<=sqrt(i);j++){
            if(i%j==0){
                break;
            }
            if(j==(int)sqrt(i))p[++cnt]=i;
        }
    }
    cin>>t;
    while(t--){
        cnt=0;
        cin>>l>>r;
        for(int i=l;i<=r;i++){
            int k=i,flag=1,len=0;
            while(k!=0){
                if(k%10==2||k%10==3||k%10==5||k%10==7){
                    flag=0;
                    break;
                }
                len++;
                s1[len]=k%10;
                k=k/10;
            }
            if(!flag)continue;
            for(int j=1;j<=cnt;j++){
                int len2=0;
                if(p[j]>i)break;
                k=p[j];
                while(k!=0){
                    s2[++len2]=k%10;
                    k=k/10;
                }
                if(cocu(len,len2)){
                    flag=0;
                    break;
                }
            }
            if(flag)cnt++;
        }
        cout<<cnt<<endl;
    }
    return 0;
}
