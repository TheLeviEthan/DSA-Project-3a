/* Author: Ethan Ruddell
 * Last Edited: 11/25/24
 *
 *
 */

#include <iostream>
#include <vector>
#include <map>
#pragma once
using namespace std:

class HashMap{
private:
    //struct to represent data points containing all information
    struct point{
        string county;
        string state;
        string date;
        int aqi;
        point* next;
        point(string county, string state, string date, int aqi){
            this->county = county;
            this->state = state;
            this->date = date;
            this->aqi = aqi;
            this->next = nullptr;
        }
    };

    //utilizing an unordered map to store a hashed string key and the int value for the AQI
    unordered_map<int, point> hashMap;
    int tableSize;
    double loadFactor;
    const double loadThreshold = 0.5;

    //helper function to update the load factor
    void updateTableSize();

    //conversion of the state, county, and date to a hashed int
    int hashFunction(point dataPoint, int tableSize);

    //given a key, iterate through linked list to see if point is present
    point findHelper(dataPoint);


public:
    //constructors
    HashMap(){
        this->tableSize = 5;
    }

    bool insert(string county, string state, string date, int aqi);
    bool remove(string county, string state, string date);
    int search(string county, string state, string date);
};