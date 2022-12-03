#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+50;
const int M = 3e7+1000;
int a[N],pos[N],qa[N],qb[N];
int rt[N],t[M],rs[M],ls[M];
int n,m,tot,ca,cb,x;
long long ans;
inline int low(int n){
	return n & (-n);
}
void change(int& p,int l,int r,int x,int y){
	if(p == 0) p = ++tot;
	t[p] += y;
	if(l == r) return;
	int mid = (l+r) / 2;
	if(x <= mid) change(ls[p],l,mid,x,y);
	else change(rs[p],mid+1,r,x,y);
}
long long query(int l,int r,int x,bool h){
	for(int i = l-1;i > 0;i -= low(i)) qa[++ca] = rt[i];
	for(int i = r;i > 0;i -= low(i)) qb[++cb] = rt[i];
	int ll = 1,rr = n,mid;
	long long ret = 0;
	while(ll != rr){
		mid = (ll+rr)/2;
		if(x <= mid){
			if(h){
				for(int i = 1;i <= ca;i++) ret -= t[rs[qa[i]]];
				for(int i = 1;i <= cb;i++) ret += t[rs[qb[i]]];
			}
			for(int i = 1;i <= ca;i++) qa[i] = ls[qa[i]];
			for(int i = 1;i <= cb;i++) qb[i] = ls[qb[i]];
			rr = mid;
		}
		else{
			if(!h){
				for(int i = 1;i <= ca;i++) ret -= t[ls[qa[i]]];
				for(int i = 1;i <= cb;i++) ret += t[ls[qb[i]]];
			}
			for(int i = 1;i <= ca;i++) qa[i] = rs[qa[i]];
			for(int i = 1;i <= cb;i++) qb[i] = rs[qb[i]];
			ll = mid+1;
		}
	}
	ca = cb = 0;
	return ret;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
		pos[a[i]] = i;
		ans += query(1,i-1,a[i],1);
		for(int j = i;j <= n;j += low(j)) change(rt[j],1,n,a[i],1);
	}
	// for(int i = 1;i <= n;i++) printf("%d ",pos[i]);
	// putchar('\n');
	printf("%lld\n",ans);
	for(int i = 1;i < m;i++){
		scanf("%d",&x);
		ans -= query(1,pos[x]-1,x,1);
		ans -= query(pos[x]+1,n,x,0);
		printf("%lld\n",ans);
		for(int j = pos[x];j <= n;j += low(j)) change(rt[j],1,n,x,-1);
	}
	return 0;
}