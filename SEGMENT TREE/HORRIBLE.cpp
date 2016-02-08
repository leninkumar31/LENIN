//http://www.spoj.com/problems/HORRIBLE/
//author:leninkumar
//segment tree+lazy propagation
#include <bits/stdc++.h>
#define SET(a,val) memset(a,val,sizeof(a))
using namespace std;
typedef long long ll;
void update(ll segment[], ll lazy[], int low, int high, int left, int right,
		ll val, int s) {
	//lazy update if not updated
	if (lazy[s]) {
		segment[s] += (high - low + 1) * lazy[s];
		if (low != high) {
			lazy[2 * s + 1] += lazy[s];
			lazy[2 * s + 2] += lazy[s];
		}
		lazy[s] = 0;
	}
	//no overlap
	if (left > high || right < low)
		return;
	//total overlap
	if (left <= low && right >= high) {
		segment[s]+= (high - low + 1) * val;
		if (low != high) {
			lazy[2 * s + 1] += val;
			lazy[2 * s + 2] += val;
		}
		return;
	}
	//partial overlap
	int mid = (low + high) / 2;
	update(segment, lazy, low, mid, left, right, val, 2 * s + 1);
	update(segment, lazy, mid + 1, high, left, right, val, 2 * s + 2);
	//summing left and right part
	segment[s] = segment[2 * s + 1] + segment[2 * s + 2]; 
}
ll query(ll segment[], ll lazy[], int low, int high, int left, int right,
		int s) {
	//lazy update if not updated
	if (lazy[s]) {
		segment[s] += (high - low + 1) * lazy[s];
		if (low != high) {
			lazy[2 * s + 1] += lazy[s];
			lazy[2 * s + 2] += lazy[s];
		}
		lazy[s] = 0;
	}
	//no overlap
	if (left > high || right < low)
		return 0;
	//total overlap
	if (left <= low && right >= high)
		return segment[s];
	//partial overlap
	int mid = (low + high) / 2;
	ll lval = query(segment, lazy, low, mid, left, right, 2 * s + 1);
	ll rval = query(segment, lazy, mid + 1, high, left, right, 2 * s + 2);
	return lval + rval;
}
//initially all elememts are zero so no need of building segment tree
int main() {
	int t;//no of test cases
	scanf("%d", &t);
	while (t--) {
		int n, q;//n-no of elements q-no of queries
		scanf("%d%d", &n, &q);
		int N = 2 * pow(2, ceil(log2(n))) - 1;//no of nodes in segment tree
		ll segment[N];//segment tree
		ll lazy[N];//lazy tree
		//initializing with zeroes
		SET(segment, 0);
		SET(lazy, 0);
		while (q--) {
			int type;
			scanf("%d", &type);
			if (!type) {
				int l, r;
				ll val;
				scanf("%d%d%lld", &l, &r, &val);
				update(segment, lazy, 0, n - 1, l - 1, r - 1, val, 0);
			} else {
				int l, r;
				scanf("%d%d", &l, &r);
				ll sum = query(segment, lazy, 0, n - 1, l - 1, r - 1, 0);
				printf("%lld\n", sum);
			}
		}
	}
	return 0;
}
