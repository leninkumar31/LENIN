//Author:leninkumar
//http://www.spoj.com/problems/DCEPC206/
//related to inversion count
#include <bits/stdc++.h>
#define MAX 1000009
using namespace std;
typedef long long ll;
ll BIT[MAX], temp;
ll sum(int x) {
	ll res = 0;
	while (x) {
		res += BIT[x];
		x -= (x & -x);
	}
	return res;
}
void update(int x, int val) {
	while (x <= temp) {
		BIT[x] += val;
		x += (x & -x);
	}
}
int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		int a[n];
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		temp = a[0];
		for (int i = 1; i < n; i++) {
			if (temp < a[i])
				temp = a[i];
		}
		memset(BIT,0,sizeof(ll)*(temp+1));
		ll ans = 0;
		for (int i = 0; i < n; i++) {
			ans += sum(a[i]);
			update(a[i] + 1, a[i]);
		}
		cout<<ans<<endl;
	}
	return 0;
}
