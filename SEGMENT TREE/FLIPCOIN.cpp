//author :leninkumar
//https://www.codechef.com/problems/FLIPCOIN/
//accepted code
//segment tree +lazy propagation
#include <bits/stdc++.h>
#define MAX 100005
using namespace std;
int segment[3 * MAX];
int lazy[3 * MAX];
void update(int low, int high, int left, int right, int s) {
	//this is for propagating update if there is update bt not propagated
	if (lazy[s]) {
		segment[s] = high - low + 1 - segment[s];//total lights minus already switched on
		lazy[s] = 0;
		if (low != high) {
			//if it is not leaf instead of propagting updates
			//we are using lazy tree          
			lazy[2 * s + 1] = lazy[2 * s + 1] ? 0 : 1;
			lazy[2 * s + 2] = lazy[2 * s + 2] ? 0 : 1;
		}
	}
	//no overlap
	if (left > high || right < low)
		return;
	//total overlap
	if (left <= low && right >= high) {
		segment[s] = high - low + 1 - segment[s];
		if (low != high) {
			lazy[2 * s + 1] = lazy[2 * s + 1] ? 0 : 1;
			lazy[2 * s + 2] = lazy[2 * s + 2] ? 0 : 1;
		}
		return;
	}
	//partial overlap
	int mid = (low + high) / 2;
	update(low, mid, left, right, 2 * s + 1);
	update(mid + 1, high, left, right, 2 * s + 2);
	segment[s]=segment[2*s+1]+segment[2*s+2];
}
int query(int low, int high, int left, int right, int s) {
	//this is for propagating update if there is update bt not propagated
	if (lazy[s]) {
		segment[s] = high - low + 1 - segment[s];
		lazy[s] = 0;
		if (low != high) {
			lazy[2 * s + 1] = lazy[2 * s + 1] ? 0 : 1;
			lazy[2 * s + 2] = lazy[2 * s + 2] ? 0 : 1;
		}
	}
	//no overlap
	if (left > high || right < low)
		return 0;
	//total overlap
	if (left <= low && right >= high)
		return segment[s];
	//partial overlap
	int mid = (low + high) / 2;
	int lval = query(low, mid, left, right, 2 * s + 1);
	int rval = query(mid + 1, high, left, right, 2 * s + 2);
	return lval + rval;
}
//no need to build segment tree because intially all elements are zero
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	while (m--) {
		int type, l, r;
		scanf("%d%d%d", &type, &l, &r);
		if (type) {
			int val = query(0, n - 1, l, r, 0);
			printf("%d\n", val);
		} else
			update(0, n - 1, l, r, 0);
	}
	return 0;
}
