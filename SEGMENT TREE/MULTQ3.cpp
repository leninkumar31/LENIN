//Author:leninkumar
//http://www.spoj.com/problems/MULTQ3/
//segment tree+lazy propagation
//accepted code
#include <bits/stdc++.h>
#define MAX 100005
using namespace std;
typedef struct node {
	int a[3];
	int val;
	//for merging left and right nodes
	void merge(node l, node r) {
		for (int i = 0; i < 3; i++)
			a[i] = l.a[i] + r.a[i];
	}
};
node segment[3 * MAX];
int lazy[3 * MAX];
void build(int low, int high, int s) {
	if (low == high) {
		segment[s].val = 0;
		segment[s].a[0] = 1;
		segment[s].a[1] = 0;
		segment[s].a[2] = 0;
		return;
	}
	int mid = (low + high) / 2;
	build(low, mid, 2 * s + 1);
	build(mid + 1, high, 2 * s + 2);
	segment[s].merge(segment[2 * s + 1], segment[2 * s + 2]);
}
//for lazy updates
void lupdate(int low, int high, int s) {
	if (lazy[s]) {
		if (lazy[s] % 3 != 0) {
			int a, b, c;
			a = segment[s].a[0];
			b = segment[s].a[1];
			c = segment[s].a[2];
			if (lazy[s] % 3 == 1) {
				segment[s].a[0] = c;
				segment[s].a[1] = a;
				segment[s].a[2] = b;
			} else {
				segment[s].a[0] = b;
				segment[s].a[1] = c;
				segment[s].a[2] = a;
			}
		}
		if (low != high) {
			lazy[2 * s + 1] += lazy[s];
			lazy[2 * s + 2] += lazy[s];
		}
		lazy[s] = 0;
	}
}
int query(int low, int high, int left, int right, int s) {
	lupdate(low, high, s);
	//no overlap
	if (left > high || right < low)
		return 0;
	//total overlap
	if (left <= low && right >= high)
		return segment[s].a[0];
	//partial overlap
	int mid = (low + high) / 2;
	int lval = query(low, mid, left, right, 2 * s + 1);
	int rval = query(mid + 1, high, left, right, 2 * s + 2);
	return lval + rval;
}
void update(int low, int high, int left, int right, int s) {
	lupdate(low, high, s);//for lazy updates
	//no overlap
	if (left > high || right < low)
		return;
	//total overlap
	if (left <= low && right >= high) {
		int a, b, c;
		a = segment[s].a[0];
		b = segment[s].a[1];
		c = segment[s].a[2];
		segment[s].a[0] = c;
		segment[s].a[1] = a;
		segment[s].a[2] = b;
		if (low != high) {
			lazy[2 * s + 1] += 1;
			lazy[2 * s + 2] += 1;
		}
		return;
	}
	//partial overlap
	int mid = (low + high) / 2;
	update(low, mid, left, right, 2 * s + 1);
	update(mid + 1, high, left, right, 2 * s + 2);
	segment[s].merge(segment[2 * s + 1], segment[2 * s + 2]);
}
int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	build(0, n - 1, 0);
	while (q--) {
		int type, l, r;
		scanf("%d%d%d", &type, &l, &r);
		if (type) {
			int ans = query(0, n - 1, l, r, 0);
			printf("%d\n", ans);
		} else
			update(0, n - 1, l, r, 0);
	}
	return 0;
}
