long long exGcd(long long a,long long b,long long &d,long long &x,long long &y) {
    if(b == 0) {
    	d=a;x=1;y=0;
    } else {
    	gcd(b,a%b,d,y,x);
    	y-= x*(a/b);
    }
}

long long inverse(long long a, long long b) {
	long long x, y, d;
	exGcd(a, b, d, x, y);
	if(d != 1) return -1;
	return x;
}
