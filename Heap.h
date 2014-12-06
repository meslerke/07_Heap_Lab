#include "Queue.h"
#include <utility>

//This should be the initial arrSize
#define START_SIZE 10

/*
 * This is a priority queue, which means that items are removed in order
 * of decreasing priority.
 *
 * 
 */
template<class Pri, class T>
class Heap : public Queue<std::pair<Pri, T> > {
public:
  Heap();
  ~Heap();

  //Add a new item
  virtual void add(std::pair<Pri,T> toAdd);

  //Remove the item with lowest priority, and return it
  //If the queue is empty, throw a string exception
  virtual std::pair<Pri,T> remove();

  //Return the number of items currently in the queue
  virtual unsigned long getNumItems();

private:
  int arrSize;
  int numItems;
  std::pair<Pri, T>* backingArray;

  //Grow the backingArray by making a new array of twice the size,
  // and copying over the data
  void grow();

  //Check the item at index, and make sure it is in the right place.
  // If not, swap it up the "tree" of the heap until you find the right
  // place
  void bubbleUp(unsigned long index);

  //Check the item at index, and make sure it is in the right place.
  // If not, swap it down the "tree" of the heap until you find the right
  // place
  void trickleDown(unsigned long index);  
};








#include <string>

template<class Pri, class T>
Heap<Pri, T>::Heap(){
	arrSize = START_SIZE;
	numItems = 0;
	backingArray = new std::pair<Pri, T>[START_SIZE];
}

template<class Pri, class T>
Heap<Pri, T>::~Heap(){
	delete[] backingArray;
}

template<class Pri, class T>
void Heap<Pri, T>::grow(){
	std::pair<Pri, T>* oldBackingArray = backingArray;
	arrSize *= 2;
	backingArray = new std::pair<Pri, T>[arrSize];
	for (int i = 0; i < arrSize / 2; i++) {
		backingArray[i] = oldBackingArray[i];
	}

	delete[] oldBackingArray;

}

template<class Pri, class T>
void Heap<Pri, T>::add(std::pair<Pri, T> toAdd){
	numItems++;
	if (numItems >= arrSize) {
		grow();
	}
	backingArray[numItems - 1] = toAdd;
	bubbleUp(numItems - 1);
}

template<class Pri, class T>
void Heap<Pri, T>::bubbleUp(unsigned long index){
	if (index == 0) {
		return;
	}
	if (backingArray[index] >= backingArray[(index - 1) / 2]) { //if the element at this index is >= than its parent
		return;
	}
	swap(backingArray[index], backingArray[(index - 1) / 2]);
		return bubbleUp((index - 1) / 2);
}

template<class Pri, class T>
void Heap<Pri, T>::trickleDown(unsigned long index){
	//My dad helped me with the implementation of this method
	bool done;
	do{
		done = false;
		int leftChild = (2 * index) + 1;
		int rightChild = (2 * index) + 2;

		if (leftChild < numItems && backingArray[index].first > backingArray[leftChild].first){
			if (backingArray[leftChild].first < backingArray[rightChild].first){	//swap with smaller child
				swap(backingArray[index], backingArray[leftChild]);
				index = leftChild;
				done = true;
			} else{
				swap(backingArray[index], backingArray[rightChild]);
				index = rightChild;
				done = true;
			}
		} else{ //index is not larger than leftChild so now check if it's larger than rightChild
			if (rightChild < numItems && backingArray[index].first > backingArray[rightChild].first){
				swap(backingArray[index], backingArray[leftChild]);
				index = leftChild;
				done = true;
			} 
			else{ //index is where it is supposed to be
				done = true;
			}
		}
	} while (done == false);
}

template<class Pri, class T>
std::pair<Pri, T> Heap<Pri, T>::remove(){
	if(numItems < 1){
		std::cout << "ERROR: Queue is empty and cannot remove" << std::endl;
	}
	std::pair<Pri, T> ret = backingArray[0];
	backingArray[0] = backingArray[numItems - 1];
	numItems--;
	trickleDown(0);
	return ret;
}

template<class Pri, class T>
unsigned long Heap<Pri, T>::getNumItems(){
	return numItems;
}

