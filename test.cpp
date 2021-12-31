#include "catch.hpp"
#include "adjacencyList.h"
#include "DoublyLinkedList.h"
#include "Stack.h"
#include "Vector.h"
TEST_CASE( "testing push function", "[Stack]" ) {

    Stack<int> test;

    SECTION("pushing and checking top value of stack")
    {
    test.push(0);
    test.push(1);
    test.push(2);
    REQUIRE(test.peek() == 2);
    }
    SECTION("pushing when stack size > 100")
    {
        for (int i = 0; i < 1110; i++) {
            test.push(i);

        }
    REQUIRE(!test.isFull());
    REQUIRE(test.peek() > 1000);
    }

}
TEST_CASE( "testing pop function", "[Stack]" ) {

    Stack<int> test1;

    SECTION("Pop on stack that is full") {
        test1.push(0);
        test1.push(1);
        test1.push(2);
        REQUIRE(test1.peek() == 2);
        test1.pop();
        REQUIRE(test1.peek() == 1);

    }SECTION("Pop on an empty stack") {

        REQUIRE(test1.pop() == 0);
        test1.pop();
        REQUIRE(test1.isEmpty());


    }
}
 TEST_CASE( "testing peek function", "[Stack]" ) {

    Stack<int> test2;

    SECTION("Peek on full stack") {
        test2.push(1);
        test2.push(2);
        test2.push(3);
        REQUIRE(test2.peek() == 3);
        test2.pop();
        REQUIRE(test2.peek() == 2);

    }
    SECTION("Peek on an empty stack") {
        test2.push(1);
        REQUIRE(test2.peek() == 1);
        test2.pop();
        REQUIRE(test2.isEmpty());


    }
}
TEST_CASE( "testing isFull function", "[Stack]" ) {

    Stack<int> test3;
    Stack<int> test4;

    SECTION("isFull on full stack") {
        for (int i = 0; i < 1101; i++) {
            test3.push(i);

        }
        REQUIRE(!test3.isFull());


    }
    SECTION("isFull on an empty stack") {
    REQUIRE(!test4.isFull());


    }
    SECTION("isFull on an half filled stack") {
        for (int i = 0; i < 50; i++) {
            test4.push(i);

        }
    REQUIRE(!test4.isFull());

    }

}
TEST_CASE( "testing isEmpty function", "[Stack]" ) {

    Stack<int> test5;
    Stack<int> test6;

    SECTION("isEmpty on full stack") {
        for (int i = 0; i < 101; i++) {
            test5.push(i);

        }
        REQUIRE(!test5.isEmpty());


    }
    SECTION("isEmpty on an empty stack") {
        REQUIRE(test6.isEmpty());


    }
    SECTION("isEmpty on an half filled stack") {
        for (int i = 0; i < 50; i++) {
            test6.push(i);

        }
        REQUIRE(!test6.isEmpty());

    }

}
TEST_CASE( "testing insertFront function", "[DoublyLinkedList]" ) {


    DoublyLinkedList<int> testList;

    SECTION("insertFront on empty list") {
    testList.insertFront(1);
    REQUIRE(testList.head->next->data == 1);
    REQUIRE(testList.tail->prev->data == 1);

    }
    SECTION("insertFront on full list") {
        testList.insertFront(1);
        testList.insertFront(2);
        testList.insertFront(3);
        REQUIRE(testList.head->next->data == 3);
        REQUIRE(testList.tail->prev->data == 1);
        REQUIRE(testList.head->next->next->data == 2);

    }

}
TEST_CASE( "testing insertBack function", "[DoublyLinkedList]" ) {


    DoublyLinkedList<int> testList;

    SECTION("insertBack on empty list") {
        testList.insertBack(1);
        REQUIRE(testList.head->next->data == 1);
        REQUIRE(testList.tail->prev->data == 1);

    }SECTION("inserBack on full list") {
        testList.insertBack(1);
        testList.insertBack(2);
        testList.insertBack(3);
        REQUIRE(testList.head->next->data == 1);
        REQUIRE(testList.tail->prev->data == 3);
        REQUIRE(testList.head->next->next->data == 2);

    }

}
TEST_CASE( "testing contains function", "[DoublyLinkedList]" ) {


    DoublyLinkedList<int> testList;

    SECTION("contains() on empty list") {
        REQUIRE(!testList.contains(4));

    }
    SECTION("contains() on full list with no match") {
        testList.insertBack(1);
        testList.insertBack(2);
        testList.insertBack(3);

        REQUIRE(!testList.contains(4));
    }
    SECTION("contains() on full list with a match") {
        testList.insertBack(1);
        testList.insertBack(2);
        testList.insertBack(3);

        REQUIRE(testList.contains(3));
    }

}
TEST_CASE( "testing remove function", "[DoublyLinkedList]" ) {


    DoublyLinkedList<int> testList;

    SECTION("remove on list with no match") {
        testList.insertBack(1);
        testList.insertBack(2);
        testList.remove(3);
        REQUIRE(testList.head->next->data == 1);
        REQUIRE(testList.tail->prev->data == 2);
    }
    SECTION("remove last element of list") {
        testList.insertBack(1);
        testList.insertBack(2);
        testList.remove(2);
        REQUIRE(!testList.contains(2));
        REQUIRE(testList.head->next->next == testList.tail);
        REQUIRE(testList.tail->prev->data == 1);
    }
    SECTION("remove first element of list") {
        testList.insertBack(1);
        testList.insertBack(2);
        testList.insertBack(3);
        testList.remove(1);
        REQUIRE(!testList.contains(1));
        REQUIRE(testList.head->next->data == 2);
        REQUIRE(testList.head->next->prev == testList.head);
    }
    SECTION("remove middle element of list") {
        testList.insertBack(1);
        testList.insertBack(2);
        testList.insertBack(3);
        testList.remove(2);
        REQUIRE(!testList.contains(2));
        REQUIRE(testList.head->next->next->data == 3);
        REQUIRE(testList.tail->prev->prev->data == 1);
    }

}

