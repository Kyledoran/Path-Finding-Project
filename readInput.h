//
// Created by Kyle Doran on 3/31/21.
//

#ifndef PA04_AMAZING_READINPUT_H
#define PA04_AMAZING_READINPUT_H
#include <iomanip>
#include <iostream>
#include <fstream>
#include "room.h"
#include "Stack.h"
#include "DoublyLinkedList.h"
#include "adjacencyList.h"
class readInput{
private:
    Vector<room> roomVector;
    Stack<int> roomStack;
    adjacencyList adjacentList;
    Vector<DoublyLinkedList<int>> pathCosts;
    Vector<Vector<int>> finalPaths;
int numOfRows;
int numOfColumns;
public:
    readInput();
    void readData(std::ifstream &fin);
    void createAdjList();
    void findPaths();
    void findMax(std::ofstream &out);
    void findMin(std::ofstream &out);

};

readInput::readInput() {

}

void readInput::readData(std::ifstream &fin) {  //reads in maze data and stores all rooms in a vector

    if(!fin.is_open()) throw std::runtime_error("Could not open file");
    numOfRows = 0;
    numOfColumns = 0;
    fin >> numOfRows;
    fin >> numOfColumns;
    char getRooms = 'x';
    int getRoom = 0;
    for (int i = 0; i < numOfRows; ++i) {
        for (int j = 0; j < numOfColumns; ++j) {
            room object;
            fin >> getRooms;
            if (getRooms == '0') //0 if room is open
                getRoom = 0;
            if (getRooms == '1') //1 if it is a wall
                getRoom = 1;
            object.setIsOpen(getRoom);
            object.setRoomLocationX(i + 1); //sets x and y locations based on i,j
            object.setRoomLocationY(j + 1);
            roomVector.push(object);
        }
    }
    int numOfPortals = 0;
    int portalLocationX = 0;
    int portalLocationY = 0;
    int portalDestinationX = 0;
    int portalDestinationY = 0;
    int portalCost = 0;

    fin >> numOfPortals;
    for (int k = 0; k < numOfPortals; ++k) {
        fin >> portalLocationX;
        fin >> portalLocationY;
        fin >> portalDestinationX;
        fin >> portalDestinationY;
        fin >> portalCost;
        for (int i = 0; i < roomVector.size(); ++i) {  //sets which rooms contain a portal and where they lead to
            if ((portalLocationX == roomVector.operator[](i).getRoomLocationX()) &&
                (portalLocationY == roomVector.operator[](i).getRoomLocationY())) {
                roomVector.operator[](i).setContainsPortal(1);
                roomVector.operator[](i).setPortalTravelLocationX(portalDestinationX);
                roomVector.operator[](i).setPortalTravelLocationY(portalDestinationY);
                roomVector.operator[](i).setPortalCost(portalCost);
            }

        }

    }
    int startingLocationX = 0;
    int startingLocationY = 0;
    int endingLocationX = 0;
    int endingLocationY = 0;
    char remove;
    fin >> remove;
    fin >> startingLocationX;
    fin >> startingLocationY;
    fin >> remove;
    fin >> endingLocationX;
    fin >> endingLocationY;
    for (int i = 0; i < roomVector.size(); ++i) {  //sets starting and ending locations
        if ((startingLocationX == roomVector.operator[](i).getRoomLocationX()) && (startingLocationY == roomVector.operator[](i).getRoomLocationY())) {
            roomVector.operator[](i).setStartingLocation(1);
        }
        if ((endingLocationX == roomVector.operator[](i).getRoomLocationX()) && (endingLocationY == roomVector.operator[](i).getRoomLocationY())) {
            roomVector.operator[](i).setEndingLocation(1);
        }
    }
}

