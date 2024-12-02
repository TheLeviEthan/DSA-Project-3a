//
// Created by rudde on 11/25/2024.
//

#include <hashMap.H>
using namespace std;

void HashMap::updateTableSize() {
    //determine new load factor based off current and set table size
    loadFactor = (double)hashMap.size() / (double)tableSize;

    //check load factor against threshold for map resizing
    if(loadFactor >= loadThreshold){
        tableSize *= 2;
    }
}

int HashMap::hashFunction(point dataPoint, int tableSize) {
    //integers to contain int representations
    int hashVal;

    //determine int values for each variable in data point
    for(char i : dataPoint.county){
        hashVal += (int)i;
    }
    for(char i : dataPoint.state){
        hashVal += (int)i;
    }
    for(char i : dataPoint.date){
        hashVal += (int)i;
    }
}

point HashMap::findHelper(dataPoint){
    point currPoint = dataPoint;
    int hashVal = hashFunction(dataPoint, tableSize);

    //base case: data point is the first or only val at key
    if(hashMap[hashVal] == dataPoint){
        return dataPoint;
    }

    //iterates through linked list at key
    while(currPoint->next != nullptr){
        currPoint = currPoint->next;
        if(currPoint.county == dataPoint.count && currPoint.state == dataPoint.state && currPoint.data == dataPoint.date){
            return dataPoint;
        }
    }

    //data point is not in the map
    return nullptr;
}

//insertion function utilizing hash function
bool HashMap::insert(string county, string state, string date, int aqi) {
    //create new data point with all relevant data
    point dataPoint = point(county, state, date, aqi);

    //determine hash value
    int hashVal = hashFunction(dataPoint, tableSize);

    //check if map already contains same data point exactly
    if(findHelper(dataPoint)){
       return false;
    }

    //if not, insert it at FRONT of linked list
    if(hashMap.find(hashVal) != hashMap.end()){
        dataPoint->next = hashMap[hashVal];
    } else {
        dataPoint->next = nullptr;
    }
    hashMap[hashVal] = dataPoint;
    return true;
}

bool HashMap::remove(string county, string state, string date{
    //determine hash val of input
    hashVal = hashFunction(county, state, date);
    point dataPoint;

    //determine if the hash map does not contain the hash val
    if(hashMap.find(hashVal) == hashMap.end()){
        return false;
    } else {
        dataPoint = hashMap[hashVal];
        //if the hash map DOES contain the hash value, check the actual county, state, date
        if(hashMap[hashVal].county == county && hashMap[hashVal].state == state && hashMap[hashVal].date == date){
            hashMap.erase(hashVal);
        } else {
            dataPoint = dataPoint->next;
        }
    }
}
