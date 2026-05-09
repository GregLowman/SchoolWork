#include "ShopQueue.hpp"
#include <iostream>

using namespace std;

ShopQueue::ShopQueue() {
   queueFront = nullptr;
   queueEnd = nullptr;
}

ShopQueue::~ShopQueue() {
   while(!isEmpty())
   {
      dequeue();
   }
}

/**
 * Checks if the shopqueue is empty or not
 * @returns Whether its empty or not
 */
bool ShopQueue::isEmpty() {
   if(queueFront == nullptr)
   {
      return true;
   }
   else
   {
      return false;
   }
}

/**
 * Returns the front order without removing it, or nullptr if the queue is empty.
 * @return A customer order
 */
CustomerOrder* ShopQueue::peek() {
   if (! isEmpty())
   {
      return queueFront;
   }

   cout << "Queue empty, cannot peek!" << endl;
   return nullptr;
}

/**
 * Adds the customers to the queue.
 * @param name The name of the customer to add.
 * @param num_pancakes The number of pancakes to add
 * @param type_of_pancake The type of pancake to add.
 */
void ShopQueue::enqueue(string name, int num_pancakes, int type_of_pancake) {
CustomerOrder *newNode = new CustomerOrder;
newNode->name = name;
newNode->number_of_pancakes = num_pancakes;
newNode->type_of_pancakes = type_of_pancake;
newNode->next = nullptr;

if(isEmpty())
{
   queueFront = queueEnd = newNode;
   return;
}

queueEnd->next = newNode;
queueEnd = queueEnd->next;
}

void ShopQueue::dequeue() {
   if(isEmpty())
   {
         cout << "Queue empty, cannot dequeue!" << endl;
         return;
   }

   CustomerOrder *hold = queueFront;
   queueFront = queueFront->next;

   if(queueFront == nullptr)
   {
      queueEnd = nullptr;
   }
   delete hold;

   return;
}

/**
 * Returns the total number of customers in the queue.
 * @returns The total number of elements
 */
int ShopQueue::queueSize(){
   int index = 0;
   CustomerOrder *current = queueFront;

   while (current!=nullptr)
   {
      current = current->next;
      index++;
   }
   return index;
}

/**
 * Returns the end of the queue.
 */
CustomerOrder* ShopQueue::getQueueEnd(){
   return queueEnd;
}
