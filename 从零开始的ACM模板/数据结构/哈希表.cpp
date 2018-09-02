struct hash_node{
	int val1,val2;
	hash_node* next;
};
const int MOD_hash = 4e6+7;
has_node* hash_table[MOD_hash];
//仅返回key值是否存在用于去重等操作,可修改为真正的hash表
bool check_and_add(int v1,int v2){
	//将v1范围控制在可以直接访问的范围 
	v1 = v1 % MOD_hash; 
	hash_node** p = &hash_table[v1];
	while(*p){
		if((*p)->val1 == v1 && (*p)->val2 == v2) return false;
		p = &((*p)->next);
	}
	*p = new node;
	(*p)->val1 = v1;
	(*p)->val2 = v2;
	(*p)->next = 0;
	return false;
}
/*
顺便提供一些[1e6, 1e7]的大质数
1000003 1999993
2000003 2999999
3000017 3999971
4000037 4999999
5000011 5999993
6000011 6999997
7000003 7999993
8000009 8999993
9000011 9999991
*/ 
