#include "PancakeHouse.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;
int const PancakeHouse::pancake_types[] = {1, 2, 5, 3, 7};



/**
 * Constructor for the Pancake House
 */
PancakeHouse::PancakeHouse() {
    profit = 0;
    pancakesCooked = 0;
    this->cashRegister = new Register;
    this->shopQueue = new ShopQueue;
    }

/**
 * Destructor for the pancake house. Removes the register and shopQueue.
 */
PancakeHouse::~PancakeHouse(){
    while(!shopQueue->isEmpty())
    {
        shopQueue->dequeue();
    }
    delete shopQueue;
    delete cashRegister;
}

/**
 * Gets the stack.
 * @returns The cash register
 */
Register* PancakeHouse::getStack(){
    return cashRegister;
}

/**
 * Gets the queue.
 * @returns The shop queue
 */
ShopQueue* PancakeHouse::getQueue() {
    return shopQueue;
}

/**
 * Gets the profit class variable
 * @returns The profit
 */
int PancakeHouse::getProfit(){
    return profit;
}

/**
 * Adds an order to the queue. Orders with a type outside 1-5 are silently rejected.
 * @param name The name of the person to be added
 * @param number_of_pancakes The total number of pancakes to be ordered
 * @param type_of_pancakes The type of pancake to be cooked (1-5)
 */
void PancakeHouse::addOrder(string name, int number_of_pancakes, int type_of_pancakes) {
    for(int index = 1; index < 6; index++)
    {
        if(type_of_pancakes == index)
        {
            shopQueue->enqueue(name, number_of_pancakes, type_of_pancakes);
        }
    }

}

/**
 * Cooks the next order by removing it from the queue and pushing its price onto the register.
 */
void PancakeHouse::cookPancakes() {
    CustomerOrder *processOrder = nullptr;

    if(!shopQueue->isEmpty())
    {
        processOrder = shopQueue->peek();
        int priceIndex = (processOrder->type_of_pancakes) - 1;
        int pancakePrice = pancake_types[priceIndex];

        int size = processOrder->number_of_pancakes;

        pancakesCooked += size;
        int price = size * pancakePrice;

        if(!cashRegister->isFull())
        {
            cashRegister->push(price);
        }

        shopQueue->dequeue();
    }

    else
    {
        cout << "Queue empty, cannot peek!" << endl;
    }

    return;
}

/*
 * Cancels the next order in the queue.
 */
void PancakeHouse::strikeOrder(){
    if(!shopQueue->isEmpty())
    {
        shopQueue->dequeue();
    }
    return;
}

/*
 * Removes the most recent sale from the register and prints the refund amount.
 */
void PancakeHouse::refundOrder(){
    int refundAmount = cashRegister->pop();

    if(refundAmount == -1)
    {
        cout << "No money in the cash register!" << endl;
        return;
    }
    cout << "Money refunded = " << refundAmount << endl;
    return;
}

/**
 * Closes the shop for the day by draining the queue and register.
 */
void PancakeHouse::closeShop(){
    while(!shopQueue->isEmpty())
    {
        shopQueue->dequeue();
    }
    while(!cashRegister->isEmpty())
    {
        cashRegister->pop();
    }
    return;
}

/**
 * Pops all remaining register entries and accumulates them into the profit total.
 */
void PancakeHouse::updateTotalProfit(){
    while(!cashRegister->isEmpty())
    {
        profit += cashRegister->pop();
    }

    return;
}

/**
 * Prints all pending orders without removing them from the queue.
 */
void PancakeHouse::printOrders(){
    CustomerOrder *customer = shopQueue->peek();
    while(customer != nullptr)
    {
        cout << "Customer name: " << customer->name << endl;
        cout << "Number of pancakes ordered: " << customer->number_of_pancakes << endl;
        cout << "Type of pancakes: " << customer->type_of_pancakes << endl;
        customer = customer->next;
    }
    return;

}
