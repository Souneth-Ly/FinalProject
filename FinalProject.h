#ifndef FINALPROJECT_H
#define FINALPROJECT_H
#include<vector>
#include<iostream>

struct vertex;

struct connection{
    person *p;
    bool isfriend;
};

struct person{
    std::string name;
    bool visited;
    int personID = -1;
    person *previous;
    std::vector<connection> adj;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addConnection(std::string name);
        void addPerson(std::string name);
        void removePerson(std::string name);
        void displayFriends();
        void displayEveryone();
        void displayMutual();
        //void displayFriendReq();
        void findDistricts();//..change name later
        void BFTraversal(std::string name);
        void shortestConnectionPath(std::string ending_name);
        void sendReq(std::string name);
    protected:
    private:
        //vector<edge> edges;
        std::vector<person> people;
        person *currentUser;
        bool ifLogged;

};

#endif // FINALPROJECT_H