void readInput::createAdjList() {
    for (int i = 0; i < roomVector.size(); ++i) {
        if(roomVector.operator[](i).getIsOpen()) { //checks if room is open or a wall

            if(roomVector.operator[](i-1).getIsOpen() && roomVector.operator[](i).getRoomLocationX() == roomVector.operator[](i -1).getRoomLocationX() && i > 0) // checks if the adjacent room to the left is open and if they are on the same row to account for rooms in the first column.
            adjacentList.add_edge(i, i-1);

            if(roomVector.operator[](i+1).getIsOpen() && roomVector.operator[](i).getRoomLocationX() == roomVector.operator[](i+1).getRoomLocationX() && i < numOfRows * numOfColumns -1) //checks if the adjacent room to the left is open and if they are on the same row to account for rooms in the last column.
                adjacentList.add_edge(i, i+1);

            if(roomVector.operator[](i-numOfColumns).getIsOpen() && roomVector.operator[](i).getRoomLocationX()>1)  //checks adjacent room above and adds to adjacency list unless it is the first row of rooms
                adjacentList.add_edge(i, i-numOfColumns);

            if (roomVector.operator[](i+numOfColumns).getIsOpen() && roomVector.operator[](i).getRoomLocationX()!=numOfRows) //checks adjacent room below and adds to adjacency list unless it is the last row of rooms
                adjacentList.add_edge(i, i+numOfColumns);

            if(roomVector.operator[](i).getContainsPortal()){  //checks for rooms that contain portals
                for (int j = 0; j < roomVector.size(); ++j) {
                    if(roomVector.operator[](i).getPortalTravelLocationX() == roomVector.operator[](j).getRoomLocationX() && roomVector.operator[](i).getPortalTravelLocationY() == roomVector.operator[](j).getRoomLocationY()) //checks entire room vector to see if a rooms portal destination equals another room's x and y location
                        adjacentList.add_edge_portal(i,j);

                }
            }


        }
    }

}

void readInput::findPaths() { //finds all possible paths for the maze
    int startingIndex = 0;
    int endingIndex = 0;
    int count = 0;
    for (int i = 0; i <roomVector.size() ; ++i) {  //finds index of starting room in room vector
        if(roomVector.operator[](i).isStartingLocation())
            startingIndex = i;
        if(roomVector.operator[](i).isEndingLocation()) //finds index of starting room in room vector
            endingIndex = i;
    }
    roomStack.push(startingIndex); //pushes starting room to the stack
    roomVector.operator[](startingIndex).setIsOnStack(1); //sets a boolean that keeps track of if a room is on the stack
    while(!roomStack.isEmpty()) {

    if(roomStack.peek() == endingIndex)  //checks if the top of the stack is the end of maze
    {
        for (int i = 0; i < roomStack.size()+1; ++i) {  //stores paths in a vector of vectors with ints

            finalPaths.operator[](count).push(roomStack.operator[](i)); //pushes room location
            if(roomVector.operator[](roomStack.operator[](i)).getContainsPortal() && roomVector.operator[](roomStack.operator[](i)).getPortalTravelLocationX() == roomVector.operator[](roomStack.operator[](i+1)).getRoomLocationX() && roomVector.operator[](roomStack.operator[](i)).getPortalTravelLocationY() == roomVector.operator[](roomStack.operator[](i+1)).getRoomLocationY())
                pathCosts.operator[](count).insertBack(roomVector.operator[](roomStack.operator[](i)).getPortalCost()); //checks if a room of the stack contains a portal and if the next room on the stack is equal to the portal destination of the prior room, if this is the case it means a portal was taken and we add the portal cost instead of one to the pathsCost vector
            else
            pathCosts.operator[](count).insertBack(roomVector.operator[](roomStack.operator[](i)).getCost());

        }
        count++; //keeps track of how many total paths have been stored for the maze

        roomStack.pop(); //pops ending location after we store path

        roomVector.operator[](endingIndex).setIsOnStack(0);

    } else {

        if(adjacentList.adjList.operator[](roomStack.peek()).operator[](adjacentList.adjList.operator[](roomStack.peek()).getCurrPtr()) == 0){ //checks if there are any unexplored adjacent rooms to the top room of stack. If all adjacent rooms have been explored but we are not at ending location, the top of the stack is popped
            roomVector.operator[](roomStack.peek()).setIsOnStack(0);
            adjacentList.adjList.operator[](roomStack.peek()).resetPtr();
            roomStack.pop();
        }
        if(roomStack.peek()!=0) { //checks if stack is empty
            if (roomVector.operator[](adjacentList.adjList.operator[](roomStack.peek()).operator[](adjacentList.adjList.operator[](roomStack.peek()).getCurrPtr())).getIsOnStack()) { //checks if connection is already on stack and moves iter if it is
                adjacentList.adjList.operator[](roomStack.peek()).incrementPtr();

            } else {
                if (adjacentList.adjList.operator[](roomStack.peek()).operator[](adjacentList.adjList.operator[](roomStack.peek()).getCurrPtr()) != 0) { //if it is not on the stack it is added to the stack here and the iter is moved forward
                    int temp = 0;
                    temp = adjacentList.adjList.operator[](roomStack.peek()).getCurrPtr();
                    adjacentList.adjList.operator[](roomStack.peek()).incrementPtr();
                    roomStack.push(adjacentList.adjList.operator[](roomStack.peek()).operator[](temp));
                    roomVector.operator[](roomStack.peek()).setIsOnStack(1);
                }

            }
        }
    }

    }




}

