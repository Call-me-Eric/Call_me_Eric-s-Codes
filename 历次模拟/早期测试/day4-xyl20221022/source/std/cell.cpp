#include<bits/stdc++.h>
#define MN 1000007
void MIN( int &x,int y ) {
  ( x>y )&&( x=y );
}

int n,m,len[MN],F[MN*2],que[MN],*QL,*QR,ans;
int &f( int col,int row ) {
  return F[col*n+row-1];
}
void cleanque() {
  QL=que;QR=que-1;
}
int quemin( int col ) {
  return f(col,*QL);
}
void inque( int col,int row ) {
  if ( row<0||row+len[col]-1>n )return;
  while ( QL<=QR&&f(col,*QR)>=f(col,row) )--QR;
  *(++QR)=row;
}
void deque( int col,int row ) {
  if ( QL<=QR&& *QL<=row )++QL;
}

int main() {
	freopen("cell.in","r",stdin);
	freopen("cell.out","w",stdout);
  scanf( "%d%d",&n,&m );

  len[0]=n;
  for ( int col=1,s,t;col<=m;++col ) {
    scanf( "%d%d",&s,&t );
    len[col]=t-s+1;
    cleanque();
    for ( int k=1;k<len[col];++k )
      inque( col-1,k );
    for ( int row=1;row<=n-len[col]+1;++row ) {
      inque( col-1,row+len[col]-1 );
      f(col,row)=quemin(col-1)+abs(s-row);
      deque( col-1,row-len[col-1]+1 );
    }
    //for ( int row=1;row<=n;++row )
      //printf( "%d ",f(col,row) );puts("");
  }
  ans=n*m;
  for ( int i=1;i<=n-len[m]+1;++i )
    MIN( ans,f(m,i) );

  printf( "%d\n",ans );
}
