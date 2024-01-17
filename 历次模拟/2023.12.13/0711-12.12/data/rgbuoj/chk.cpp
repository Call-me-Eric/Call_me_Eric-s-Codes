#include "testlib.h"
#include <bits/stdc++.h>

struct dsu {
  public:
    dsu() : _n(0) {}
    explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

  private:
    int _n;
    // root node: -1 * component size
    // otherwise: parent
    std::vector<int> parent_or_size;
};

#define ensuref(stream, cond, ...) \
do { \
	if (!(cond)) { \
		stream.quitf(_wa, __VA_ARGS__); \
	} \
} while (0)

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);

	constexpr int maxn = 250;
	int r = inf.readInteger(0, maxn - 1, "r"),
		g = inf.readInteger(0, maxn - 1, "g"),
		b = inf.readInteger(0, maxn - 1, "b"),
		n = r + g + b + 1,
		m = inf.readInteger(1, maxn * (maxn - 1) / 2, "m");
	
	ensuref(inf, (1 <= n && n <= maxn), "wrong input format");

	std::vector<std::tuple<int, int, char>> edges(m);
	for (auto &[u, v, c] : edges) {
		u = inf.readInteger(1, n, "u") - 1;
		v = inf.readInteger(1, n, "v") - 1;
		ensuref(inf, (u < v), "wrong input format");
		do {
			c = inf.readChar();
		} while (!isalpha(c));
		ensuref(inf, (c == 'r' || c == 'g' || c == 'b'), "wrong input format");
	}

	auto check_construction = [&](InStream &stream) {
		std::string str = stream.readString();
		for (char &c : str) {
			ensuref(stream, isalpha(c), "wrong output format");
			c = toupper(c);
		}

		ensuref(stream, (str == "YES" || str == "NO"), "result must be \"YES\" or \"NO\"");
		if (str == "NO") {
			return 0;
		} else {
			std::string used = stream.readString();
			ensuref(stream, (static_cast<int>(used.size()) == m), "used.size() should be m");

			dsu d(n);
			int used_r = 0, used_g = 0, used_b = 0;

			for (int i = 0; i < m; i++) {
				ensuref(stream, (used[i] == '0' || used[i] == '1'), "used[i] must be \'0\' or \'1\'");
				if (used[i] == '1') {
					auto &[u, v, c] = edges[i];
					ensuref(stream, !d.same(u, v), "edges mustn't form a cycle");
					d.merge(u, v);
					switch (c) {
						case 'r': {
							used_r++;
							break;
						}
						case 'g': {
							used_g++;
							break;
						}
						case 'b': {
							used_b++;
							break;
						}
					}
				}
			}
			
			ensuref(stream, (r == used_r && g == used_g && b == used_b), "r, g, b conditions not met, used_r = %d, used_g = %d, used_b = %d", used_r, used_g, used_b);
			return 1;
		}
	};

	auto player = check_construction(ouf), judge = check_construction(ans);
	if (player < judge) {
		quitf(_wa, "judge has a solution but player does not have");
	} else if (player == judge) {
		quitf(_ok, "construction is correct");
	} else {
		quitf(_fail, "player has a solution but judge does not have");
	}
}
