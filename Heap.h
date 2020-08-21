#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>

using std::runtime_error;
using std::vector;
using std::endl;
using std::cout;

template <class H>
class Heap {

private:

	H* arr;
	int heapSize;//number of elements in the array
	int arrSize;//size of the array

	//insertion and removal helper methods
	void bubbleUp(const int hSize);
	void swap(H& a, H& b);
	void bubbleDown(const int par);

public:

	//Non-default and copy constructors, destructor
	Heap<H>(const int hSize);
	Heap<H>(const Heap<H>& h);
	~Heap();

	//overloaded assignment operator doing deep copy
	Heap<H>& operator=(const Heap<H>& h);

	//MUTATORS
	void insert(const H val);
	H remove();

	H peek() const;
	
	//merge
	Heap<H> merge(const Heap& h) const;
	
	//accessor
	int size() const;

};

//PARAM: templated vector v and number of smallest integers m wanted in resultant vector.
//POST: returns a vector with the m smallest values from parameter vector v
template <class H>
vector<H> smallestm(vector<H> v, const int m) {
	// if m is greater than or qual to size of vector then inserting the vector in the temporary heap of size v.size() 
	//
	if (m >= v.size()) {
		
		Heap<H> tempHp(v.size());
		for (int i = 0; i < v.size(); i++) 
			tempHp.insert(v[i]);

		vector<H> result;
		for (int i = tempHp.size() - 1; i >= 0; i--) {

			//insert heap sorted values from heap to result vector
			result.insert(result.begin(), tempHp.remove());
		}
		return result;
	}

	else {

		Heap<H> tempHp(v.size());
		for (int i = 0; i < v.size(); i++) //heapifying by inserting
			tempHp.insert(v[i]);
		
		vector<H> result;
		
		for (int i = tempHp.size() - 1; i >= 0; i--)  //inserting sorted values from heap to result vector
			result.insert(result.begin(), tempHp.remove());
		result.erase(result.begin() + m, result.end()); //removing the extra elements from the result vector 
		return result;
	}

}

// CONSTRUCTOR
template <class H>
Heap<H>::Heap<H>(const int hSize) {
	arr = new H[hSize];
	heapSize = 0;
	arrSize = hSize;
}

// COPY CONSTRUCTOR
template <class H>
Heap<H>::Heap<H>(const Heap& h) {
	
	this->heapSize = h.size();
	this->arrSize = h.arrSize;
	
	if (this->size() > 0 && arrSize > 0) {

		this->arr = new H[this->arrSize];
		
		for (int i = 0; i < this->size(); i++)
			this->arr[i] = h.arr[i];
		
	}
}

// destructor: deallocates memory
template <class H>
Heap<H>::~Heap() {

	if (this->size() > 0 && arrSize > 0) {

		delete[] this->arr;
		this->heapSize = 0;
		this->arrSize = 0;
	}
}

//ASSIGNMENT OPERATOR
template <class H>
Heap<H>& Heap<H>::operator=(const Heap<H>& h) {

	if (this == &h)
		return *this;

	this->~Heap<H>();
	this->heapSize = h.size();
	this->arrSize = h.arrSize;
	if (this->size() > 0 && arrSize > 0) {

		this->arr = new H[this->arrSize];
		int i = 0;
		while(i < this->size()) {

			this->arr[i] = h.arr[i];
			i++;
		}
	}
	return *this;
}

//PARAM: two templated parameters passed by refernce 
//POST: swaps the two variables
template <class H>
void Heap<H>::swap(H& a, H& b) {

	H temp = a;
	a = b;
	b = temp;
}


template <class H>
void Heap<H>::bubbleUp(const int hSize) {

	int par = (hSize - 1) / 2;
	if (hSize > 0 && arr[hSize] > arr[par]) {

		this->swap(arr[hSize], arr[par]);
		bubbleUp(par);
	}
}
//PARAM: index of the parent element.
//POST: swaps parent element with greater valued child until correct location is found.
template <class H>
void Heap<H>::bubbleDown(const int par) {

	int ch1 = 2 * par + 1;
	int ch2 = 2 * par + 2;
	if (par >= 0 && ch1 < heapSize && (arr[ch1] >= arr[par] || arr[ch2] >= arr[par])) // parent should be greater than 0 and index of child 1 should less
	//than heapsize and array child 1 should be greater than or equal to element at par index or child 2 should be greater or equal to element at par index. {

		if (arr[ch1] >= arr[ch2]) {

			this->swap(arr[par], arr[ch1]);
			bubbleDown(ch1);
		}
		else {

			this->swap(arr[par], arr[ch2]);
			bubbleDown(ch2);
		}
	}
}

//PRE: array should have some space.
//PARAM: template variable to be inserted in heap
//POST: arranges the array again to insert the parameter. 

template <class H>
void Heap<H>::insert(const H val) {

	if (heapSize >= arrSize || arrSize == 0)
		throw runtime_error("Runtime Error! No Space in Array to Insert Value");

	if (heapSize >= 0 && heapSize < arrSize) {

		arr[this->size()] = val;
		bubbleUp(this->size());
		heapSize++;
	}
}

//PRE: Array should not be empty
//POST: removes and returns the root and arranges the array again to maintain properties of heap.
template <class H>
H Heap<H>::remove() {

	if (heapSize <= 0 || arrSize <= 0)
		throw runtime_error("Runtime Error! No Element inside the Heap to Remove");
	if(heapSize <= arrSize) {

		H root = this->arr[0];
		arr[0] = arr[heapSize - 1];
		heapSize--;
		bubbleDown(0);
		return root;
	}
}

//PRE: Array should not be empty
//POST: returns the root without making any change.
template <class H>
H Heap<H>::peek() const {

	if (heapSize == 0 || arrSize == 0)
		throw runtime_error("Runtime Error! No Element Inside the Heap to Peek");

	H root = this->arr[0];
	return root;
}

template <class H>
Heap<H> Heap<H>::merge(const Heap<H>& h) const {

	Heap<H> resultHeap(this->size() + h.size());
	int i = 0;
	while (i < this->size()) {
		
		resultHeap.insert(this->arr[i]);
		i++;
	}
	int j = 0;
	while (j < h.size()) {
		resultHeap.insert(h.arr[j]);
		j++;
	}
	return resultHeap;
}

//POST: returns the number of elements in the heap
template <class H>
int Heap<H>::size() const {
	
	return this->heapSize;
}