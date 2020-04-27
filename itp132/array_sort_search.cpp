#include <iostream>

typedef unsigned int uint32;

int bin_search(int arr[],int l,int h,int x){
	if(l<=h){
	  int m=(l+h)/2;  
	  int cur=arr[m];
		if(x == cur){
			return m;
    }
		else if(cur > x)
    {
			h=m-1;
    }
		else{
			l=m+1;
    }
    return bin_search(arr,l,h,x);
	}
	return -1;

}


void swap(int *a, int *b) { 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
  
int part (int *arr, int low, int high){ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
	int j=0;
    for(j = low; j <= high- 1; j++){ 
        if (arr[j] < pivot){
            swap(&arr[++i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
}
  

void quick_sort(int *arr, int low, int high){ 
    if (low < high){ 
        int pi = part(arr, low, high); 
        quick_sort(arr, low, pi - 1); 
        quick_sort(arr, pi + 1, high); 
    }
} 


int main(){
	int arr[13]={2,3,4,5,6,7,10,8,9,0,1,70,75};
	uint32 i=0;	
	std::cout << "Unsorted Array: [";
	for(uint32 x:arr){
		if(i>=1)
			std::cout << ",";
    i++;
		std::cout << x;
	}
	quick_sort(arr,0,12);
	std::cout << "]" << std::endl;
	std::cout << "Sorted Array: [";
  i=0;
	for(uint32 x:arr){
		if(i>=1)
			std::cout << ",";
    i++;
		std::cout << x;
	}	
	std::cout << "]" << std::endl;
	
	int arr_indicies[5]={3,7,11,70,10};
	int arr_index=0;
	std::cout << "Indexes of keys: " << std::endl;
	for(int key:arr_indicies){
		arr_index=bin_search(arr,0,12,key);
		std::cout << "Key: " << key;	
		if(arr_index != -1)
			std::cout << " found at index: " << arr_index <<  "." << std::endl;
		else
			std::cout << " not found." << std::endl;
	}
	return 0;
}