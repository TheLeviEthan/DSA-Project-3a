#ifndef HASHMAP_H
#define HASHMAP_H
#pragma once
#include <string>
#include <unordered_map>

using namespace std;

class HashMap {
private:
    struct Point {
        //data contained in each data point
        std::string county;
        std::string state;
        std::string date;
        int aqi;
        Point* next; //next data point for linked list

        //constructor
        Point(string county,  string state, string date, int aqi)
                : county(county), state(state), date(date), aqi(aqi), next(nullptr) {}
    };

    //data required for hash map
    Point** table; //pointer to the hash table
    int maxSize; //current size of the table
    int currSize; //number of elements in the hash table,
    const double loadFactorThreshold = 0.5;

    //hash function
    int hashFunction(string county,  string state, string date);

    //rehash and resize function
    void rehash();

public:
    //constructor w/ default initial size
    HashMap(int initialSize = 5);

    //destructor
    ~HashMap();

    //functions
    bool insert(string county, string state, string date, int aqi);
    bool remove(string county, string state, string date);
    int search(string county, string state, string date);
    void printGraph();
};

#endif
