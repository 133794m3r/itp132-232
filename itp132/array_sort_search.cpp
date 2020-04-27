#include <iostream>

typedef unsigned int uint32;
//binary search algorithm recursive version.
/*
* takes array as input, starting point, max point, and the key to find.
*/
int bin_search(int *arr,int l=0,int h,int x){
	//as long as the lower point is less than or equal to the 
	//high we're still able to search.
	if(l<=h){
		//set the midpoint to be l+h/2.
		int m=(l+h)/2;
		//get the current value.
		int cur=arr[m];
		// if key is equal to that value then we have the index.
		if(x == cur){
			//return the middle.
			return m;
		}
		//othwerise if current value is greater than x then we have went past it.
		else if(cur > x){
			//set the highest to the middle minus 1.
			h=m-1;
		}
		//othwerise we set low ot the middle+1 as we're lower than it.
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
//by using * we're getting the actual value itself by derefencing it.
void swap(int *a, int *b) { 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
//the partition function of quick sort. Takes low and high, plus array.
int part (int *arr, int low = 0, int high){ 
    int pivot = arr[high];// pivot 
    int i = (low - 1);  // Index of smaller element 
	int j=0; //start j as zero.
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
  
//quick sort function. Sorts in place.
void quick_sort(int *arr, int low=0, int high){ 
	//if the lower point is less than our high time to keep going.
    if (low < high){ 
		//get the partition index so that we can sort it in replace.
        int pi = part(arr, low, high); 
		//quick sort the items before the middle of the partition.
        quick_sort(arr, low, pi - 1); 
		//quick sort the items after the partition index.
        quick_sort(arr, pi + 1, high); 
    }
} 


int main(){
	//our unsorted array.
	int arr[13]={2,3,4,5,6,7,10,8,9,0,1,70,75};
	uint32 i=0;
	//print the array.
	std::cout << "Unsorted Array: [";
	for(uint32 x:arr){
		if(i>=1)
			std::cout << ",";
		i++;
		std::cout << x;
	}
	std::cout << "]" << std::endl;
	
	//quicksort it.
	quick_sort(arr,0,12);
	//print the sorted array.
	std::cout << "Sorted Array: [";
	i=0;
	for(uint32 x:arr){
		if(i>=1)
			std::cout << ",";
    i++;
		std::cout << x;
	}	
	std::cout << "]" << std::endl;
	//get the values we want to find.
	int arr_keys[5]={3,7,11,70,10};
	//the index of it has to be int so that it can be signed.
	int arr_index=0;
	//output the index of all of the keys.
	std::cout << "Indexes of keys: " << std::endl;
	//loop over every key and print index.
	for(int key:arr_keys){
		//search for it.
		arr_index=bin_search(arr,0,12,key);
		std::cout << "Key: " << key;	
		//key wasn't found.
		if(arr_index != -1)
			std::cout << " found at index: " << arr_index <<  "." << std::endl;
		else
			std::cout << " not found." << std::endl;
	}
	
	return 0;
}