#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+1000;
int t[N],l[N];
int n;
stack<int>stk;

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)
		scanf("%d",&t[i]);
	for(int i = 1;i <= n;i++)
		scanf("%d",&l[i]);
	int now = t[1];
	for(int i = 1;i <= n;i++){
		while(t[i] <= now && i <= n) stk.push(i),i++; 
		while((i >= n || now < t[i])&&(!stk.empty())){
			printf("%d ",stk.top());
			now+=l[stk.top()];
			stk.pop();
		}
	}
	getchar();getchar();getchar();
	return 0;
}