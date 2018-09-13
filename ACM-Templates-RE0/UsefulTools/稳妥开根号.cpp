ll my_sqrt(ll x){
	ll ret = sqrt(x);
	while((ret+1)*(ret+1) <= x) ++ret;
	while( ret*ret > y) --ret;
	return ret;
} 
