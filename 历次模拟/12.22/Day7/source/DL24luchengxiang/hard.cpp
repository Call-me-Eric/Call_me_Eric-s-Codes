#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
#define int ll
#define endl '\n'
#define gc cin.get
#define pc cout.put
const int N=3e2+5;
const int M=1e5+5;
const int inf=0x3f3f3f3f;
const int mod=1e9+7;
const int base=13131;
inl int read(){
    int x=0,f=1;char c=gc();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=gc();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=gc();}
    return x*f;
}
inl void write(int x){
    if(x<0){pc('-');x=-x;}
    if(x>9)write(x/10);
    pc(x%10+'0');
}
inl void writei(int x){write(x);pc(' ');}
inl void writel(int x){write(x);pc('\n');}
int n,k,q;
struct matrix{
    int a[N];
}x,y;
struct Matrix{
    int a[N][N];
}A;
inl void empty_matrix(matrix &a){
    for(int i=1;i<=n;i++)
        a.a[i]=0;
}
inl void empty_Matrix(Matrix &a){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            a.a[i][j]=0;
}
inl void init_Martix(Matrix &a){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            a.a[i][j]=i==j;
}
matrix operator*(Matrix a,matrix b){
    matrix ans;empty_matrix(ans);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            ans.a[i]^=a.a[i][j]&b.a[j];
    }
    return ans;
}
Matrix operator*(Matrix a,Matrix b){
    Matrix ans;empty_Matrix(ans);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++)
                ans.a[i][j]^=a.a[i][k]&b.a[k][j];
    return ans;
}
inl Matrix qpow(Matrix a,int b){
    Matrix ans;init_Martix(ans);
    while(b){
        if(b&1)ans=ans*a;
        a=a*a;
        b>>=1;
    }
    return ans;
}
signed main(){
    freopen("hard.in","r",stdin);
    freopen("hard.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    n=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            char c=gc();
            while(!isdigit(c))c=gc();
            A.a[i][j]=c-'0';
        }
    }
    for(int i=1;i<=n;i++){
        char c=gc();
        while(!isdigit(c))c=gc();
        x.a[i]=c-'0';
    }
    q=read();
    while(q--){
        k=read();
        y=qpow(A,k)*x;
        for(int i=1;i<=n;i++)cout<<y.a[i];cout<<endl;
    }
    return 0;
}