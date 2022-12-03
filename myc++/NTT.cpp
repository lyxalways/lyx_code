#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const int G = 3;
const int GI = 332748118;
const int N = (1<<18)+5000;
int rn,r[N];
inline int add(int a,int b){
	int c = a+b;
	if(c > MOD)
		c-= MOD;
	return c;
}
inline int sub(int a,int b){
	int c = a-b;
	if(c < 0) 
		c += MOD;
	return c;
}
inline int time(int a,int b){
	return 1ll * a * b % MOD;
}
inline int fp(int a,int b)
{
	int k = a,ans = 1;
	while(b > 0) {
		if(b%2==1) 
			ans = time(ans,k);
		b /= 2;
		k = time(k,k);
	}
	return ans;
}
inline void rev(int lim){
	for(int i = 0; i < lim; i++) {
		r[i] = r[i/2]/2;
		if(i % 2 ==1) {
			r[i] += lim / 2;
		}
	}
	rn = lim;
}
struct dxs {
	vector<int>f;
	int len;
	dxs() {};
	dxs(int n){
		f.resize(n+1);
		len = n;
	}
	void read() {
		scanf("%d",&len);
		len--;
		f.resize(len+1);
		for(int i = 0; i <= len; i++)
			scanf("%d",&f[i]);
	}
	void print() {
		for(int i = 0; i <= len; i++)
			printf("%d ",f[i]);
		putchar('\n');
	}
	void turn() {
		for(int i = 0; i <= len; i++)
			if(i < r[i])
				swap(f[i],f[r[i]]);
	}
	dxs mod(int n) {
		dxs tmp = *this;
		tmp.f.resize(n);
		tmp.len = n-1;
		return tmp;
	}
	dxs NTT(int d,int l) const {
		if(l != rn) rev(l);
		dxs tmp = *this;
		tmp = tmp.mod(l);
		tmp.turn();
		for(int ll = 2; ll <= l; ll *= 2) {
			int hl = ll / 2;
			int w1 = fp(d==1?G:GI,(MOD-1)/ll);
			for(int rk = 0; rk < l; rk += ll) {
				int w = 1;
				for(int nd = rk; nd < rk+hl; nd++) {
					int t1 = tmp.f[nd],t2 = time(w,tmp.f[nd+hl]);
					tmp.f[nd] = add(t1,t2),tmp.f[nd+hl] = sub(t1,t2);
					w = time(w,w1);
				}
			}
		}
		return tmp;
	}
	dxs operator + (const dxs &tmp) const {
		dxs nw(max(len,tmp.len));
		int i = 0,j = 0;
		while(i <= len && j <= tmp.len){
			nw.f[i] = add(f[i],tmp.f[j]);
			i++;j++;
		}
		while(i <= len) nw.f[i] = f[i],i++;
		while(j <= tmp.len) nw.f[j] = tmp.f[j],j++;
		return nw;
	}
	dxs operator - (const dxs &tmp) const {
		dxs nw(max(len,tmp.len));
		int i = 0,j = 0;
		while(i <= len && j <= tmp.len){
			nw.f[i] = sub(f[i],tmp.f[j]);
			i++;j++;
		}
		while(i <= len) nw.f[i] = f[i],i++;
		while(j <= tmp.len) nw.f[j] = sub(0,tmp.f[j]),j++;
		return nw;
	}
	dxs operator * (const int &tmp) const {
		dxs nw = *this;
		for(int i = 0; i <= nw.len; i++)
			nw.f[i] = time(nw.f[i],tmp);
		return nw;
	}
	dxs operator * (const dxs &tmp) const {
		int l;
		for(l = 1; l <= (len + tmp.len + 1); l *= 2);
		dxs nw1 = this->NTT(1,l);
		dxs nw2 = tmp.NTT(1,l);
		dxs ans(l-1);
		for(int i = 0; i < l; i++)
			ans.f[i] = time(nw1.f[i],nw2.f[i]);
		ans = ans.NTT(-1,l);
		int inv = fp(l,MOD-2);
		for(int i = 0; i < l; i++)
			ans.f[i] = time(ans.f[i],inv);
		ans = ans.mod(len+tmp.len+1);
		return ans;
	}
	dxs INV() {
		dxs b(0);
		int lim = 2;
		b.f[0] = fp(f[0],MOD-2);
		while(lim <= len*2) {
			b = b*2-(b*b*(this->mod(lim))).mod(lim);
			lim *= 2;
		}
		return b.mod(this->len+1);
	}
};
int main(){
	dxs a,b;
	a.read();
	b = a.INV();
	b.print();
	getchar();getchar();
	return 0;
}