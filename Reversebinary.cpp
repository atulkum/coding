#import <iostream>
int main(){
	unsigned int N;
	std::cin >> N;
	
	unsigned int ret;
	while(N != 0){
		ret |= (N & 0x1);
		N = N >> 1;
		if(N != 0){
			ret = ret << 1;
		}	
	}
	std::cout << ret << std::endl;
	return 1;
}
