//计算[1-x]有多少个数最多只有3个位置不是0 
int num[20],len;
ll cal(int x,bool limit,int last){
	if(last == 0 || x>= len) return 1;
	if(limit&&num[x] == 0) return cal(x+1,limit,last);
	ll ans = 0;
	if(limit){
		//1 - num[x]-1 
		if(num[x] != 1) ans += (num[x]-1) * cal(x+1,false,last - 1);
		//0 
		if(num[x] != 0) ans += cal(x+1,false,last);
		ans += cal(x+1,true,last-1); 
	} else{
		ans += 9 * cal(x+1,false,last-1);
		ans += cal(x+1,false,last);
	}
	return ans;
}
ll solve(ll x){
	ll tmp[20],ps = 0;
	while(x){
		tmp[ps++] = x%10;
		x /= 10;
	}
	for(int i = 0;i < ps;i++){
		num[i] = tmp[ps-1-i];
	}
	len = ps;
	return cal(0,true,3); 
}

