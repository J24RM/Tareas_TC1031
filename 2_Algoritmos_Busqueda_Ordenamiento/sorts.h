#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <string>


#ifndef SORTS_H_
#define SORTS_H_

using namespace std;

template <class T> 
class Sorts
{
private:
	void swap(std::vector<T>&, int, int);
	void mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high);
	void mergeArray(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high);
	void copyArray(std::vector<T> &A, std::vector<T> &B, int low, int high);

public:
	std::vector<T>& ordenaSeleccion(std::vector<T>& v);
	std::vector<T>& ordenaBurbuja(std::vector<T>& v);
	std::vector<T>& ordenaMerge(std::vector<T>& v);
	long busqSecuencial(const std::vector<T>&, int val);
	long busqBinaria(const std::vector<T>&, int val);



	
};

template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
	int tem = v[i];
	v[i] = v[j];
	v[j] = tem;
}



template <class T>
std::vector<T>&  Sorts<T>::ordenaSeleccion(std::vector<T>& v){
    for(int i = 0; i < v.size() - 1; i++){
    	int pos = i;
    	T min = v[i];
    	for (int j = i + 1; j < v.size();j++){
    		if (min > v[j]){
    			pos = j;
    			min = v[j];
    		}
    	}
    	if ( i != pos){
    		swap(v,i,pos);
    	}
    }
    return v;
}

template <class T>
std::vector<T>& Sorts<T>::ordenaBurbuja(std::vector<T>& v) {

    for(int i = v.size() - 1; i > 0 ; i--){
    	for (int j = 0; j < i ; j++){
    		if (v[j] > v[j+1]){
    			swap(v,j,j+1);
    		}
    	}
    }
    return v;
   
}

template <class T>
std::vector<T>& Sorts<T>::ordenaMerge(std::vector<T>& v) {
	std::vector<T> tmp(v.size());

	mergeSplit(v, tmp, 0 ,v.size() - 1);
    return v;
}


template <class T>
void Sorts<T>::mergeSplit(std::vector<T>& A, std::vector<T> &B, int low, int high) {

	int mid;

	if (low == high){
		return; 
	}

	mid = (high + low) / 2;

	mergeSplit(A, B, low, mid);
	mergeSplit(A, B, mid + 1, high);
	mergeArray(A, B, low, mid, high);
	copyArray(A, B, low, high);

}

template <class T>
void Sorts<T>::mergeArray(std::vector<T>& A, std::vector<T> &B, int low, int mid, int high) {
	int i,j,k;

	i = low;

	j = mid + 1;

	k = low;

	while(i <= mid && j <= high){
		if (A[i] < A[j]){
			B[k] = A[i];
			i++;
		}
		else{
			B[k] = A[j];
			j++;
		}
		k++;
	}
	if (i > mid){
		for (; j <= high; j++){
			B[k++] = A[j];
		}
	}

	else{
		for (; i <= high; i++){
			B[k++] = A[i];
		}
	}
	
}


template <class T>
void Sorts<T>::copyArray(std::vector<T>& A, std::vector<T> &B, int low, int high) {
	int i,j;

	i = low;

	j = high;

	for(; i <= high; i++){
		A[i] = B[i];
	}

}

template <class T>
long Sorts<T>::busqSecuencial(const std::vector<T> &source, int val) {

    for (int i = 0; i < source.size(); i++){
    	if(source[i] == val){
    		return i;
    	}
	}

    return -1;
}

template <class T>
long Sorts<T>::busqBinaria(const std::vector<T> &source, int val) {
	int low = 0;

	int high = source.size() ;

	
	while(low <= high){
		int mid = (high + low) / 2;
		if (source[mid] == val){
			return mid;
		}
		if(source[mid] > val){
			high = mid - 1;
		} 
		if(source[mid] < val){
			low = mid + 1;
		}

	}

   return -1;
}

#endif /* SORTS_H_ */