#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2550;
const int M = 20010;
const int inf = 1e9+7;
int head[N],nxt[M],to[M];
int E;
void init(){
	E = 0;
	memset(head,-1,sizeof(head));
}
void add(int x,int y){
	E++;
	to[E] = y;
	nxt[E] = head[x];
	head[x] = E;
}
int n,m,k,x,y;
ll num[N];
int way[N][N];
void bfs(){
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			way[i][j] = inf;
		}
	}
	for(int i = 1;i <= n;i++){
		queue<int>q;
		way[i][i] = 0;
		q.push(i);
		while(!q.empty()){
			int f = q.front();
			q.pop();
			for(int j = head[f];j != -1;j = nxt[j]){
				if(way[i][to[j]] == inf){
					way[i][to[j]] = way[i][f]+1;
					q.push(to[j]);
				}
			}
		}
	}
}
bool book[N];
struct node{
	int p;
	ll nm;
	bool operator<(const node& tmp)const{
		return nm > tmp.nm;
	}
};
vector<node> vt[N];
int main(){
	//freopen("holiday.in","r",stdin);
	//freopen("holiday.out","w",stdout);
	init();
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 2;i <= n;i++)
		scanf("%lld",&num[i]);
	for(int i = 1;i <= m;i++){
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	bfs();
	for(int i = 2;i <= n;i++){
		for(int j = 2;j <= n;j++)if(i != j){
			if(way[1][j] <= k+1 && way[i][j] <= k+1){
				node tmp = {j,num[j]};
				vt[i].push_back(tmp);
			}
		}
		sort(vt[i].begin(),vt[i].end());
	}
	ll ans = 0;
	for(int i = 2;i <= n;i++){
		book[i-1] = book[n]  = 0;
		for(int j = i+1;j <= n;j++)if(way[i][j] <= k+1){
			book[i] = book[j-1] = 0;
			book[i] = book[j] = 1;
			int t = 0;
			int w = 0;
			while(t < vt[i].size()&&book[vt[i][t].p]==1)t++;
			if(t == vt[i].size()) continue;
			while(w < vt[j].size()&&book[vt[j][w].p]==1)w++;
			if(w == vt[j].size()) continue;
			if(vt[i][t].p != vt[j][w].p){
				ans = max(ans,num[i]+num[j]+vt[i][t].nm+vt[j][w].nm);
				continue;
			}
			long long mmmm = vt[i][t].nm;
			t++;
			w++;
			while(t < vt[i].size()&&book[vt[i][t].p]==1)t++;
			while(w < vt[j].size()&&book[vt[j][w].p]==1)w++;
			if(t == vt[i].size()&&w==vt[j].size()) continue;
			else if(t == vt[i].size()) ans = max(ans,num[i]+num[j]+mmmm+vt[j][w].nm);
			else if(w == vt[j].size()) ans = max(ans,num[i]+num[j]+vt[i][t].nm+mmmm);
			else ans = max(ans,num[i]+num[j]+max(vt[i][t].nm,vt[j][w].nm)+mmmm);
		}
	}
	printf("%lld\n",ans);
	return 0;
}