#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
	freopen("sumeru.in","r",stdin);
	freopen("sumeru.out","w",stdout);
	int T;cin>>T;
	while(T--)
	{
		int a11,a12,a13,a21,a22,a23,a31,a32,a33,a41,a42,a43;
		cin>>a11>>a12>>a13>>a21>>a22>>a23>>a31>>a32>>a33>>a41>>a42>>a43;
		int aa1=a11,bb1=a21,cc1=a31,dd1=a41,aa2=a12,bb2=a22,cc2=a32,dd2=a42,aa3=a13,bb3=a23,cc3=a33,dd3=a43;
		double x,y,z;
		int t1=(bb2*aa1-bb1*aa2)*(cc3*aa1-cc1*aa3),t2=(bb3*aa1-bb1*aa3)*(cc2*aa1-cc1*aa2),
			t3=(bb2*aa1-bb1*aa2)*(dd3*aa1-dd1*aa3),t4=(dd2*aa1-dd1*aa2)*(bb3*aa1-bb1*aa3);
		z=(double)(t3-t4)/(t1-t2);
		int t5=(bb1*aa2-bb2*aa1)*(bb1*cc3-bb3*cc1),t6=(bb1*aa3-bb3*aa1)*(bb1*cc2-bb2*cc1),
			t7=(dd2*bb1-dd1*bb2)*(bb1*cc3-bb3*cc1),t8=(dd3*bb1-dd1*bb3)*(bb1*cc2-bb2*cc1);
		x=(double)(t7-t8)/(t5-t6);
		int t9=(bb2*aa1-bb1*aa2)*(cc3*aa1-cc1*aa3),t10=(bb3*aa1-bb1*aa3)*(cc2*aa1-cc1*aa2),
			t11=(dd2*aa1-dd1*aa2)*(cc3*aa1-cc1*aa3),t12=(dd3*aa1-dd1*aa3)*(cc2*aa1-cc1*aa2);
		y=(double)(t11-t12)/(t9-t10);
		if(x>=0&&y>=0&&z>=0) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
