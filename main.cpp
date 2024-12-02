/* Author: Ethan Ruddell
 * Last Edited: 12/2/24
 *
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "BTree.h"
#include "hashMap.h"

using namespace std;


int main(){
    //create two data types for comparison
    HashMap map;
    BTree tree = BTree(0);

    //create input and output strings
    fstream in;
    fstream out;

    //strings from CSV read
    string county, state, countyCode, stateCode, date, aqiString, endJunk;

    //opening files
    in.open("daily_aqi_by_county_2023.csv", ios::in);
    out.open("daily_aqi_by_county_2023.csv", ios::out | ios::app);

    vector<string> row;
    string line, word, temp;
    while(in >> temp){
        row.clear();
        getline(in, line);
        stringstream wholeLine(line);
        while(getline(wholeLine, word, ',')){
            row.push_back(word);
        }
    }
}