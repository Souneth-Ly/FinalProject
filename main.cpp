
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "FinalProject.h"

using namespace std;
char menu()
{
    //Menu options still need work.
    char userinput;
    std::cout << "======Main Menu=====" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Add Friends" << std::endl;
    std::cout << "3. Remove Friend" << std::endl;
    std::cout << "4. Display Everyone" << std::endl;
    std::cout << "5. Display Friends" << std::endl;
    std::cout << "6. Display Mutual Friends" << std::endl;
    std::cout << "7. Display Friend Requests" << std::endl;
    std::cout << "8. Send Friend Request" << std::endl;
    std::cout << "9. Logout" << std::endl;
    std::cout << "Q. Quit" << std::endl;//Logout?
    cin >> userinput;
    return userinput;
}

int main(int argc, char* argv[])
{
    ifstream infile(argv[1]);
    vector<string> cities;
    //int distanceArray[15][15];
    int i = 0;
    int n = 0;
    string input;
    string input2;
    char userinput;
    string line;
    string word;
    bool sourceExist = false;
    bool destExist = false;
    //int distanceArrayInt;
    Graph G;
    //string distanceValue;
while(getline(infile, line))
    {
        vector<string> vect;
        stringstream ss(line);

        while(getline(ss, word, ','))
            vect.push_back(word);

        if(vect[0] == "people")
        {
            for(int i = 1; i < vect.size(); i++)
            {
                G.addPerson(vect[i]);
                cities.push_back(vect[i]);
            }
        }
        else
        {
            for(int i = 1; i < vect.size();i++){
                G.addConnection(vect[0], cities[i-1], stoi(vect[i]));
            }
        }
        vect.clear();
    }

    G.findDistricts();

   do
   {
       userinput = menu();
       switch(userinput){
        case '1':
            cin.ignore();
            cout << "Please enter login name" << endl;
            getline(cin, input);
            G.login(input);
            break;
        case '2':
            break;
        case '3':
            cin.ignore();
            cout << "Please enter a name" << endl;
            getline(cin, input);
            G.removeFriend(input);
            break;
        case '4':
            G.displayEveryone();
            break;
        case '5':
            G.displayFriends();
            break;
        case '6':
            G.displayMutual();
            break;
        case '7':
            G.displayFriendReq();
            break;
        case '8':
            cin.ignore();
            cout << "Please enter a name" << endl;
            getline(cin, input);
            G.sendReq(input);
            break;
        case '9':
            G.logout();
            break;
       }

   }while(userinput != 'Q');
   cout << "Goodbye!" << endl;
}

