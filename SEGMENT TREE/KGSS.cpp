//author :leninkumar
//accepted code
//http://www.spoj.com/problems/KGSS/
#include <bits/stdc++.h>
#define MAX 10005
using namespace std;
typedef struct node {
	int maxval;//it stores max value
	int minval;//it stores next max value
	void merge(node l, node r) {
		maxval = max(l.maxval, r.maxval);//we are finding max value
		minval = max(l.minval, max(r.minval, min(l.maxval, r.maxval)));//finding next max
	}
} node;
//building segment tree
node build(int a[], node segment[], int low, int high, int s) {
	//for leaf nodes
	if (low == high) {
		segment[s].minval = 0;
		segment[s].maxval = a[low];
		return segment[s];
	}
	int mid = (low + high) / 2;
	node l = build(a, segment, low, mid, 2 * s + 1);//left part
	node r = build(a, segment, mid + 1, high, 2 * s + 2);//right part
	segment[s].merge(l, r);//finding maxx and next max 
	return segment[s];
}
//point update
void update(int a[], node segment[], int low, int high, int pos, int val,
		int s) {
	if (low == pos && high == pos) {
		a[low] = val;
		segment[s].minval = 0;
		segment[s].maxval = val;
		return;
	}
	int mid = (low + high) / 2;
	if (mid < pos)
		update(a, segment, mid + 1, high, pos, val, 2 * s + 2);
	else
		update(a, segment, low, mid, pos, val, 2 * s + 1);
	segment[s].merge(segment[2 * s + 1], segment[2 * s + 2]);
}
node query(int a[], node segment[], int low, int high, int left, int right,
		int s) {
	//total overlap
	if (left <= low && right >= high)
		return segment[s];
	//partial overlap
	int mid = (low + high) / 2;
	if (mid >= right)//only left part
		return query(a, segment, low, mid, left, right, 2 * s + 1);
	else if (mid < left)//only right part
		return query(a, segment, mid + 1, high, left, right, 2 * s + 2);
	//if silution exists in both lef t and right
	node l = query(a, segment, low, mid, left, right, 2 * s + 1);
	node r = query(a, segment, mid + 1, high, left, right, 2 * s + 2);
	node n;
	n.merge(l, r);
	return n;
}
int main() {
	int n;
	scanf("%d", &n);
	int a[n + 1];
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	int N = 2 * pow(2, ceil(log2(n))) - 1;//finding nodes of segment tree
	node segment[N];
	build(a, segment, 0, n - 1, 0);//building segment tree
	int q;
	scanf("%d", &q);
	while (q--) {
		char ch;
		int l, r;
		cin>>ch;
		scanf("%d%d",&l,&r);
		if (ch == 'Q') {
			node temp=query(a, segment, 0, n - 1, l - 1, r - 1, 0);
			printf("%d\n", temp.maxval+temp.minval);
		} else
			update(a, segment, 0, n - 1, l - 1, r, 0);
	}
	return 0;
}
