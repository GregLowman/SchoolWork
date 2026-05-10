#include <iostream>
#include <cstdlib>
#include <iostream>
#include "Register.hpp"


using namespace std;

Register::Register(){
   top = 0;
}

/*
 * Returns true if the register is full.
 */
bool Register::isFull(){
   if(top == SIZE)
   {
      return true;
   }
   return false;
}

/*
 * Pushes a sale price onto the stack.
 * @param money: the type of pancake's price times the quantity
 */
void Register::push( int money ){
   if(!isFull())
   {
      a[top] = money;
      top++;
      return;
   }

   cout << "Stack overflow: " << endl;
   return;
}


/*
 * Returns true if the register is empty.
 */
bool Register::isEmpty(){
   if(top == 0)
   {
      return true;
   }
   return false;
}

/*
 * Prints all amounts in the stack from top to bottom.
 */
void Register::disp(){
   cout << "top = " << top << endl;

   cout << "Print stack from top to bottom:" << endl;

   for(int i = top-1; i >= 0; i--)
   {
      cout << a[i] << endl;
   }
}

int Register::pop(){
   if(isEmpty())
   {
      cout << "Stack empty, cannot pop an item!" << endl;
      return -1;
   }

   top --;
   return a[top];
}
