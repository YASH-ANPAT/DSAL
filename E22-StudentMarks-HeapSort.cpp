#include <iostream>
using namespace std;

class studentHeap {
	private:
		int* maxHeap;
		int* minHeap;
		int capacity;
		
		void upadjustMax(int heap[], int i){
			int temp;
			while(i>1 && heap[i] > heap[i/2]){
				temp = heap[i/2];
				heap[i/2] = heap[i];
				heap[i] = temp;
				i = i/2;
			}
		}
		
		void upadjustMin(int heap[], int i){
			int temp;
			while(i>1 && heap[i] < heap[i/2]){
				temp = heap[i/2];
				heap[i/2] = heap[i];
				heap[i] = temp;
				i = i/2;
			}
		}
		
		void insertMax(int heap[], int x){
			int n;
			n = heap[0];
			heap[n+1] = x;
			heap[0] = n+1;
			upadjustMax(heap, n+1);
		}
		
		void insertMin(int heap[], int x){
			int n;
			n = heap[0];
			heap[n+1] = x;
			heap[0] = n+1;
			upadjustMin(heap, n+1);
		}
		
	public:
		
		studentHeap(int cap){
			capacity = cap;
			maxHeap = new int[capacity+1];
			minHeap = new int[capacity+1];
			maxHeap[0]=0;
			minHeap[0]=0;
		}
		
		void addMark(int mark){
			if(maxHeap[0]>=capacity){
				cout<<"Heap is full!!";
			}
			insertMax(maxHeap, mark);
			insertMin(minHeap, mark);
		}
		
		int getMax(){
			return maxHeap[1];
		}
		
		int getMin(){
			return minHeap[1];
		}
};

int main(){
	int studentCount;
	cout<<"Enter total number of students in class: ";
	cin>>studentCount;
	
	studentHeap marks(studentCount);
	
	cout<<"Enter marks of each student: \n";
	for(int i=0; i<studentCount; i++){
		int mark;
		cin>>mark;
		marks.addMark(mark);
	}
	
	cout<<"\n Highest marks: "<<marks.getMax()<<endl;
	cout<<"\n Lowest marks: "<<marks.getMin()<<endl;
	
	return 0;
}