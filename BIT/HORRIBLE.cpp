//Author:leninkumar
//http://www.spoj.com/problems/HORRIBLE/
//Accepted code
//range update-range query
#include <bits/stdc++.h>
#define MAX 100009
using namespace std;
typedef long long ll;
int t, n, c;
ll BIT1[MAX];//for range update and point query
ll BIT2[MAX];//for X factor
//for updating
void update(ll BIT[], int x, ll val) {
	while (x <= n) {
		BIT[x] += val;
		x += (x & -x);//to get next node
	}
}
//if u pass BIT1 u wil get value at that index 
//if u pass BIT2 u wil get X factor
ll sum(ll BIT[], int x) {
	ll ans = 0;
	while (x > 0) {
		ans += BIT[x];
		x -= (x & -x);//to get parent node
	}
	return ans;
}
//to get prefix sum
ll query(int p) {
	return p * sum(BIT1, p) - sum(BIT2, p);
}
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &c);
		memset(BIT1, 0, sizeof(ll) * (n + 1));
		memset(BIT2, 0, sizeof(ll) * (n + 1));
		while (c--) {
			int type, l, r;
			scanf("%d%d%d", &type, &l, &r);
			if (!type) {
				ll val;
				scanf("%lld", &val);
				//updating BIT1,and BIT2
				update(BIT1, l, val);
				update(BIT1, r + 1, -val);
				update(BIT2, l, val * (l - 1));
				update(BIT2, r + 1, -val * (r));
			} else
				printf("%lld\n", query(r) - query(l - 1));//to get range sum
		}
	}
	return 0;
}
