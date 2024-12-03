#include "hashMap.h"
#include <iostream>
#include <stdexcept>

using namespace std;

HashMap::HashMap(int initialSize) //constructor, initial size and currSize set to 0
{
    maxSize = initialSize;
    table = new Point*[maxSize];
    for (int i = 0; i < maxSize; ++i) {
        table[i] = nullptr;
    }
}

HashMap::~HashMap() { //destructor for entire map
    for (int i = 0; i < maxSize; ++i) {
        Point* current = table[i];
        while (current) {
            Point* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
    delete[] table;
}

int HashMap::hashFunction(string county,  string state, string date)  {
    int hashVal = 0;
    //add int representation of each character in county, state, date
    for (char c : county) hashVal += c;
    for (char c : state) hashVal += c;
    for (char c : date) hashVal += c;
    return hashVal % maxSize;
}

void HashMap::rehash() {
    int oldSize = maxSize; //save old size to iterate rehash
    maxSize *= 2; //double the current table size
    Point** oldTable = table; //copy the old table into temporary var to get values

    table = new Point*[maxSize]; //create new table with new doubled size
    for (int i = 0; i < maxSize; ++i) { //set each val in new table to null
        table[i] = nullptr;
    }
    currSize = 0; //initialize size of new map

    for (int i = 0; i < oldSize; ++i) {
        Point* current = oldTable[i]; //current pointer tracks old values
        while (current != nullptr) { //iterating through linked list at each key
            insert(current->county, current->state, current->date, current->aqi);
            Point* toDelete = current; //save pointer to delete to manage mem
            current = current->next; //next item in linked list
            delete toDelete; //delete old item
        }
    }
    delete[] oldTable; //delete pointer to old table
}

bool HashMap::insert(string county,  string state, string date, int aqi) {
    if ((double)(currSize) / (double)maxSize >= loadFactorThreshold) { //check size constraint
        rehash(); //rehash and resize if current size too large
    }

    int hashVal = hashFunction(county, state, date); //create hash val for new data
    Point* current = table[hashVal]; //identify item at key = hashVal

    while (current != nullptr) { //iterate through linked list if there is already val at key = hashVal
        if (current->county == county && current->state == state && current->date == date) { //if already present
            return false;
        }
        current = current->next; //next item in linked list
    }

    Point* newPoint = new Point(county, state, date, aqi); //create new point
    newPoint->next = table[hashVal]; //insert at front of linked list at key = hashVal
    table[hashVal] = newPoint; //insert into hash table
    ++currSize;
    return true;
}

bool HashMap::remove(string county, string state, string date) {
    int hashVal = hashFunction(county, state, date); //determine hash val for given data
    Point* current = table[hashVal]; //see what is at key = hashVal
    Point* prev = nullptr; //previous pointer for deletion within linked list

    while (current != nullptr) { //while there is something
        if (current->county == county && current->state == state && current->date == date) { //if data point present
            if (prev != nullptr) { //if you are in the middle of linked list
                prev->next = current->next; //set prev's next value to current's next value
            } else { //only item in the linked list
                table[hashVal] = current->next; //set hashVal's value to null
            }
            delete current; //memory mnage
            --currSize;
            return true;
        }
        prev = current; //iterate through linked list
        current = current->next;
    }
    return false;
}

int HashMap::search(string county, string state, string date){
    int hashVal = hashFunction(county, state, date); //determine hash val for given data
    Point* current = table[hashVal]; //see what is at key = hashVal

    while (current != nullptr) { //while there is something
        if (current->county == county && current->state == state && current->date == date) { //if data point = given
            return current->aqi; //return aqi for that data point
        }
        current = current->next; //iterate through linked list
    }
    return -1;
}

void HashMap::printGraph(){
    for (int i = 0; i < maxSize; ++i) { //for every item in table
        Point* current = table[i]; //current point = point at i
        std::cout << "Bucket " << i << ": ";
        while (current) {
            std::cout << "[" << current->county << ", " << current->state << ", " << current->date << ", " << current->aqi << "] -> ";
            current = current->next;
        }
        std::cout << "NULL\n";
    }
}
