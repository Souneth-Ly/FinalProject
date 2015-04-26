#include <iostream>
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
