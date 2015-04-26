#include <iostream>
#include <queue>
#include "FinalProject.h"

Graph::Graph()
{
}

Graph::~Graph()
{

}

void Graph::addPerson(std::string name)
{
    //Copied from Assignment 8. Pretty much the same.
    bool found = false;
    for(int i = 0; i < people.size(); i++){
        if(people[i].name == name){
            found = true;
            std::cout<<people[i].name<<" found."<<std::endl;
        }
    }
    if(found == false){
        person newPerson;
        newPerson.name = name;
        people.push_back(newPerson);

    }
}

void Graph::addConnection(std::string name1, std::string name2, int weight)
{
    //Needs checked over.
    //Might need to be changed because of friend request function
    //Copied over from Assignment 8, but this one only adds edge one way instead of both ways.
    bool alreadyAdded = false;
    for(int i = 0; i < people.size(); i++)
        if(name1 == people[i].name)
            for(int j = 0; j < people[i].adj.size(); j++)
                if(name2 == people[i].adj[j].p->name)
                    alreadyAdded = true;
    if(!alreadyAdded){
        for(int i = 0; i < people.size(); i++){
            if(people[i].name == name1){
                for(int j = 0; j < people.size(); j++){
                    if(people[j].name == name2 && i != j && weight > 0){
                        connection newConnection;
                        newConnection.p = &people[j];
                        newConnection.isfriend = true;
                        people[i].adj.push_back(newConnection);
                    }
                }
            }
        }
    }
}

void Graph::login(std::string name)
{
    bool found = false;
    if(!isLogged)
    {
        for(int i = 0; i < people.size(); i++)
        {
            if(name == people[i].name)
            {
                isLogged = true;
                found = true;
                currentUser = &people[i];
                std::cout << "Welcome " << currentUser->name << "." << std::endl;
            }
        }
        if(!found)
            std::cout << "User not found." << std::endl;
    }
    else
        std::cout << "Please log out before logging in to another user." << std::endl;


}

void Graph::displayFriends()
{
    for(int i = 0; i < currentUser->adj.size(); i++)
    {
        for(int j = 0; j < currentUser->adj[i].p->adj.size(); j++)
        {
            if(currentUser->adj[i].p->adj[j].p->name == currentUser->name) //Checks to see if the connection has currentUser as one of his friends
                std::cout << currentUser->adj[i].p->name << std::endl;
        }
    }
}

void Graph::BFTraversal(std::string name) //Breadth First Traversal used for findDistricts
{
    std::queue<person*> bfq;
    person p;
    int i = 0;
    for(i=0; i<people.size();i++) {
        if (name==people[i].name) {
            p = people[i];
            break;
        }
    }
    people[i].visited = true;
    bfq.push(&people[i]);

    while (!bfq.empty()) {
        p = *bfq.front();
        bfq.pop();
        for(i=0;i<p.adj.size();i++) {
                for(int j = 0; j < p.adj[i].p->adj.size(); j++)
                if (p.adj[i].p->visited==false && p.adj[i].p->adj[j].p->name == p.name) {
                    p.adj[i].p->visited = true;
                    bfq.push(p.adj[i].p);
                }

        }
    }
}

void Graph::findDistricts()
{
    for(int i = 0; i < people.size(); i++)
    {
        people[i].visited = false;
    }
    int n = 0;
    for(int i = 0; i < people.size(); i++)
    {
        if(people[i].visited == false)
        {
            BFTraversal(people[i].name);
            n++;
            for(int j = 0; j < people.size(); j++)
            {
                if(people[j].visited == true && people[j].groupID == -1)
                    people[j].groupID = n;
            }
        }
    }
}

void Graph::displayEveryone()
{
    for(int i = 0; i < people.size(); i++)
    {
        std::cout << people[i].groupID << ": " << people[i].name << std::endl;
    }
}
