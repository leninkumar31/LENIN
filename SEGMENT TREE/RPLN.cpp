//author:lenin kumar 
//language:c++
//date:06/02/16
//http://www.spoj.com/problems/RPLN/ link to problem
//concept:segment tree
//accepted code
// easy
#include <bits/stdc++.h>
#define MAX 100005
#define SET(a,val) memset(a,val,sizeof(a))
using namespace std;
int a[MAX];//original array
int segment[4 * MAX];//for segment tree
int build(int low, int high, int s) {
	//for leafs we assign values directly else we have to find min of left part and 
	// right part
	if (low == high) {
		segment[s] = a[low];
		return segment[s];
	}
	int mid = (low + high) / 2;
	int lval = build(low, mid, 2 * s + 1);
	int rval = build(mid + 1, high, 2 * s + 2);
	segment[s] = min(lval, rval);
	return segment[s];
}
int minval(int low, int high, int left, int right, int s) {
	//no overlap
	if (left > high || right < low)
		return INT_MAX;
	//total overlap
	if (left <= low && right >= high)
		return segment[s];
	//partial overlap
	int mid = (low + high) / 2;
	int lval = minval(low, mid, left, right, 2 * s + 1);
	int rval = minval(mid + 1, high, left, right, 2 * s + 2);
	return min(lval, rval);
}
int main() {
	int t; //no of testcases
	scanf("%d", &t);
	for (int i=1;i<=t;i++) {
		int n, q; //n-no of elements,q-no of queries
		scanf("%d%d", &n, &q);
		SET(segment, 0); //initializing segment tree with zeroes
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		//build segmenttree for array elemets
		build(0, n - 1, 0);
		printf("Scenario #%d:\n\n",i);
		 while(q--){
			int l, r;
			scanf("%d%d", &l, &r);
			int mval = minval(0, n - 1, l-1, r-1, 0);
			printf("%d\n\n",mval);
		}
	}
	return 0;
}
