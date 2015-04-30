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

//Works the same as AddVertex from Assignment 8
//Is used at the beginning to add people in, does not need user input.
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

//Is used for adding edges between people.
//Is used when initiating graph
//Is also used when sending a request. In order to work, friend requested needs to be within the graph
//name1 is the currently logged in user, name2 is the user that currentUser will connect to.
void Graph::addConnection(std::string name1, std::string name2, int weight)
{
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
                    if(people[j].name == name2 && i != j && weight > 0){ //Weight is either 1, -1 or 0. If weight is 0, that's self. 1 is a friend request to the person. -1 is no friend request.
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

//Checks for log-in name and if name is within the graph then that user will be marked as the logged-in user.
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

//Displays all friends connected to currentUser while ignoring friend requests.
void Graph::displayFriends()
{
    if(isLogged)
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
    else
        std::cout << "Not logged in." << std::endl;
}

//BFTraversal code taken from moodle.
//A change was made to check the difference between friend requests and friends
void Graph::BFTraversal(std::string name)
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

//Same as old findDistrict code.
//Finds the groups of connections that aren't connected to the other groups and labels them with an ID
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

//Goes through graph and prints out ID and name of each person in graph
void Graph::displayEveryone()
{
    for(int i = 0; i < people.size(); i++)
        std::cout << people[i].groupID << ": " << people[i].name << std::endl;
}

//Messy code, needs some form of cleaning up
//Displays people who are friends of currentUser's friends, that are not currentUser's friends.
void Graph::displayMutual(){
    //Creates a vector "names" in order to store all the mutual friends
    std::vector<std::string> names;
    bool nameFound = false;
    if(isLogged){
        for(int i = 0; i < currentUser->adj.size(); i++) //Checks each of current user's friends
        {
            for(int j = 0; j < currentUser->adj[i].p->adj.size(); j++) //Checks each of current user's friend's friends. These are potential mutual friends
            {
                for(int k = 0; k  < currentUser->adj.size(); k++) //This is used to check each of currentUser's friends and see if it matches with the potential mutual friend
                {
                    //if statement checks if the potential mutual friend is either the currentUser, the currentUser's friends, and that these connections are not friend requests
                    if(currentUser->adj[k].p->name != currentUser->adj[i].p->adj[j].p->name && currentUser->adj[i].p->name != currentUser->adj[k].p->name && currentUser->name != currentUser->adj[i].p->adj[j].p->name){
                        for(int l = 0; l < currentUser->adj[i].p->adj[j].p->adj.size(); l++){   //Loops through mutual friends to check if mutual friend is already in vector
                            if(currentUser->adj[i].p->name == currentUser->adj[i].p->adj[j].p->adj[l].p->name){
                                nameFound = false;
                                for(int m = 0; m < names.size(); m++)
                                    if(currentUser->adj[i].p->adj[j].p->name == names[m])
                                        nameFound = true;
                                if(!nameFound)
                                    names.push_back(currentUser->adj[i].p->adj[j].p->name);
                            }
                        }
                    }
                }
            }
        }
        for(int i = 0; i < names.size(); i++)
            std::cout << names[i] << std::endl;
    }
    else
        std::cout << "Not logged in." << std::endl;
}

//Sends a "Friend Request"
//This function actually has multiple purposes. In our function, the graph works by making it so connections are one way.
//Two people are friends when they both have a connection pointed to each other.
//If there's only one connection, it's a friend connection one way.
void Graph::sendReq(std::string name){
    if(isLogged){
        person *Holder = NULL;
	std::cout<<Holder<<std::endl;
        bool requestToPerson = true;
        bool requestToUser = true;
	for(int i = 0; i <people.size(); i++){
	    if(people[i].name == ""){
		std::cout<<"There is no one by this name"<<std::endl;
		}else{
        for(int i = 0; i < people.size(); i++){
		//std::cout<<"3"<<std::endl;
            if(people[i].name == name){
                Holder = &people[i];
            }
        }
	}
}
	if(Holder == NULL){
	std::cout<<"person doesn't exist"<<std::endl;
	return;
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
        findDistricts();
    }
    else
        std::cout << "Not logged in." << std::endl;

}

//Removes a friend or a friend request connected to currentUser
void Graph::removeFriend(std::string name){
    if(isLogged){
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
    else
        std::cout << "Not logged in." << std::endl;
}

//Displays all friend requests directed to currentUser
void Graph::displayFriendReq(){
    if(isLogged){
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
    else
        std::cout << "Not logged in." << std::endl;

}

void Graph::logout(){
    currentUser = NULL;
    isLogged = false;
    std::cout << "You have been logged out" << std::endl;
}

