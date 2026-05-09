// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"
#include<sstream>


using namespace std;


node* HashTable::createNode(string charName, node* nextNode)
{
	// TODO
	node* character = new node;
	character->characterName = charName;
	character->pq = PriorityQ(50);
	character->next = nextNode;	
	return character;
}


HashTable::HashTable(int bsize)
{
	// TODO
	tableSize = bsize;
	table = new node*[bsize];
	numCollision = 0;

	for(int i = 0; i < bsize; i++)
	{
		table[i] = nullptr;
	}
}


void HashTable::printTable()
{

	// TODO

	node* current = nullptr;

	for(int i = 0; i < tableSize; i++)
	{
		if(table[i])
		{
			cout << "table[" << i << "]: ";
			cout << table[i]->characterName;
			current = table[i]->next;			
			while(current)
			{
				cout << ", " << current->characterName;
				current = current->next;
			}
		}
		else 
		{
			cout << "table[" << i << "]: ";  
		}
		cout << endl;

	}

}


//function to calculate hash function
unsigned int HashTable::hashFunction(string charName)
{
	// TODO
	int total = 0;
	for(char i : charName)
	{
		total += i;
	}

	return(total % tableSize);
}



node* HashTable::searchCharacter(string charName)
{
	int index = hashFunction(charName);
	node* current = table[index];
	while(current)
	{
		if(current->characterName == charName)
		{
			return current;
		}
		current = current->next;
	}
	return nullptr;
}



//function to insert
void HashTable::insertItem(ItemInfo newItem)
{
	// TODO

	string name = newItem.characterName;
	node* charCheck = searchCharacter(name);
	int index = hashFunction(name);

	if(charCheck != nullptr)
	{
		charCheck->pq.insertElement(newItem);
	}
	else if(charCheck == nullptr && table[index] != nullptr)
	{
		node* toAdd = createNode(name, table[index]);
		table[index] = toAdd;
		toAdd->pq.insertElement(newItem);
		numCollision++;
	}
	else if (charCheck == nullptr && table[index] == nullptr)
	{
		node* toAdd = createNode(name, nullptr);
		table[index] = toAdd;
		toAdd->pq.insertElement(newItem);
	}
}


void HashTable:: buildBulk(string fname)
{
    // TODO

	ifstream instream;
	instream.open(fname);

	string line;

	if(instream.is_open())
	{
		while(getline(instream, line))
		{
			string characterName, itemName, itemDamage, comments;

			stringstream ss(line);

			getline(ss, characterName, ';');
			getline(ss, itemName, ';');
			getline(ss, itemDamage, ';');
			getline(ss, comments, ';');

			int damage = stoi(itemDamage);

			ItemInfo item;
			item.characterName = characterName;
			item.itemName = itemName;
			item.damage = damage;
			item.comment = comments;

			insertItem(item);
		}
		instream.close();
	}

	else
	{
		cout << "File not found" << endl;
	}
}

void HashTable::deleteEntry(string charName) {
	// TODO
	node* toDelete = searchCharacter(charName);
	int index = hashFunction(charName);

	if(toDelete == nullptr)
	{
		return;
	}
	else if(table[index] != nullptr && toDelete != nullptr)
	{
		node* hold = nullptr;
		node* current = table[index];

		if(table[index] == toDelete)
		{
			table[index] = toDelete->next;
			delete toDelete;
			return;
		}
		
		while(current->next)
		{
			if(current->next == toDelete)
			{
				current->next = toDelete->next;
				delete toDelete;
				return;
			}
			current = current->next;
		}
	}
}
