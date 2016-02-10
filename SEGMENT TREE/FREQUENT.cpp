//Author:leninkumar
//http://www.spoj.com/problems/FREQUENT/
//accepted code
#include <bits/stdc++.h>
#define MAX 100009
using namespace std;
typedef struct node {
	int ffreq;//it stores highest frequency number in that range
	int pfreq;//it stores starting number frequency in that range
	int pval;//it stores starting val in that range
	int sfreq;//it stores last number frequency in that range
	int sval;//it stores last value in that range
	//initializing leaf nodes
	void init(int x) {
		pval = sval = x;
		ffreq = pfreq = sfreq = 1;
	}
	//merging left and right parts
	void merge(node l, node r) {
		pval = l.pval;
		//if left part prefix val and right part prefix value are same
		if (l.pval == r.pval)
			pfreq = l.pfreq + r.pfreq;
		else//else only left prefix
			pfreq = l.pfreq;
		sval = r.sval;
		if (l.sval == r.sval)//if left sufix and right suffix are same
			sfreq = l.sfreq + r.sfreq;
		else//else only right suffix
			sfreq = r.sfreq;
		if(l.sval==r.pval)//if left suffix and right prefix are same
		  ffreq = max(l.ffreq, max(r.ffreq, l.sfreq + r.pfreq));
		else//if not equal
		  ffreq=max(l.ffreq,r.ffreq);
	}
} node;
int a[MAX];
void build(node segment[], int low, int high, int s) {
	//for leaf nodes
	if (low == high) {
		segment[s].init(a[low]);
		return;
	}
	int mid = (low + high) / 2;
	build(segment, low, mid, 2 * s + 1);
	build(segment, mid + 1, high, 2 * s + 2);
	segment[s].merge(segment[2 * s + 1], segment[2 * s + 2]);//merging left and right parts
}
node query(node segment[], int low, int high, int left, int right, int s) {
	//total overlap
	if (left <= low && right >= high)
		return segment[s];
	//partial overlap
	int mid = (low + high) / 2;
	if (mid >= right)
		return query(segment, low, mid, left, right, 2 * s + 1);
	else if (mid < left)
		return query(segment, mid + 1, high, left, right, 2 * s + 2);
	node l = query(segment, low, mid, left, right, 2 * s + 1);
	node r = query(segment, mid + 1, high, left, right, 2 * s + 2);
	node n;
	n.merge(l, r);
	return n;
}
int main() {
	int n, q;
	while (1) {
		scanf("%d", &n);
		if (n == 0)
			break;
		scanf("%d", &q);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		int N = 2 * pow(2, ceil(log2(n))) - 1;
		node segment[N];
		build(segment, 0, n - 1, 0);
		while (q--) {
			int l, r;
			scanf("%d%d", &l, &r);
			node temp = query(segment, 0, n - 1, l - 1, r - 1, 0);
			printf("%d\n", temp.ffreq);
		}
	}
	return 0;
}
