//Author:leninlumar
//http://www.spoj.com/problems/YODANESS/
//accepted code
//inversion count
#include <bits/stdc++.h>
#define MAX 30009
using namespace std;
typedef long long ll;
int t, n;
ll BIT[MAX];
void update(int x, int val) {
	while (x <= n) {
		BIT[x] += val;
		x += (x & -x);
	}
}
ll sum(int x) {
	ll res = 0;
	while (x) {
		res += BIT[x];
		x -= (x & -x);
	}
	return res;
}
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		vector<string> v;
		for (int i = 0; i < n; i++)
		{
			string str;
			cin>>str;
			v.push_back(str);
		}
		map<string, int> m;
		for (int i = 0; i < n; i++) {
			string str;
			cin >> str;
			m[str] = i + 1;
		}
		int a[n];
		for (int i = 0; i < v.size(); i++)
			a[i] = m[v[i]];
		memset(BIT, 0, sizeof(ll) * (n + 1));
		ll ans = 0;
		for (int i = n - 1; i >= 0; i--) {
			ans += sum(a[i]);
			update(a[i] + 1, 1);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
