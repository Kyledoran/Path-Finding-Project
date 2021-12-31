//
// Created by Kyle Doran on 3/31/21.
//

#ifndef PA04_AMAZING_ROOM_H
#define PA04_AMAZING_ROOM_H
class room {
private:
 bool isOpen;
 bool containsPortal;
 int portalCost;
 int portalTravelLocationX;
 int portalTravelLocationY;
int roomLocationX;
int roomLocationY;
bool startingLocation;
bool endingLocation;
bool isOnStack;
int cost;
public:
    room();
    void setIsOpen(int x);
    bool getIsOpen();
    void setContainsPortal(int x);
    bool getContainsPortal();
    void setPortalCost(int x);
    int getPortalCost();
    void setPortalTravelLocationX(int x);
    int getPortalTravelLocationX();
    void setPortalTravelLocationY(int x);
    int getPortalTravelLocationY();
    void setRoomLocationX(int x);
    int getRoomLocationX();
    void setRoomLocationY(int x);
    int getRoomLocationY();
    void setStartingLocation(int x);
    bool isStartingLocation();
    void setEndingLocation(int x);
    bool isEndingLocation();
    void setIsOnStack(int x);
    bool getIsOnStack();
    int getCost();


};

void room::setIsOpen(int x)  {
if(x == 0)
    isOpen = true;
if (x == 1)
    isOpen = false;
}

bool room::getIsOpen() {
    return isOpen;
}

void room::setContainsPortal(int x) {
    if(x == 0)
        containsPortal = false;
    if (x == 1)
        containsPortal = true;

}

bool room::getContainsPortal() {
    return containsPortal;
}

void room::setPortalCost(int x) {
    portalCost = x;


}

int room::getPortalCost() {
    return portalCost;
}

void room::setPortalTravelLocationX(int x) {
    portalTravelLocationX = x;

}

int room::getPortalTravelLocationX() {
    return portalTravelLocationX;
}

void room::setPortalTravelLocationY(int x) {
portalTravelLocationY = x;
}

int room::getPortalTravelLocationY() {
    return portalTravelLocationY;
}

void room::setRoomLocationX(int x) {
roomLocationX = x;
}

int room::getRoomLocationX() {
    return roomLocationX;
}

void room::setRoomLocationY(int x) {
    roomLocationY = x;

}

int room::getRoomLocationY() {
    return roomLocationY;
}

void room::setStartingLocation(int x) {
    if(x == 0)
        startingLocation = false;
    if (x == 1)
        startingLocation = true;

}

bool room::isStartingLocation() {
    return startingLocation;
}

void room::setEndingLocation(int x) {
    if(x == 0)
        endingLocation = false;
    if (x == 1)
        endingLocation = true;

}

bool room::isEndingLocation() {
    return endingLocation;
}

room::room() {
    isOpen = false;
    containsPortal = false;
    portalCost = 0;
    portalTravelLocationX = 0;
    portalTravelLocationY = 0;
    roomLocationX = 0;
    roomLocationY = 0;
    startingLocation = false;
    endingLocation = false;
    isOnStack = false;
    cost = 1;


}

void room::setIsOnStack(int x) {
    if(x == 0)
        isOnStack = false;
    if(x == 1)
        isOnStack = true;

}

bool room::getIsOnStack() {
    return isOnStack;
}

int room::getCost() {
    return cost;
}


#endif //PA04_AMAZING_ROOM_H
