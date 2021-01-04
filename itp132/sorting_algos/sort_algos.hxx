//
// Created by macarthur on 1/3/21.
//

#ifndef ITP232_SORT_ALGOS_HXX
#define ITP232_SORT_ALGOS_HXX
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

template <typename T> void bubble_sort( std::vector<T> &arr){
	bool swapped;
	for(size_t i=arr.size();i  > 0; i--){
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
	for(size_t i=1;i < arr.size();i++){
		size_t lowest = i;
		for(size_t j= i+1;j<arr.size(); j++){
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
	tmp.resize((mid-start)+(end-j));
	while(i <= mid && j <= end){
		if(v[i] <= v[j]){
			tmp[i]=v[i];
			i++;
		}
		else{
			tmp[j]=v[j];
			j++;
		}
	}
	while (i <= mid){
		tmp[i]=v[i];
		i++;
	}
	while( j <= end){
		tmp[j]=v[j];
		j++;
	}
	for(size_t i=start; i<= end; i++){
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
	_merge_sort(arr, 0, arr.size());
}
#endif //ITP232_SORT_ALGOS_HXX
