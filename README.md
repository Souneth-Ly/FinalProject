# FinalProject
Final Project for CSCI-2270
Written by Austin Chau and Ameya Bahirat
Social Network Class

----------------
Project Summary
----------------
This class provides simple functions that create a directed graph of people and uses edges in order to establish friendship. The class allows various groups of people to be displayed. The function also allows friend requests to be sent, accepted, and deleted.

-----------
How to Run
-----------
Program comes with a "people.txt" file to use for example. This file has a list of people and their weights, which will be read in through the program. The format of the text file is the same as the one that was used for the zombie cities program in Assignment 8.

Can be run through terminal.
Compile with
g++ -std=c++11 FinalProject.h FinalProject.cpp main.cpp
Then run program with
./a.out "people.txt"
--------------
Group Members
--------------
Austin Chau
Ameya Bahirat

-------------
Contributors
-------------

-----------------
Open issues/bugs
-----------------
- The mutualFriends function seems very messy. Is there anything that can be done to make it cleaner?