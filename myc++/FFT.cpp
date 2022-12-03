#include <bits/stdc++.h>
using namespace std;
const int N = 4e6+50;
const double PI = acos(-1.0);
int l,n,m,r[N],ans[N];
string s1,s2;
int read(){
    int s=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=s*10+ch-'0';
        ch=getchar();
    }
    return s*f;
}
struct cp{
    double r,i;
    cp (double _r = 0,double _i = 0) {r = _r, i = _i;}
    cp operator + (const cp &tmp) {return cp(r+tmp.r,i+tmp.i);}
    cp operator - (const cp &tmp) {return cp(r-tmp.r,i-tmp.i);}
    cp operator * (const cp &tmp) {return cp(r*tmp.r-i*tmp.i,r*tmp.i+i*tmp.r);}
};
cp f[N],g[N];
void init(){
    cin >> s1 >> s2;
    n = s1.length()-1;
    m = s2.length()-1;
    for(int i = 0;i <= n;i++) f[i].r = s1[n-i]-'0';
    for(int i = 0;i <= m;i++) g[i].r = s2[m-i]-'0';
    for(l = 1;l < n+m+1;l *= 2);
    for(int i = 0;i < l;i++){
        if(i % 2 == 0) r[i] = r[i/2] / 2;
        else r[i] = r[i-1] + l/2;
    }
}

void FFT (cp f[],int d){
    for(int i = 0;i < l;i++)
        if(i < r[i]) swap(f[i],f[r[i]]);
    for(int len = 2;len <= l;len *= 2){
        int hl = len / 2;
        cp w1,w = cp(cos(2*PI/len),d*sin(2*PI/len));
        for(int st = 0;st < l;st += len){
            w1 = cp(1,0);
            for(int nd = st;nd < st+hl;nd++){
                cp t1 = f[nd],t2 = w1 * f[nd+hl];
                f[nd] = t1 + t2,f[nd+hl] = t1 - t2;
                w1 = w1 * w;
            }
        }
    }
    
}

void solve(){
    FFT(f,1);FFT(g,1);
    for(int i = 0;i < l;i++) f[i] = f[i] * g[i];
    FFT(f,-1);
    for(int i = 0;i <= n+m;i++)
        ans[i] = (int)(f[i].r/l+0.5);
    for(int i = 0;i <= n+m;i++){
        ans[i+1] += ans[i] / 10;
        ans[i] %= 10;
    }
    bool flag = 0;
    for(int i = n+m+1;i >= 0;i--){
        if(flag==0&&ans[i]==0)continue;
        flag = 1;
        printf("%d",ans[i]);
    }
}

int main(){
    init();
    solve();
    getchar();getchar();getchar();
    return 0;
}