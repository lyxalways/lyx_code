#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const int G = 3;
const int GI = 332748118;
const int N = (1<<15)+5000;
int rn,r[N];
inline int fp(int a,int b)
{
	int k = a,ans = 1;
	while(b > 0) {
		if(b%2==1) {
			ans = 1ll * ans * k % MOD;
		}
		b /= 2;
		k = 1ll * k * k % MOD;
	}
	return ans;
}
inline int add(int a,int b)
{
	int c = a+b;
	if(c > MOD) {
		c-= MOD;
	}
	return c;
}
inline int sub(int a,int b)
{
	int c = a-b;
	if(c < 0) {
		c+= MOD;
	}
	return c;
}
inline int time(int a,int b)
{
	return 1ll * a * b % MOD;
}
inline void rev(int lim)
{
	for(int i = 0; i < lim; i++) {
		r[i] = r[i/2]/2;
		if(i % 2 ==1) {
			r[i] += lim / 2;
		}
	}
	rn = lim;
}
struct dxs {
	int f[N];
	int len;
	dxs() {
		memset(f,0,sizeof(f));
		len = 0;
	};
	void read() {
		scanf("%d",&len);
		this->len-=1;
		for(int i = 0; i <= len; i++) {
			scanf("%d",&f[i]);
		}
	}
	void print() {
		for(int i = 0; i <= len; i++) {
			printf("%d ",f[i]);
		}
		putchar('\n');
	}
	void turn() {
		for(int i = 0; i <= len; i++)
			if(i < r[i]) {
				swap(f[i],f[r[i]]);
			}
	}
	dxs mod(int n) {
		dxs tmp;
		tmp.len = n-1;
		for(int i = 0; i <= n-1; i++) {
			tmp.f[i] = f[i];
		}
		return tmp;
	}
	dxs NTT(int d,int l) const {
		if(l != rn) {
			rev(l);
			rn = l;
		}
		dxs tmp = *this;
		tmp.len = l-1;
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
		dxs nw;
		nw.len = max(len,tmp.len);
		for(int i = 0; i <= nw.len; i++) {
			nw.f[i] = add(f[i],tmp.f[i]);
		}
		return nw;
	}
	dxs operator - (const dxs &tmp) const {
		dxs nw;
		nw.len = max(len,tmp.len);
		for(int i = 0; i <= nw.len; i++) {
			nw.f[i] = sub(f[i],tmp.f[i]);
		}
		return nw;
	}
	dxs operator * (const int &tmp) const {
		dxs nw = *this;
		for(int i = 0; i <= nw.len; i++) {
			nw.f[i] = time(nw.f[i],tmp);
		}
		return nw;
	}
	dxs operator * (const dxs &tmp) const {
		int l;
		for(l = 1; l <= (len + tmp.len + 1); l *= 2);
		dxs nw1 = this->NTT(1,l);
		dxs nw2 = tmp.NTT(1,l);
		dxs ans;
		for(int i = 0; i < l; i++) {
			ans.f[i] = time(nw1.f[i],nw2.f[i]);
		}
		ans = ans.NTT(-1,l);
		int inv = fp(l,MOD-2);
		for(int i = 0; i < l; i++) {
			ans.f[i] = time(ans.f[i],inv);
		}
		ans.len = len + tmp.len;
		return ans;
	}
	dxs INV() {
		dxs b[2];
		int cur = 0,bas = 1,lim = 2;
		b[cur].f[0] = fp(this->f[0],MOD-2);
		while(bas <= this->len) {
			cur ^= 1;
			b[cur] = b[cur^1] * 2;
			b[cur^1] = ((b[cur^1] * b[cur^1]).mod(lim) * (this->mod(lim))).mod(lim);
			b[cur] = b[cur] - b[cur^1];
			bas *= 2;
			lim *= 2;
		}
		return b[cur].mod(this->len+1);
	}
};
int main()
{
	dxs a,b;
	a.read();
	b = a.INV();
	b.print();
	return 0;
}
