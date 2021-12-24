#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <cmath>
#include <random>
#include <ctime>
using namespace std;
typedef long long ll;
typedef long double ld;

const int INF = 1e9, MOD = 1e9 + 7, Q = 38;
const ld eps = 1e-9;
const ll ll_INF = 1e18;
mt19937 gen;


void solve() {
	string s;
	getline(cin, s);
	vector<int> st;
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == ' ') continue;
		else if (s[i] == '+') {
			int x1 = st.back();
			st.pop_back();
			int x2 = st.back();
			st.pop_back();
			st.push_back(x1 + x2);
		}
		else if (s[i] == '-') {
			int x1 = st.back();
			st.pop_back();
			int x2 = st.back();
			st.pop_back();
			st.push_back(x2 - x1);
		}
		else if (s[i] == '*') {
			int x1 = st.back();
			st.pop_back();
			int x2 = st.back();
			st.pop_back();
			st.push_back(x1 * x2);
		}
		else {
			st.push_back(s[i] - '0');
		}
	}
	cout << st.back();
}


signed main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);
	int t = 1;
	//	gen.seed(time(0));
	//	cout << fixed;
	//	cout.precision(15);
//	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