TEST_CASE( "testing addEdge function", "[adjacencyList]" ) {
    adjacencyList myList;
    SECTION("addEdge on empty list"){
        myList.add_edge(0,1);
        myList.add_edge(0,2);
        myList.add_edge(0,3);
        myList.add_edge(1,2);
        myList.add_edge(2,3);
        REQUIRE(myList.adjList.operator[](0).operator[](0) == 1);
        REQUIRE(myList.adjList.operator[](0).operator[](1) == 2);
        REQUIRE(myList.adjList.operator[](0).operator[](2) == 3);
        REQUIRE(myList.adjList.operator[](1).operator[](0) == 0);
        REQUIRE(myList.adjList.operator[](1).operator[](1) == 2);
        REQUIRE(myList.adjList.operator[](2).operator[](0) == 0);
        REQUIRE(myList.adjList.operator[](2).operator[](1) == 1);
        REQUIRE(myList.adjList.operator[](2).operator[](2) == 3);
    }
    SECTION("same addEdge called twice"){
        myList.add_edge(0,1);
        myList.add_edge(0,1);
        REQUIRE(myList.adjList.operator[](0).operator[](0) == 1);
        REQUIRE(myList.adjList.operator[](0).operator[](1) != 1);
    }
    SECTION("addEdge  making sure destination vector is updated properly"){
        myList.add_edge(0,1);
        myList.add_edge(0,2);
        myList.add_edge(2,1);
        myList.add_edge(2,3);
        REQUIRE(myList.adjList.operator[](1).operator[](0) == 0);
        REQUIRE(myList.adjList.operator[](2).operator[](0) == 0);
        REQUIRE(myList.adjList.operator[](2).operator[](1) == 1);
        REQUIRE(myList.adjList.operator[](2).operator[](2) == 3);
        REQUIRE(myList.adjList.operator[](3).operator[](0) == 2);
    }

}
TEST_CASE( "testing get adjacent rooms function", "[adjacencyList]" ) {
    adjacencyList myList;
    Vector<int> testVector;
    SECTION("when there are no adjacent rooms"){
        testVector.push(2);
        myList.get_adjacent_rooms(3);
        REQUIRE(myList.adjList.size() == 0);
        REQUIRE(!myList.get_adjacent_rooms(2).operator==(testVector));
    }
    SECTION("when there are adjacent rooms"){
        myList.add_edge(0,1);
        myList.add_edge(0,2);
        myList.add_edge(2,1);
        myList.add_edge(2,3);
        testVector.push(0);
        testVector.push(1);
        testVector.push(3);
       REQUIRE(myList.get_adjacent_rooms(2).operator==(testVector));
    }
}




