#include "PriorityQueue.hpp"
#include <limits.h>
using namespace std;

void swap(ItemInfo *a, ItemInfo *b)
{
	// TODO
	ItemInfo temp = *a;
	*a = *b;
	*b = temp;
	return;
}

/*
Constructor for our MinHeap implementation
*/
PriorityQ::PriorityQ()
{
	// Constructor given no arguments
	currentSize = 0;
	heapArr = nullptr;
	capacity = 0;
}

PriorityQ::PriorityQ(int size)
{
	// Constructor with parameters given 
	currentSize = 0;
	capacity = size;
	heapArr = new ItemInfo[size];
}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
	// Returns index of the parent in the array 
	return ((index - 1) / 2);
}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index)
{
	// Returns index of the left child in the array 
	return ((index * 2) + 1);
}

/*
Returns the right child of a node.
*/
int PriorityQ::rightChild(int index)
{
	// Returns index of the right child in the array 
	return ((index * 2) + 2);

}

ItemInfo* PriorityQ::peek()
{
	// TODO
	if(currentSize == 0)
	{
		return nullptr;
	}
	else
	{
		return(&heapArr[0]);
	}
}

void PriorityQ::heapify(int i)
{	
	int maxIndex = i;
	int maxDamage = heapArr[i].damage;
	
	//has two children
	if(leftChild(i) < currentSize && rightChild(i) < currentSize)
	{
		
			
		//Define the max damage node

		if(heapArr[leftChild(i)].damage > maxDamage)
		{
			maxIndex = leftChild(i);
			maxDamage = heapArr[leftChild(i)].damage;
		}
		if(heapArr[rightChild(i)].damage > maxDamage)
		{
			maxIndex = rightChild(i);
			maxDamage = heapArr[rightChild(i)].damage;
		}



		if(maxIndex == rightChild(i))
		{
			swap(&heapArr[i], &heapArr[rightChild(i)]);
			heapify(rightChild(i));
		}
		else if(maxIndex == leftChild(i))
		{
			swap(&heapArr[i], &heapArr[leftChild(i)]);
			heapify(leftChild(i));
		}
		else
		{
			return;
		}
	}
	//has one child
	else if (leftChild(i) < currentSize)
	{
		if(heapArr[leftChild(i)].damage > maxDamage)
			{
				swap(&heapArr[i], &heapArr[leftChild(i)]);
				heapify(leftChild(i));
			}
		else
		{
			return;
		}

	}
	//has no children
	else
	{
		return;
	}
}

void PriorityQ::insertElement(ItemInfo item)
{
	// TODO
	int index = currentSize;
	if (currentSize < capacity)
	{
		heapArr[index] = item;
		while(index > 0)
		{
			if(heapArr[parent(index)].damage < heapArr[index].damage)
			{
				swap(&heapArr[parent(index)], &heapArr[index]);
				index = parent(index);
			}
			else
			{
				currentSize++;
				return;
			}
		}
		currentSize++;
		return;
	}
	else
	{
		return;
	}
}

/*
Prints the elements in the heap
*/
void PriorityQ::print()
{
	// TODO
	for(int i = 0; i < currentSize; i++)
	{
		cout << "\t" << "Item: " << heapArr[i].itemName << endl;
		cout << "\t" << "Damage: " << heapArr[i].damage << endl;
		cout << "\t" << "Comment: " << heapArr[i].comment << endl;
		cout << "\t" << "=================" << endl;
	}
}

// Optional function, use if you need to
void PriorityQ::popHelper(int i) {
	// TODO
}

// Method to remove minimum element (or root) from min heap
void PriorityQ::pop()
{
	// TODO
	if(currentSize > 0)
	{
		heapArr[0] = heapArr[currentSize - 1];
		currentSize--;
		heapify(0);
	}

}
