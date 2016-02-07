//BRCKTS.cpp
//http://www.spoj.com/problems/BRCKTS/
//author:leninkumar
//accepted code
#include <bits/stdc++.h>
#define MAX 30005
using namespace std;
typedef struct node {
	int left;//left stores no of unmatched open braces
	int right;//right stores no of unmatched closed braces
	void merge(node l, node r) {
		int same = min(l.left, r.right);
		left = l.left + r.left - same;
		right = l.right + r.right - same;
	}
} node;
char ch[MAX];
node build(node segment[],int low, int high, int s) {
	//for leaf nodes
	if (low == high) {
		if (ch[low] == '(') {
			segment[s].left = 1;
			segment[s].right = 0;
		} else {
			segment[s].left = 0;
			segment[s].right = 1;
		}
		return segment[s];
	}
	int mid = (low + high) / 2;
	node l = build(segment,low, mid, 2 * s + 1);//left part
	node r = build(segment,mid + 1, high, 2 * s + 2);//right part
	segment[s].merge(l, r);
	return segment[s];
}
void update(node segment[],int low, int high, int pos, int s) {
	//if pos is not between low and high
	if(pos>high||pos<low)
		return ;
	//for leaf nodes
	if (low == pos && high == pos) {
		//updating original string and leaf nodes of segment
		if (ch[pos] == ')') {
			ch[pos] = '(';
			segment[s].left = 1;
			segment[s].right = 0;
		} else {
			ch[pos] = ')';
			segment[s].left = 0;
			segment[s].right = 1;
		}
		return;
	}
	int mid = (low + high) / 2;
	if (pos > mid)//right part
		update(segment,mid + 1, high, pos, 2 * s + 2);
	else//left part
		update(segment,low, mid, pos, 2 * s + 1);
	segment[s].merge(segment[2 * s + 1], segment[2 * s + 2]);//updating node values
}
int main() {
	int n;//size of string
	int count=1;//this is for testcase number
	while (scanf("%d", &n) != EOF) {
		printf("Test %d:\n",count);
		scanf("%s", ch);
		int N=2*pow(2,ceil(log2(n)))-1;//calculating no of nodes in segment tree
		node segment[N];
		build(segment,0, n - 1, 0);//buiding segment tree
		int q;
		scanf("%d", &q);
		while (q--) {
			int k;
			scanf("%d", &k);
			if (k) {
				update(segment,0, n - 1, k - 1, 0);//for updates
			} else {
				//if k==0 we need to print that string is correct bracket word or not
				if (segment[0].left == 0 && segment[0].right == 0)
					printf("YES\n");
				else
					printf("NO\n");
			}
		}
		count++;
	}
	return 0;
}
