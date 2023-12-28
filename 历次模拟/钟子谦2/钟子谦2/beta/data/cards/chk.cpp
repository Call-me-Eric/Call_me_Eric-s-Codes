#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int n;
vector<int> oo;
vector<pii> p;
ll pans, pouf;

ll calc(vector<int> &res) {
	ll atk = 0, ret = 0;
	for (int i = 0; i < n; i++) {
		if (res[i] == 1)
			atk += p[i].first;
		else
			ret += atk + p[i].second;
	}
	return ret;
}

int main(int argc, char *argv[]) {
	//registerLemonChecker(argc, argv);
	 registerTestlibCmd(argc,argv);
	n = inf.readInt();
	p.resize(n);
	for (int i = 0; i < n; i++) {
		p[i].first = inf.readInt();
		p[i].second = inf.readInt();
	}
	auto aans = ans.readLong();
    auto aouf = ouf.readLong();
	for (int i = 0; i < n; i++) {
		oo.push_back(ouf.readInt(1, 2));
        ans.readInt(1, 2);
	}
	auto rc = calc(oo);
    assert(rc<=aans);
    if(rc!=aouf)
        quitf(_wa,"wrong solution: reported damage is %lld, but actual damage is %lld.",aouf,rc);
    else if (rc == aans)
		quitf(_ok, "total damage is %lld.", rc);
	else
		quitf(_wa, "expected total damage is %lld, but actual total damage is %lld.", aans, rc);
}
