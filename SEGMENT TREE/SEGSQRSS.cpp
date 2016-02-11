//Author : leninkumar
//http://www.spoj.com/problems/SEGSQRSS/
//accpted code
#include <bits/stdc++.h>
#define MAX 100009
using namespace std;
typedef long long ll;
int N;
int a[MAX];
typedef struct node {
	ll sum;//sum of values in that range
	ll sq;//sum of squares in that range
	//merging left and right part
	void merge(node l, node r) {
		sum = l.sum + r.sum;
		sq = l.sq + r.sq;
	}
}node;
void build(int a[], node segment[], int low, int high, int s) {
	//if it is leaf node
	if (low == high) {
		segment[s].sum = a[low];
		segment[s].sq = a[low] * a[low];
		return;
	}
	//if it is not a leaf node
	int mid = (low + high) / 2;
	build(a, segment, low, mid, 2 * s + 1);
	build(a, segment, mid + 1, high, 2 * s + 2);
	segment[s].merge(segment[2 * s + 1], segment[2 * s + 2]);
}
void update(node segment[], pair<int, int> lazy[], int low, int high, int left,
		int right, int val, int s, int t) {
	//lazy update
	if (lazy[s].second) {
		if (lazy[s].first) {
			segment[s].sq += (high - low + 1) * lazy[s].second * lazy[s].second
					+ 2 *  segment[s].sum * lazy[s].second;
			segment[s].sum += (high - low + 1) * lazy[s].second;
			if (low != high) {
				lazy[2 * s + 1].first = lazy[2 * s + 1].first ? 1 : 0;
				lazy[2 * s + 2].first = lazy[2 * s + 2].first ? 1 : 0;
				lazy[2 * s + 1].second += lazy[s].second;
				lazy[2 * s + 2].second += lazy[s].second;
			}
			lazy[s].second = 0;
		} else {
			segment[s].sum = (high - low + 1) * lazy[s].second;
			segment[s].sq = (high - low + 1) * lazy[s].second * lazy[s].second;
			if (low != high) {
				lazy[2 * s + 1].first = 0;
				lazy[2 * s + 2].first = 0;
				lazy[2 * s + 1].second = lazy[s].second;
				lazy[2 * s + 2].second = lazy[s].second;
			}
			lazy[s].second = 0;
		}
	}
	//no overlap
	if (left > high || right < low)
		return;
	//total overlap
	if (left <= low && right >= high) {
		if (t) {
			segment[s].sq += (high - low + 1) * val * val
					+ 2 * segment[s].sum  * val;
			segment[s].sum += (high - low + 1) * val;
			if (low != high) {
				lazy[2 * s + 1].first = t;
				lazy[2 * s + 1].second += val;
				lazy[2 * s + 2].first = t;
				lazy[2 * s + 2].second += val;
			}
		} else {
			segment[s].sum = (high - low + 1) * val;
			segment[s].sq = (high - low + 1) * val * val;
			if (low != high) {
				lazy[2 * s + 1].first = t;
				lazy[2 * s + 1].second = val;
				lazy[2 * s + 2].first = t;
				lazy[2 * s + 2].second = val;
			}
		}
		return;
	}
	//partial overlap
	int mid = (low + high) / 2;
	update(segment, lazy, low, mid, left, right, val, 2 * s + 1, t);
	update(segment, lazy, mid + 1, high, left, right, val, 2 * s + 2, t);
	segment[s].merge(segment[2 * s + 1], segment[2 * s + 2]);
}
node query(node segment[], pair<int, int> lazy[], int low, int high, int left,
		int right, int s) {
	//lazy update
	if (lazy[s].second) {
		if (lazy[s].first) {
			segment[s].sq += (high - low + 1) * lazy[s].second * lazy[s].second
					+ 2 * segment[s].sum * lazy[s].second;
			segment[s].sum += (high - low + 1) * lazy[s].second;
			if (low != high) {
				lazy[2 * s + 1].first = lazy[2 * s + 1].first ? 1 : 0;
				lazy[2 * s + 2].first = lazy[2 * s + 2].first ? 1 : 0;
				lazy[2 * s + 1].second += lazy[s].second;
				lazy[2 * s + 2].second += lazy[s].second;
			}
			lazy[s].second = 0;
		} else {
			segment[s].sum = (high - low + 1) * lazy[s].second;
			segment[s].sq = (high - low + 1) * lazy[s].second * lazy[s].second;
			if (low != high) {
				lazy[2 * s + 1].first = 0;
				lazy[2 * s + 2].first = 0;
				lazy[2 * s + 1].second = lazy[s].second;
				lazy[2 * s + 2].second = lazy[s].second;
			}
			lazy[s].second = 0;
		}
	}
	//total overlap
	if(left<=low&&right>=high)
		return segment[s];
	//partial overlap
	int mid=(low+high)/2;
	if(mid>=right)
		return query(segment,lazy,low,mid,left,right,2*s+1);
	else if(mid<left)
		return query(segment,lazy,mid+1,high,left,right,2*s+2);
	node l=query(segment,lazy,low,mid,left,right,2*s+1);
	node r=query(segment,lazy,mid+1,high,left,right,2*s+2);
	node temp;
	temp.merge(l,r);
	return temp;
}
int main() {
	int t;
	scanf("%d", &t);
	for (int l = 1; l <= t; l++) {
		printf("Case %d:\n",l);
		int n, q;
		scanf("%d%d",&n,&q);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		N = 2 * pow(2, ceil(log2(n))) - 1;
		node segment[N];
		pair<int, int> lazy[N];//lazy tree it store type of update and value
		build(a, segment, 0, n - 1, 0);
		while (q--) {
			int type, l, r;
			scanf("%d%d%d",&type,&l,&r);
			switch (type) {
			int x;
			case 0:
				//update for setting
				scanf("%d", &x);
				update(segment, lazy, 0, n - 1, l - 1, r - 1, x, 0, type);
				break;
			case 1:
				//update for incrementing
				scanf("%d", &x);
				update(segment, lazy, 0, n - 1, l - 1, r - 1, x, 0, type);
				break;
			case 2:
				//update for querying
				node temp = query(segment, lazy, 0, n - 1, l - 1, r - 1, 0);
				printf("%lld\n", temp.sq);
				break;
			}
		}
	}
	return 0;
}
