//Author :leninkumar
//http://www.spoj.com/problems/GSS4/
//accepted code
//we are doing range update bt lazy is not needed to make it accept.
//after performing square root if number is 1 if you perform updates again it will
//-be 1 only..we use this property
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef struct node {
	ll sum;//used for storing sum
	//flag is true if left and right parts are true means numbers in left and right
	//-parts are equal to 1 we dont need to update again
	bool flag;
	void merge(node l, node r) {
		sum = l.sum + r.sum;
		flag = (l.flag && r.flag) ? true : false;
	}
} node;
//building segment tree
void build(ll a[], node segment[], int low, int high, int s) {
	if (low == high) {
		segment[s].sum = a[low];
		if (a[low] == 1)
			segment[s].flag = true;
		else
			segment[s].flag = false;
		return;
	}
	int mid = (low + high) / 2;
	build(a, segment, low, mid, 2 * s + 1);
	build(a, segment, mid + 1, high, 2 * s + 2);
	segment[s].merge(segment[2 * s + 1], segment[2 * s + 2]);
}
//querying segment tree
ll query(ll a[], node segment[], int low, int high, int left, int right,
		int s) {
	//no overlap
	if (left > high | right < low)
		return 0;
	//total overlap
	if (left <= low && right >= high)
		return segment[s].sum;
	//partial overlap
	int mid = (low + high) / 2;
	ll lval = query(a, segment, low, mid, left, right, 2 * s + 1);
	ll rval = query(a, segment, mid + 1, high, left, right, 2 * s + 2);
	return lval + rval;
}
//updating segment tree
void update(ll a[], node segment[], int low, int high, int left, int right,
		int s) {
	//no overlap
	if (left > high || right < low)
		return;
	//if node is true we don need to update
	if (segment[s].flag)
		return;
	//if it is leaf
	if (low == high) {
		a[low] = sqrt(a[low]);
		segment[s].sum = a[low];
		if (a[low] == 1)
			segment[s].flag = true;
		return;
	}
	//if it is not leaf
	int mid = (low + high) / 2;
	if (mid >= right)
		update(a, segment, low, mid, left, right, 2 * s + 1);
	else if (mid < left)
		update(a, segment, mid + 1, high, left, right, 2 * s + 2);
	else {
		update(a, segment, low, mid, left, right, 2 * s + 1);
		update(a, segment, mid + 1, high, left, right, 2 * s + 2);
	}
	segment[s].merge(segment[2 * s + 1], segment[2 * s + 2]);
}
int main() {
	int n;
	int count = 1;
	while (scanf("%d", &n) != EOF) {
		printf("Case #%d:\n", count);
		ll a[n];
		for (int i = 0; i < n; i++)
			scanf("%lld", &a[i]);
		int N = 2 * pow(2, ceil(log2(n))) - 1;
		node segment[N];
		build(a, segment, 0, n - 1, 0);
		int q;
		scanf("%d", &q);
		while (q--) {
			int type, l, r;
			scanf("%d%d%d", &type, &l, &r);
			if (type) {
				ll sum = query(a, segment, 0, n - 1, min(l - 1, r - 1),
						max(l - 1, r - 1), 0);
				printf("%lld\n", sum);
			} else
				update(a, segment, 0, n - 1, min(l - 1, r - 1),
						max(l - 1, r - 1), 0);
		}
		count++;
		printf("\n");
	}
	return 0;
}
