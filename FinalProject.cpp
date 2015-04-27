#include <iostream>
#include <queue>
#include <vector>
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

void Graph::displayMutual(){
    //bool Mutual;
    //vector<person*> MutualwithReq
    for(int i = 0; i < currentUser->adj.size(); i++)
    {
        for(int j = 0; j < currentUser->adj[i].p->adj.size(); j++)
        {
            for(int k = 0; k  < currentUser->adj.size(); k++)
            {
                if(currentUser->adj[k].p->name != currentUser->adj[i].p->adj[j].p->name && currentUser->adj[i].p->name != currentUser->adj[k].p->name && currentUser->name != currentUser->adj[i].p->adj[j].p->name){
                   //std::cout << currentUser->adj[i].p->adj[j].p->name <<std::endl;
                   for(int l = 0; l < currentUser->adj[i].p->adj[j].p->adj.size(); l++){
                        //std::cout <<"Adj "<<  currentUser->adj[i].p->name << std::endl;
                        //std::cout << "ADjadj "<<currentUser->adj[i].p->adj[l].p->name << std::endl;
                        if(currentUser->adj[i].p->name == currentUser->adj[i].p->adj[j].p->adj[l].p->name ){
                            std::cout << currentUser->adj[i].p->adj[j].p->name << std::endl;
                        }
                   }

                }



            }
        }
    }
}

void Graph::sendReq(std::string name){
    person *Holder;
    bool requestToPerson = true;
    bool requestToUser = true;

    for(int i = 0; i < people.size(); i++){
        if(people[i].name == name){
            Holder = &people[i];
        }
    }
    for(int i = 0; i < currentUser->adj.size(); i++){
        if(currentUser->adj[i].p->name == Holder->name){
            requestToPerson = false; //If my adjacent friends contain the person, I can't send a request to the person
        }
    }
    for(int i = 0; i < Holder->adj.size(); i++){
        if(Holder->adj[i].p->name == currentUser->name){
            requestToUser = false; //If their adjacent friends contain me, they cannot send a friend request to me
        }
    }
    if(!requestToPerson && !requestToUser){
        std::cout << "You are already friends" << std::endl;
    }
    if(requestToPerson && !requestToUser){
        std::cout << "You accepted a friend request" << std::endl;
        addConnection(currentUser->name, name, 1);
    }
    if(!requestToPerson && requestToUser){
        std::cout << "You have already sent a friend request" << std::cout;
    }
    if(requestToPerson && requestToUser){
        std::cout << "Friend Request sent" << std::endl;
        addConnection(currentUser->name, name, 1);
    }

}
void Graph::removeFriend(std::string name){
    person *Holder;
    bool deleteUser = false;
    bool deleteFriend = false;
    for(int i = 0; i < currentUser->adj.size(); i++){
        if(currentUser->adj[i].p->name == name){
            currentUser->adj.erase(currentUser->adj.begin() + i);
            deleteFriend = true; //Friend removed from currentUser's adjacent list
        }
    }
    for(int i = 0; i < people.size(); i++){
        if(people[i].name == name){
            Holder = &people[i];
        }
    }
    for(int i = 0; i < Holder->adj.size(); i++){
        if(Holder->adj[i].p->name == currentUser->name){
            Holder->adj.erase(Holder->adj.begin() + i);
            deleteUser = true; //currentUser removed from Friend's adjacent list
        }
    }
    if(deleteUser && deleteFriend){
        std::cout << name << " removed from list of friends" << std::endl;
    }
    if(!deleteUser && deleteFriend){
        std::cout << "Friend request to " << name << " canceled" << std::endl;
    }
    if(!deleteUser && !deleteFriend){
        std::cout << name << " is not on your list of friends" << std::endl;
    }
    if(deleteUser && !deleteFriend){
        std::cout << name << "'s Friend request was denied" << std::endl;
    }
    findDistricts();
}
void Graph::displayFriendReq(){
    bool isFound = false;
    bool noReqs = true;
    for(int i = 0; i < people.size(); i++){
        for(int k = 0; k < people[i].adj.size(); k++){
            if(people[i].adj[k].p->name == currentUser->name){
                for(int j = 0; j < currentUser->adj.size(); j++){
                    if(currentUser->adj[j].p->name == people[i].name){
                        isFound = true;
                        noReqs = false;
                    }
                }
                if(!isFound)
                {
                    std::cout << people[i].name << std::endl;
                }
                isFound = false;
            }
        }
    }
    if(noReqs)
    {
        std::cout << "No friend requests." << std::endl;
    }

}
void Graph::logout(){
    currentUser = NULL;
    isLogged = false;
    std::cout << "You have been logged out" << std::endl;
}
