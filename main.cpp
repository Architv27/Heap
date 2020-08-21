#include"Heap.h"
using namespace std;

void simpleTest()
{
	// Int Heap Tests
	Heap<int> pq1(4);

	pq1.insert(3);
	pq1.insert(1);
	pq1.insert(42);

	cout << "pq1 root = " << pq1.peek() << endl; //42
	int urgent = pq1.remove();
	cout << "pq1 root = " << pq1.peek() << endl; //3
	cout << "pq1 size = " << pq1.size() << endl; //2

	Heap<int> pq2(pq1);
	pq2.insert(13);
	Heap<int> pq3 = pq1.merge(pq2); // should contain duplicates
	cout << "pq3 size = " << pq3.size() << endl; //5
	cout << "pq3 root = " << pq3.peek() << endl; //13
}
int main()
{
	simpleTest();
	return 0;
}