#include "Vector.h"
#ifndef PA04_AMAZING_ADJACENCYLIST_H
#define PA04_AMAZING_ADJACENCYLIST_H

class adjacencyList{
public:
    Vector<Vector<int>> adjList;

    adjacencyList() {

    }
    void add_edge(int source, int destination) {
        int count = 0;
        for (int i = 0; i < adjList.operator[](source).size() ; ++i) {
            if(adjList.operator[](source).operator[](i) == destination){
                count++;
            }
        }
        if(count == 0) {
            adjList.operator[](source).push(destination);
            adjList.operator[](destination).push(source);
        }

    }
    void add_edge_portal(int source, int destination) {
        int count = 0;
        for (int i = 0; i < adjList.operator[](source).size() ; ++i) {
            if(adjList.operator[](source).operator[](i) == destination){
                std::cout << "These rooms are already connected" << std::endl;
                count++;
            }
        }
        if(count == 0) {
            adjList.operator[](source).push(destination);
        }

    }
    Vector<int> get_adjacent_rooms(int some_room){
        if(adjList.operator[](some_room).size()==0)
            std::cout << "No matching room found" << std::endl;
        else
            return adjList.operator[](some_room);

    }

};
#endif //PA04_AMAZING_ADJACENCYLIST_H
