#include <iostream>
/*
* Array Sorting and Searching Demo
* By Macarthur Inbody <admin-contact@transcendental.us> 2020
* Licensed AGPLv3
*/
/*
* Binary Search algorithm utilizing a super power(recursion).
* takes array as input, starting point, max point, and the key to find.
* template overuse shows that I am a real C++ programmer.
* T is the unsigned int, char, int, unsigned char etc data type. K is the search key which is it's own type which is the key. Can be any of the words or IEEE754 types.
*/
template <typename T, typename S, typename K> T bin_search(S *arr,T l, T h, K x){
	//as long as the lower point is less than or equal to the 
	//high we're still able to search.
	if(l<=h){
		//set the midpoint to be l+h/2. The type is the same type as our low and high data type.
		T m=(l+h)/2;		
		//get the current value. The value should be the same type as our key.
		//for floating points you have to be careful due to floating point rounding.
		K cur=arr[m];
		// if key is equal to that value then we have the index.
		if(x == cur){
			//return the middle.
			return m;
		}
		//otherwise if current value is greater than x then we have went past it.
		else if(cur > x){
			//set the highest to the middle minus 1.
			h=m-1;
		}
		//otherwise we set low ot the middle+1 as we're lower than it.
		else{
			l=m+1;
		}
		//call it again with the new low and high.
		return bin_search(arr,l,h,x);
	}
	//if we ever reach this point the value wasn't found.
	//thus the index is -1.
	return -1;

}

//swap the first value with the second.
//by using * we're getting the actual value itself by de-refencing it.
template <typename T> void swap(T *a, T *b){
	T t = *a;
	*a = *b;
	*b = t;
}

//the over use of templates shows that it's a true C++ program.
template <typename T, typename N> N part(T *arr, N low, N high){
    N pivot = arr[high];// pivot 
    N i = (low - 1);  // Index of smaller element 
	N j;
	//iterate over the entire thing.
    for(j = low; j <= high- 1; j++){
		//if the current value is less than the pivot value we saw before
        if (arr[j] < pivot){
			//it means we need to swap them to get them sorted.
			//pass by value of the pointer.
            swap(&arr[++i], &arr[j]); 
        } 
    }
    swap(&arr[i + 1], &arr[high]);
	//return the index value of i plus 1.
    return (i + 1); 
}

//here's the real quicksort implementation.
template <typename T, typename N >void qsrt(T *arr, N low, N high){
	//if the lower point is less than our high time to keep going.
    if (low < high){ 
		//get the partition index so that we can sort it in replace.
        int pi = part(arr, low, high); 
		//quick sort the items before the middle of the partition.
        qsrt(arr, low, pi - 1); 
		//quick sort the items after the partition index.
        qsrt(arr, pi + 1, high); 
    }
}

//normally quick sort requires the person to pass to it a end point that's one less
//than the length. This way they can just pass the length to us.
template <typename T, typename N> void quick_sort(T *arr, N start, N length){
	qsrt(arr,start,length-1);
}

//have to use templates for _everything_.
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
	//our unsorted array.
	int int_arr[13]={2,3,4,5,6,7,10,8,9,0,1,70,75};
	//showing that it also works with strings.
	char str_arr[10]="93ZAzy";
	//double array.
	double fp_arr[10]={1.1,2.1,3.1,4.1,5.1,6.1,0.1,-1.1,-2.1,-3.1};
	
	//showing int arrays.
	//print the array.
	std::cout << "Unsorted Int Array: ";
	print_arr(int_arr,13);
	//quicksort it.
	quick_sort(int_arr,0,13);
	//print the sorted array.
	std::cout << "Sorted Int Array: ";
	print_arr(int_arr,13);
	
	//now with c-style strings.
	std::cout << "Unsorted Str Array: ";
	print_arr(str_arr,9);
	quick_sort(str_arr,0,9);
	std::cout << "Sorted Str Array: ";
	print_arr(str_arr,9);
	
	//now with floating points.
	std::cout << "Unsorted Double Array: ";
	print_arr(fp_arr,9);
	quick_sort(fp_arr,0,9);
	std::cout << "Sorted Double Array: ";
	print_arr(fp_arr,9);
	
	//get the values we want to find.
	int arr_keys[5]={3,7,11,70,10};
	//the index of it has to be int so that it can be signed.
	int arr_index;
	//output the index of all of the keys.
	std::cout << "Indexes of keys: " << std::endl;
	//loop over every key and print index.
	for(int key:arr_keys){
		//search for it.
		arr_index=bin_search(int_arr,0,12,key);
		//say what the key is.
		std::cout << "Key: " << key;	
		//key wasn't found.
		if(arr_index != -1)
			std::cout << " found at index: " << arr_index <<  "." << std::endl;
		//or it was.
		else
			std::cout << " not found." << std::endl;
	}
	
	return 0;
}
