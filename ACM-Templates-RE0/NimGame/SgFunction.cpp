//DFS��SG������ǰ���ǲ�����ѭ������(��) 
int DFS(int x){
	if(sg[x] != -1) return sg[x];
	set<int> s;
	for(new status nx by x){
		if(!check(nx)) continue;
		s.insert(DFS(nx));
	}
	int tmp = 0;
	while(s.count(tmp)) tmp++;
	return sg[x] = tmp;
}
