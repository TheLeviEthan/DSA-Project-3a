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
    int countyInt;
    int stateInt;
    int dateInt;

    //strings to concatenate int representations
    string countyIntStr;
    string stateIntStr;
    string dateIntStr;

    //determine int values for each variable in data point
    for(char i : dataPoint.county){
        stateInt += (int)i;
    }
    for(char i : dataPoint.state){
        stateInt += (int)i;
    }
    for(char i : dataPoint.date){
        stateInt += (int)i;
    }

    //convert calculated integers to individual strings
    countyIntStr = to_string(countyIntStr);
    stateIntStr = to_string(stateIntStr);
    dateIntStr = to_string(dateIntStr);

    //concatenate strings, convert to int, mod table size, return
    return (stoi(countyIntStr + stateIntStr + dateIntStr) % tableSize);
}

point HashMap::findHelper(dataPoint){
    point currPoint = dataPoint;
    int hashVal = hashFunction(dataPoint, tableSize);

    //base case: data point is the first or only val at key
    if(hashMap[hashVal] == dataPoint){
        return true;
    }

    //iterates through linked list at key
    while(currPoint->next != nullptr){
        currPoint = currPoint->next;
        if(currPoint.county == dataPoint.count && currPoint.state == dataPoint.state && currPoint.data == dataPoint.date){
            return true;
        }
    }

    //data point is not in the map
    return false;
}

//insertion function utilizing hash function
bool HashMap::insert(string county, string state, string date, int aqi) {
    //create new data point with all relevant data
    point dataPoint = point(county, state, date, aqi);

    //determine hash value
    int hashVal = hashFunction(dataPoint, tableSize);

    //check if map already contains same data point exactly
    if(!findHelper(dataPoint)){
        //if not, insert it at FRONT of linked list
        dataPoint->next = hashMap[hashVal];
        hashMap[hashVal] = dataPoint;
    }
}


