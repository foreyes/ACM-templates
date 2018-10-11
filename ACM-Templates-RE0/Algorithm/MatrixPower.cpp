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
