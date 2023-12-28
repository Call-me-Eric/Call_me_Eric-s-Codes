#include <bits/stdc++.h>
#include "testlib.h"

const int maxn = 1e6 + 10;

using string = std::string;

int T, n;
int a[maxn], b[maxn], c[maxn];
bool hacked = 0;

bool check() {
	int ax = 0, ay = 0, bx = 0, by = 0;
	for (int i = 1; i <= n; i++) {
		if (!c[i]) ax += a[i], bx += b[i];
		else ay += a[i], by += b[i];
	}
	return ax == ay && bx == by;
}

bool judge(string s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != ' ' && s[i] != EOF && s[i] != '\n' && s[i] != '\r') return false;
	}
	return true;
}

int main(int argc, char* argv[]) {
    registerLemonChecker(argc, argv);
    T = inf.readInt();
    inf.readEoln();
    while (T--) {
    	n = inf.readInt();
    	inf.readEoln();
    	for (int i = 1; i <= n; i++) {
    		a[i] = inf.readInt(1, 2);
    		if (i != n) inf.readSpace();
    	}
    	inf.readEoln();
    	for (int i = 1; i <= n; i++) {
    		b[i] = inf.readInt(1, 2);
    		if (i != n) inf.readSpace();
    	}
    	inf.readEoln();
    	int x = ans.readInt(-1, 1);
    	c[1] = ouf.readInt(-1, 1);
    	if (x == -1) {
    		if (c[1] != -1) {
    			for (int i = 2; i <= n; i++) {
    				ouf.readSpace();
    				c[i] = ouf.readInt(0, 1);
    			}
    			if (check()) {
    				hacked = 1;
    				string qwq = ouf.readLine();
    				if (!judge(qwq)) quitf(_wa, "output incorrect.");
    				ans.readLine();
    			} else {
    				quitf(_wa, "sum not equal.");
    			}
    		} else {
    			string qwq = ouf.readLine();
    			if (!judge(qwq)) quitf(_wa, "output incorrect.");
    			ans.readLine();
    		}
    		continue;
    	}
    	if (c[1] == -1) {
    		quitf(_wa, "There's a solution, but -1 found.");
    		continue;
    	}
    	for (int i = 2; i <= n; i++) {
			ouf.readSpace();
			c[i] = ouf.readInt(0, 1);
			ans.readSpace();
			ans.readInt(0, 1);
		}
		string qwq = ouf.readLine();
		if (!judge(qwq)) quitf(_wa, "output incorrect.");
    	ans.readLine();
    	if (!check()) quitf(_wa, "sum not equal.");
    }
    if (hacked) {
    	quitf(_ok, "ok the answer is correct, and you hacked std!!!");
    } else {
    	quitf(_ok, "ok the answer is correct.");
    }
}
