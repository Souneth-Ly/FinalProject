#ifndef FINALPROJECT_H
#define FINALPROJECT_H
#include <vector>
#include <iostream>
#include <queue>

struct person;
struct connection;

struct connection{
    person *p;
    bool isfriend = false;
};

struct person{
    std::string name;
    bool visited;
    int groupID = -1;
    person *previous;
    std::vector<connection> adj;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addPerson(std::string name);
        void addConnection(std::string, std::string, int weight);
        void login(std::string);
        void removeFriend(std::string name);
        void sendReq(std::string name);
        void displayFriends();
        void displayEveryone();
        void displayMutual();
        void displayFriendReq();
        void findDistricts();
        void BFTraversal(std::string);
        void logout();
    protected:
    private:
        //vector<edge> edges;
        std::vector<person> people;
        person *currentUser;
        bool isLogged = false;

};

#endif // FINALPROJECT_H
