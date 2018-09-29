int main(){
	cin>>n;
	for(int i = 0;i < n;i++) cin>>a[i];
	memset(dp,0x3f,sizeof(dp));
	for(int i = 0;i < n;i++){
		*lower_bound(dp,dp+n,a[i]) = a[i];
	}
	cout<<lower_bound(dp,dp+n,0x3f3f3f3f) - dp - 1;
}
