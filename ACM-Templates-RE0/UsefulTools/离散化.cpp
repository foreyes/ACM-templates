//无去重离散化，新的下标从1开始，最大下标为_cnt 
 int idx[maxn],_cnt;
 inline int get_id(int x){
 	return lower_bound(idx+1,idx+_cnt+1,x) - idx; 
 }
 void discretize(int* f,int size){
 	for(int i = 1;i <= size;i++) idx[i] = f[i];
 	sort(idx+1,idx+size+1);
 	_cnt = size;
 }

 //去重离散化，新的下标从1开始，最大下标为_cnt 
 const int dis_maxn = 1e6+10;
 ll idx[dis_maxn], tmp_id[dis_maxn];
 int _cnt;
 int get_id(ll x){
 	return lower_bound(idx+1,idx+_cnt_1,x) - idx;
 }
 void discretize(ll f, int size){
 	_cnt = 0;
 	for(int i = 1;i <= n;i++) tmp_id[i] = f[i];
 	sort(tmp_id+1, tmp_id+size+1);
 	for(int i = 1;i <= size;i++){
 		if(i != 1 || tmp_id[i] != tmp_id[i-1]) idx[++_cnt] = tmp_id[i];
	}
} 
