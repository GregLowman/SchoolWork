#include "LinkedInNetwork.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void LinkedInNetwork::addProfessional(string name){
    bool found = false;
    int size = professionals.size();

    for (int i = 0; i < size; i++)
    {
        if(professionals[i])
        {
            if(professionals[i]->name == name)
            {
                found = true;
            }
        }
    }


    if(!found)
    {
        Professional *newProffesional = new Professional;
        newProffesional->name = name;

        professionals.push_back(newProffesional);
    }
    else
    {
        cout << name << " found." << endl;
    }
    return;
}


void LinkedInNetwork::addConnection(string v1, string v2){
    int size = professionals.size();
    Professional *personOne = nullptr;
    Professional *personTwo = nullptr;

    for (int i = 0; i < size; i++)
    {
        if(professionals[i]->name == v1)
        {
            personOne = professionals[i];
        }

        else if(professionals[i]->name == v2)
        {
            personTwo = professionals[i];
        }
    }

    if(personOne && personTwo)
    {
        neighbor neighOne;
        neighbor neighTwo;

        neighOne.v = personOne;
        neighTwo.v = personTwo;

        personOne->neighbors.push_back(neighTwo);
        personTwo->neighbors.push_back(neighOne);
    }

}

void LinkedInNetwork::displayConnections(){

    for(auto prof : professionals)
    {
        cout << prof->name << " --> ";

        for(auto neigh : prof->neighbors)
        {
            cout << neigh.v->name << " ";
        }
        cout << endl;
    }
}

void LinkedInNetwork::breadthFirstTraverse(string sourceProfessional){
    Professional *root = nullptr;

    for (auto prof : professionals)
    {
        if(prof->name == sourceProfessional)
        {
            root = prof;
        }
    }

    cout << "Starting Professional (root): " << sourceProfessional << "-> ";

    vector<Professional*> queue;
    root->visited = true;
    root->connectionOrder = 0;
    queue.push_back(root);

    while(!queue.empty())
    {
        Professional *current = queue.front();
        queue.erase(queue.begin());

        for(auto neigh : current->neighbors)
        {
            if(!neigh.v->visited)
            {
                neigh.v->visited = true;
                neigh.v->connectionOrder = current->connectionOrder + 1;
                cout << neigh.v->name << "(" << neigh.v->connectionOrder << ") " ;
                queue.push_back(neigh.v);
            }
        }
    }


}

void bfs_helper(string source, vector<Professional*> &professionals) {

Professional *root = nullptr;

    for (auto prof : professionals)
    {
        if(prof->name == source)
        {
            root = prof;
        }
    }

    if(root == nullptr)
    {
        return;
    }
    vector<Professional*> queue;
    root->visited = true;
    root->connectionOrder = 0;
    queue.push_back(root);

    while(!queue.empty())
    {
        Professional *current = queue.front();
        queue.erase(queue.begin());

        for(auto neigh : current->neighbors)
        {
            if(!neigh.v->visited)
            {
                neigh.v->visited = true;
                neigh.v->connectionOrder = current->connectionOrder + 1;
                queue.push_back(neigh.v);
            }
        }
    }

}

vector<string> LinkedInNetwork::suggestProfessionalsWithinKthOrder(string professionalName, int k){
    vector<string> professionalsWithinK;

    bfs_helper(professionalName, professionals);


    for(auto prof : professionals)
    {
        if(prof->visited && prof->connectionOrder <= k && prof->connectionOrder != 0)
        {
            professionalsWithinK.push_back(prof->name);
        }
    }
    return professionalsWithinK;
}
