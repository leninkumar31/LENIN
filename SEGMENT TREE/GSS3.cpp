//Author:leninkumar
//http://www.spoj.com/problems/GSS1/
//accepted code
//we have to use divide and conquer max sum subarray concept
//what we are storing in node and how we are merging left and right part is important
#include <bits/stdc++.h>
#define MAX 50009
using namespace std;
typedef struct node {
	int sum; //to store sum of all elements of that part
	int presum; //prefix sum of that part
	int sufsum; //suffix sum of that part
	int maxsum; //max sum sub array of that part
	//initializing leaf nodes
	void init(int x) {
		presum = sufsum = sum = maxsum = x;
	}
	//merginging left and right part
	void merge(node l, node r) {
		sum = l.sum + r.sum;	//sum is simply sum of left and right part
		presum = max(l.presum, l.sum + r.presum);
		sufsum = max(r.sufsum, l.sufsum + r.sum);
		maxsum = max(l.maxsum, max(r.maxsum, l.sufsum + r.presum));	//maxsum sub array
		//-is max of left max sum and right max sum and sum of left suffix sum and
		//-right prefix sum
	}
} node;
int a[MAX];		//input array
node segment[3 * MAX];		//segment tree
//building segment tree
void build(int low, int high, int s) {
	//for leaf nodes
	if (low == high) {
		segment[s].init(a[low]);
		return;
	}
	//if not leaf build left and right parts
	int mid = (low + high) / 2;
	build(low, mid, 2 * s + 1);
	build(mid + 1, high, 2 * s + 2);
	segment[s].merge(segment[2 * s + 1], segment[2 * s + 2]);
}
node query(int low, int high, int left, int right, int s) {
	//total overlap
	if (left <= low && right >= high)
		return segment[s];
	//partial overlap
	int mid = (low + high) / 2;
	if (mid >= right)
		return query(low, mid, left, right, 2 * s + 1);
	else if (mid < left)
		return query(mid + 1, high, left, right, 2 * s + 2);
	node l = query(low, mid, left, right, 2 * s + 1);
	node r = query(mid + 1, high, left, right, 2 * s + 2);
	node temp;
	temp.merge(l, r);
	return temp;
}
//point update
void update(int low, int high, int pos, int val, int s) {
	if (low == pos && high == pos) {
		a[low] = val;
		segment[s].init(a[low]);
		return;
	}
	int mid = (low + high) / 2;
	if (pos <= mid)
		update(low, mid, pos, val, 2 * s + 1);
	else
		update(mid + 1, high, pos, val, 2 * s + 2);
	segment[s].merge(segment[2 * s + 1], segment[2 * s + 2]);
}
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	build(0, n - 1, 0);
	int q;
	scanf("%d", &q);
	while (q--) {
		int type, l, r;
		scanf("%d%d%d", &type, &l, &r);
		if (type) {
			node temp = query(0, n - 1, l - 1, r - 1, 0);
			printf("%d\n", temp.maxsum);
		} else
			update(0, n - 1, l - 1, r, 0);
	}
	return 0;
}
