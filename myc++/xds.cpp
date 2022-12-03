#include<bits/stdc++.h>
using namespace std;
const int N = 200010;
long long ans[4*N],tag[4*N],a[N];
int n,m;
inline int ls(int x){
	return x * 2;
}
inline int rs(int x){
	return x * 2 + 1;
}
inline void push_up(int p){
	ans[p] = max(ans[ls(p)],ans[rs(p)]);
}
inline void build(int l,int r,int p){
	tag[p] = 0;
	if(l == r){
		ans[p] = a[l];
		return;
	}
	int mid = (l+r) / 2;
	build(l,mid,ls(p));
	build(mid+1,r,rs(p));
	push_up(p);
}
inline void f(int p,int l,int r,long long k){
	tag[p] += k;
	ans[p] += k * (r-l+1);
}
inline void push_down(int p,int l,int r){
	int mid = (l+r) / 2;
	f(ls(p),l,mid,tag[p]);
	f(rs(p),mid+1,r,tag[p]);
	tag[p] = 0;
}
inline void update(int p,int l,int r,int nl,int nr,long long k){
	if(nl <= l && r <= nr){
		ans[p] += k * (r-l+1);
		tag[p] += k;
		return;
	}
	push_down(p,l,r);
	int mid = (l+r) / 2;
	if(nl <= mid)update(ls(p),l,mid,nl,nr,k);
	if(mid + 1 <= nr)update(rs(p),mid+1,r,nl,nr,k);
	push_up(p);
}
long long query(int p,int l,int r,int nl,int nr){
	long long ret = 0;
	if(nl <= l && r <= nr) return ans[p];
	push_down(p,l,r);
	int mid = (l+r) / 2;
	if(nl <= mid) ret += query(ls(p),l,mid,nl,nr);
	if(mid + 1 <= nr) ret += query(rs(p),mid+1,r,nl,nr);
	return ret;
}
int main(){
	int op,x,y;
	long long k;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++)
		scanf("%lld",&a[i]);
	build(1,n,1);
	while(m--){
		scanf("%d",&op);
		if(op == 1){
			scanf("%d%d%lld",&x,&y,&k);
			update(1,1,n,x,y,k);
		}
		else{
			scanf("%d",&x);
			long long res = query(1,1,n,x,x);
			printf("%lld\n",res);
		}
	}
	return 0;
}
