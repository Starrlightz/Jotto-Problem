
#include <execution>
#include <bits/stdc++.h>

using namespace std;

#define int unsigned 

constexpr int N = 5176;

int32_t main() {
	const int ALL = (1 << 26) - 1;
	bitset<ALL + 1> filter0, filter, tried;
	auto Insert0 = [&](int x) {filter0[x] = 1; };
	auto Count0 = [&](int x) -> bool {return filter0[x];  };
	auto Insert = [&](int x) {filter[x] = 1; };
	auto Count = [&](int x) -> bool {return filter[x];  };
	auto Insert2 = [&](int x) {tried[x] = 1; };
	auto Count2 = [&](int x) -> bool {return tried[x];  };
	auto t1 = chrono::high_resolution_clock::now();
	auto Time = [&] {
		auto t2 = chrono::high_resolution_clock::now();
		cout << (t2 - t1).count() / 1e9 << " s" << '\n';
	};
	ifstream cin;
	vector<string> words;
	auto encode1 = [&](const string& x) {
		int e = 0;
		for (auto y : x)
			e |= 1 << (25 - (y - 'a'));
		return e;
	};
	auto encode = [&](const string& x) {
		int e = 0;
		for (auto y : x)
			e |= 1 << (y - 'a');
		return e;
	};
	cin.open("wordle-combined.txt");
	string cur;
	while (cin >> cur) {
		if (cur.length() != 5)
			continue;
		if (__builtin_popcount(encode(cur)) == 5)
			words.emplace_back(cur);
	}
	cin.close();
	sort(words.begin(), words.end(), [&](const string& a, const string& b) {return (encode1(a)) > (encode1(b)); });
	words.erase(unique(words.begin(), words.end(), [&](const string& a, const string& b) {return encode(a) == encode(b); }), words.end());
	const int n = words.size();
	vector<int> enc(n);
	unordered_map<int, string> inv;
	unordered_map<int, int> hash;
	for (int i = 0; i < n; ++i) {
		enc[i] = encode(words[i]);
		inv[enc[i]] = words[i];
		hash[enc[i]] = i;
	}
	Time();
	vector<bitset<N>> v(n);
	for (int i = 0; i < n - 2; ++i)
		for (int j = i + 1; j < n - 1; ++j)
			if (!(enc[i] & enc[j]))
				v[i].set(j), v[j].set(i);
	Time();
	vector<tuple<int, int, int>> sol;
	int cnt = 0;
	for (int i = 0; i < n - 2; ++i) {
		int mask = enc[i];
		for (int j = v[i]._Find_first(); j < i; j = v[i]._Find_next(j)) {
			int newmask = mask | enc[j];
			if (!Count0(newmask)) {
				Insert0(newmask);
				for (int z = ALL ^ newmask; z; z &= (z - 1))
					Insert(newmask | (1 << __builtin_ctz(z)));
			}
		}
		vector<int> dummy;
		for (int j = v[i]._Find_next(i); j < n - 1; j = v[i]._Find_next(j))
			if (!Count2(mask | enc[j])) {
				Insert2(mask | enc[j]);
				dummy.emplace_back(j);
			}
		for_each(execution::par, dummy.begin(), dummy.end(), [&](int j) {
			auto cur = v[i] & v[j];
			for (int k = cur._Find_next(j + 1); k < n; k = cur._Find_next(k)) {
				int finalmask = mask | enc[j] | enc[k], neededmask = ALL ^ finalmask;
				if (Count(neededmask)) {
					int x = enc[i] | enc[j];
					vector<pair<int, int>> sol1, sol2;
					for (int i = 0; i < n; ++i)
						if (hash.count(x ^ enc[i]) && hash[x ^ enc[i]] < i)
							sol1.emplace_back(i, hash[x ^ enc[i]]);
					for (int w = neededmask; w; w &= (w - 1)) {
						int mask = neededmask ^ (1 << __builtin_ctz(w));
						if (Count0(mask))
							for (int i = 0; i < n; ++i)
								if (hash.count(mask ^ enc[i]) && hash[mask ^ enc[i]] < i)
									sol2.emplace_back(i, hash[mask ^ enc[i]]);
					}
                    for (auto a : sol1)
                        for (auto b : sol2)
                            ++cnt, printf("%s %s %s %s %s\n", words[a.first].c_str(), words[a.second].c_str(), words[k].c_str(), words[b.first].c_str(), words[b.second].c_str());
				}
			}
			}
		);
	}
	cout << cnt << '\n';
	Time();
}