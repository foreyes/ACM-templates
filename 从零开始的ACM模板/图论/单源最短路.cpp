void dijkstra(int st){
	priority_queue<pll> q;
	for(int i = 1;i <= n;i++) dist[i] = 1e18+10;
	dist[st] = 0;q.push(mp(0,st));
	while(!q.empty()){
		pll cur = q.top();q.pop();
		if(dist[cur.se] != -cur.fi) continue;
		for(pll p : G[cur.se]){
			if(dist[p.fi] > dist[cur.se] + p.se){
				dist[p.fi] = dist[cur.se] + p.se;
				q.push(mp(-dist[cur.se],cur.se))
			}
		}
	}
}
bool spfa(int st){
	ll cnt[maxn] = {0},sqrtn = sqrt(n) + 1;
	queue<pll> q;
	for(int i = 1;i <= n;i++) dist[i] = 1e18+10;
	dist[st] = 0;q.push(mp(0,st));
	while(!q.empty()){
		pll cur = q.front();q.pop();
		if(++cnt[cur] > sqrtn) return false;
		for(pll p : G[cur.se]){
			if(dist[p.fi] > dist[cur.se] + p.se){
				dist[p.fi] = dist[cur.se] + p.se;
				q.push(mp(dist[cur.se],cur.se));
			}
		}
	}
	return true;
}