void readInput::findMax(std::ofstream &out){
    if(!out.is_open()) throw std::runtime_error("Could not open file");
    int max = 0;
    int maxIndex = 0;
    int size = 0;

    for (int k = 0; k < 200 ; ++k) { //finds how many paths were found in total
        if (pathCosts.operator[](k).sumData() != 0)
            size++;

    }

    for (int i = 0; i < size; ++i) { //checks if the sum of every path is greater than max, if it is max is set equal to that sum and the index for this path is stored
        if (pathCosts.operator[](i).sumData() > max){
            max = pathCosts.operator[](i).sumData();
            maxIndex = i;
        }

    }

    out << max << std::endl; //prints total cost for the most expensive path
   out << finalPaths.operator[](maxIndex).size() << std::endl; //prints total number of rooms in that path
    for (int j = 0; j < finalPaths.operator[](maxIndex).size(); ++j) { //prints x and y location for each room on the path along with the cost
        out << roomVector.operator[](finalPaths.operator[](maxIndex).operator[](j)).getRoomLocationX() << ",";
        out << roomVector.operator[](finalPaths.operator[](maxIndex).operator[](j)).getRoomLocationY() << " ";
        if(roomVector.operator[](finalPaths.operator[](maxIndex).operator[](j)).getContainsPortal() && roomVector.operator[](finalPaths.operator[](maxIndex).operator[](j)).getPortalTravelLocationX() == roomVector.operator[](finalPaths.operator[](maxIndex).operator[](j+1)).getRoomLocationX() && roomVector.operator[](finalPaths.operator[](maxIndex).operator[](j)).getPortalTravelLocationY() == roomVector.operator[](finalPaths.operator[](maxIndex).operator[](j+1)).getRoomLocationY())
        out << roomVector.operator[](finalPaths.operator[](maxIndex).operator[](j)).getPortalCost() << std::endl; //prints portal cost if a portal was taken otherwise it prints 1
        else
            out << roomVector.operator[](finalPaths.operator[](maxIndex).operator[](j)).getCost() << std::endl;


    }

}

void readInput::findMin(std::ofstream &out) { //same process as findMax function but for minimum
    if(!out.is_open()) throw std::runtime_error("Could not open file");
    int min = 100;
    int minIndex = 0;
    int size = 0;

    for (int k = 0; k < 200 ; ++k) {
        if (pathCosts.operator[](k).sumData() != 0)
            size++;

    }

    for (int i = 0; i < size; ++i) {
        if (pathCosts.operator[](i).sumData() < min){
            min = pathCosts.operator[](i).sumData();
            minIndex = i;
        }

    }

    out << min << std::endl;
    out << finalPaths.operator[](minIndex).size() << std::endl;
    for (int j = 0; j < finalPaths.operator[](minIndex).size(); ++j) {
        out << roomVector.operator[](finalPaths.operator[](minIndex).operator[](j)).getRoomLocationX() << ",";
        out << roomVector.operator[](finalPaths.operator[](minIndex).operator[](j)).getRoomLocationY() << " ";
        if(roomVector.operator[](finalPaths.operator[](minIndex).operator[](j)).getContainsPortal() && roomVector.operator[](finalPaths.operator[](minIndex).operator[](j)).getPortalTravelLocationX() == roomVector.operator[](finalPaths.operator[](minIndex).operator[](j+1)).getRoomLocationX() && roomVector.operator[](finalPaths.operator[](minIndex).operator[](j)).getPortalTravelLocationY() == roomVector.operator[](finalPaths.operator[](minIndex).operator[](j+1)).getRoomLocationY())
            out << roomVector.operator[](finalPaths.operator[](minIndex).operator[](j)).getPortalCost() << std::endl;
        else
            out << roomVector.operator[](finalPaths.operator[](minIndex).operator[](j)).getCost() << std::endl;


    }

}




#endif //PA04_AMAZING_READINPUT_H
