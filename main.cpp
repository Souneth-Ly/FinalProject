
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
    std::cout << "3. Remove Friends" << std::endl;
    std::cout << "4. Display Everyone" << std::endl;
    std::cout << "5. Display Friends" << std::endl;
    std::cout << "6. Display Mutual Friends" << std::endl;
    std::cout << "7. Shortest connection path" << std::endl;
    std::cout << "8. Send Friend Request" << std::endl;
    std::cout << "9. Quit" << std::endl;//Logout?
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

   do
   {
       userinput = menu();
       switch(userinput){
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '6':
            break;
        case '7':
            break;
        case '8':
            break;
       }

   }while(userinput != '9');
   cout << "Goodbye!" << endl;
}

