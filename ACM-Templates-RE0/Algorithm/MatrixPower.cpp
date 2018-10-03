#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1e9+7;

struct Mat{
	int size;
	vector<vector<ll> > a;
	Mat(int size = 3):size(size){}
	void setZero(){
		for(int i = 0;i < size;i++){
			vector<ll> tmp(size);
			for(int j = 0;j < size;j++){
				tmp[j] = 0;
			}
			a.push_back(tmp);
		}
	}
	void setUnit(){
		setZero();
		for(int i = 0;i < size;i++) a[i][i] = 1;
	}
	vector<ll>& operator[](size_t n){
		return a[n];
	} 
	Mat operator*(Mat& tar){
		Mat ret(size);
		ret.setZero();
		for(int i = 0;i < size;i++){
			for(int j = 0;j < size;j++){
				for(int k = 0;k < size;k++){
					ret[i][j] = (ret[i][j] + a[i][k] * tar[k][j])%MOD;
				}
			}
		}
		return ret;
	}
};

Mat matPow(Mat a,ll b){
	Mat ret(a.size);
	ret.setUnit();
	while(b){
		if(b & 1) ret = ret * a;
		a = a * a;
		b >>= 1;
	}
	return ret;
}

Mat init(){
	Mat ret(9);
	ret.setZero();
	ret[0][1] = ret[0][2] = 1;
	ret[1][4] = ret[1][5] = 1;
	ret[2][7] = ret[2][8] = 1;
	ret[3][0] = ret[3][1] = 1;
	ret[4][3] = ret[4][5] = 1;
	ret[5][6] = ret[5][7] = ret[5][8] = 1;
	ret[6][0] = ret[6][2] = 1;
	ret[7][3] = ret[7][4] = ret[7][5] = 1;
	ret[8][6] = ret[8][7] = 1;
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	ll n,T;
	cin>>T;
	while(T--){
		cin>>n;
		if(n == 1){
			cout<<3<<endl;
			continue;
		}
		if(n == 2){
			cout<<9<<endl;
			continue;
		}
		Mat M = init();
		M = matPow(M,n-2);
		ll ans = 0;
		for(int i = 0;i < 9;i++){
			for(int j = 0;j < 9;j++)
				ans = (ans + M[i][j]) % MOD;
		}
		cout<<ans<<endl;
	} 
	return 0;
}
