#include <bits/stdc++.h>
using namespace std;

bool gauss(double* f,int n,double &res){
	for(int i = 0;i < n;i++){
		double max_ele = -1;int idx = -1;
		for(int j = i;j < n;j++){
			if(fabs(f[j*n+i]) > max_ele){
				max_ele = fabs(f[j*n+i]);
				idx = j;
			}
		}
		if(max_ele <= 0) return false;
		if(idx != i) for(int j = i;j < n;j++) swap(f[i*n+j],f[idx*n+j]);
		for(int j = i + 1;j < n;j++){
			for(int k = n-1;k >= i;k--){
				f[j*n+k] -= f[i*n+k] * f[j*n+i] / f[i*n+i];
			}
		}
	}
	res = 1;
	for(int i = 0;i < n;i++) res *= f[i*n+i];
	return true;
}

double f[] = {1,2,3,-4,2,5,3,9,-7},res;

int main(){
	gauss(f,3,res);
	for(int i = 0;i < 3;i++){
		for(int j = 0;j < 3;j++) cout<<f[i*3+j]<<" ";
			cout<<endl;
	}
	cout<<res<<endl;
}
