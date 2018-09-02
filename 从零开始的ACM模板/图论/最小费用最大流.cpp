const int inf = 0x3f3f3f3f;
const int mm = 111111;
const int maxn = 999;
int node,src,dest,edge;
int ver[mm],flow[mm],cst[mm],nxt[mm];
int head[maxn],work[maxn],dis[maxn],q[maxn];
int tot_cost;
void prepare(int _node,int _src,int _dest){
    node=_node,src=_src,dest=_dest;
    for(int i=0; i<node; ++i)head[i]=-1;
    edge=0;
    tot_cost = 0;
}
void add_edge(int u,int v,int c,int cost){
    ver[edge]=v,flow[edge]=c,nxt[edge]=head[u],cst[edge]=cost,head[u]=edge++;
    ver[edge]=u,flow[edge]=0,nxt[edge]=head[v],cst[edge]=-cost,head[v]=edge++;
}
int ins[maxn];
int pre[maxn];
bool Dinic_spfa(){
    memset(ins,0,sizeof(ins));
    memset(dis,inf,sizeof(dis));
    memset(pre,-1,sizeof(pre));
    queue<int> Q;
    //int i,u,v,l,r=0;
    Q.push(src);
    dis[src] = 0,ins[src] = 1;
    pre[src] = -1;
    while(!Q.empty()){
        int u = Q.front();Q.pop();
        ins[u] = 0;
        for(int e = head[u];e != -1;e = nxt[e]){
            int v = ver[e];
            if(!flow[e]) continue;
            if(dis[v] > dis[u] + cst[e]){
                dis[v] = dis[u] + cst[e];
                pre[v] = e;
                if(!ins[v]) ins[v] = 1,Q.push(v);
            }
        }    	
    }
    return dis[dest] < inf;
}
int Dinic_flow(){
    int i,ret=0,delta=inf;
    while(Dinic_spfa()){
        for(int i=pre[dest];i != -1;i = pre[ver[i^1]])
    		delta = min(delta,flow[i]);
		for(int i=pre[dest];i != -1;i = pre[ver[i^1]])
    		flow[i] -= delta,flow[i^1] += delta;
		ret += delta;
		tot_cost += dis[dest]*delta;
    }
    return ret;
}
