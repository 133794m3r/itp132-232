//
// Created by macarthur on 1/3/21.
//

#ifndef ITP232_SORT_ALGOS_HXX
#define ITP232_SORT_ALGOS_HXX

#include <memory>

template <typename T> void bubble_sort(T *arr, size_t len){
	bool swapped;
	for(size_t i=len;i  > 0; i--){
		for(size_t j=0;j<i-1;j++){
			if(arr[j] > arr[j+1]){
				std::swap(arr[j],arr[j+1]);
				swapped = true;
			}
		}
		if(!swapped) break;
	}
}

template <typename T> void insert_sort(T &arr, size_t len){
	T cur;
	size_t j=0;
	for(size_t i=1;i < len;i++){
		cur = arr[i];
		for(j=i-1;j>=0 && arr[j] > cur; j--){
			arr[j+1] = arr[j];
		}
		arr[j+1] = cur;
	}
}
template <typename T> void select_sort(T &arr, size_t len){
	for(size_t i=0;i<len;i++){
		size_t lowest = i;
		for(size_t j=i+1;j<len; j++){
			if(arr[j] < arr[lowest]){
				lowest = j;
			}
		}
		if(i!=lowest){
			std::swap(arr[i],arr[lowest]);
		}
	}
}

template <typename T> void merge_(T *v, const size_t start, const size_t mid, const size_t end){
	size_t i = start;
	size_t j = mid+1;
	size_t n = 0;
	std::unique_ptr<T[]> tmp(new T[(end-start)+1]());

	while(i <= mid && j <= end){
		if(v[i] <= v[j]){
			tmp[n++]=v[i];
			i++;
		}
		else{
			tmp[n++]=v[j];
			j++;
		}
	}

	while (i <= mid){
		tmp[n++]=v[i];
		i++;
	}

	while( j <= end){
		tmp[n++]=v[j];
		j++;
	}

	for(i=start; i<= end; i++){
		v[i] = tmp[i-start];
	}
}

template <typename T> void _merge_sort(T *arr,size_t start, size_t end){
	if(start < end){
		size_t mid = (start+end)/2;
		_merge_sort(arr,start,mid);
		_merge_sort(arr,mid+1,end);
		merge_(arr,start,mid,end);
	}
}

template <typename T> void merge_sort(T *arr, size_t len){
	_merge_sort(arr, 0, len-1);
}

//vector templates
template <typename T> void bubble_sort( std::vector<T> &arr){
	bool swapped;
	for(size_t i=arr.size();i >0; i--){
		for(size_t j=0;j<i-1;j++){
			if(arr[j] > arr[j+1]){
				std::swap(arr[j],arr[j+1]);
				swapped = true;
			}
		}
		if(!swapped) break;
	}
}

template <typename T> void insert_sort(std::vector<T> &arr){
	T cur;
	size_t j=0;
	for(size_t i=1;i < arr.size();i++){
		cur = arr[i];
		for(j= i -1;j>=0 && arr[j] > cur; j--){
			arr[j+1] = arr[j];
		}
		arr[j+1] = cur;
	}
}

template <typename T> void select_sort(std::vector<T> &arr){
	size_t len = arr.size();
	for(size_t i=0;i < len;i++){
		size_t lowest = i;
		for(size_t j= i+1;j<len; j++){
			if(arr[j] < arr[lowest]){
				lowest = j;
			}
		}
		if(i != lowest){
			std::swap(arr[i],arr[lowest]);
		}
	}
}

template <typename T> void merge_(std::vector<T> &v, size_t start, size_t mid, size_t end){
	size_t i = start;
	size_t j = mid+1;
	std::vector<T> tmp;
	tmp.reserve((end-start)+1);
	while(i <= mid && j <= end){

		if(v[i] <= v[j]){
			tmp.push_back(v[i]);
			i++;
		}
		else{
			tmp.push_back(v[j]);
			j++;
		}
	}
	while (i <= mid){
		tmp.push_back(v[i]);
		i++;
	}
	while( j <= end){
		tmp.push_back(v[j]);
		j++;
	}
	for(i=start; i<= end; ++i){
		v[i] = tmp[i-start];
	}
}

template <typename T> void _merge_sort(std::vector<T> &arr,size_t start, size_t end){
	if(start < end){
		size_t mid = (start+end)/2;
		_merge_sort(arr,start,mid);
		_merge_sort(arr,mid+1,end);
		merge_(arr,start,mid,end);
	}
}

template <typename T> void merge_sort(std::vector<T> &arr){
	_merge_sort(arr, 0, arr.size()-1);
}
#endif //ITP232_SORT_ALGOS_HXX
