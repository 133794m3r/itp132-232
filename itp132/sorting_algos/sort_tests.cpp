#include <algorithm>
#include <iostream>
#include "../vectors.hxx"
#include "sort_algos.hxx"
template <typename T, typename N> void print_arr(T *arr, N n) {
	N i;
	std::cout << "[";
	for (i=0; i < n; i++){
		if(i > 0)
			std::cout << ",";
		std::cout << arr[i];
	}
	std::cout << "]" << std::endl;
}

int main(){
	unsigned long long arr[10]={10,9,8,7,1,2,3,4,5,6};
	std::vector<int> vec={3,4,5,6,7,1,2,8,9,10};
	std::vector<int> vec2 = vec;
	print_arr(arr,10);
	bubble_sort(arr,10);
	print_arr(arr,10);
	std::cout << vec;
	bubble_sort(vec);
	std::cout << vec;
	vec = vec2;
	merge_sort(vec);
	std::cout << vec << std::endl;
	return 0;
}
