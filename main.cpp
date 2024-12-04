/* Author: Ethan Ruddell
 * Last Edited: 12/2/24
 *
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "BTree.h"
#include "hashMap.h"

using namespace std;

int* getAQIs(vector<pair<string, int>> inputs){
    int returnArr[12]; //create an array of average AQIs for each month
    int monthAvg = 0;
    int monthTotal = 0;
    int monthsNum = 0;

    //for each month 1 through 12
    for(int i = 1; i <= 12; i++){
        for(int j = 0; j < inputs.size(); j++){ //for every item in the input remaining
            if(stoi(inputs[j].first.substr(0,2)) == i){ //if the month val = the index
                monthTotal += inputs[j].second; //add AQI to month total
                monthsNum ++; //iterate number of AQIs in that month
                inputs.erase(inputs.begin() + j); //remove pair from input
            }
        }
        monthAvg = monthTotal / monthsNum; //calculate average for that month
        returnArr[i-1] = monthAvg; //set month's index to its AQI average
    }
    return returnArr;
}

int main(){
    //DEBUG: clear test file upon start
    ofstream ofs;
    ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    //create two data types for comparison
    HashMap map;
    BTree tree = BTree(0);

    //create input and output strings
    fstream in;
    fstream out;

    //strings from CSV read
    string county, state, date, aqiString;

    //opening files
    in.open("daily_aqi_by_county_2023.csv", ios::in);
    out.open("test.txt", ios::out | ios::app);

    vector<string> row;
    string line, word, temp;

    while(getline(in, line)) {
        //DEBUG: write to test file
        //out << line << endl;

        row.clear();
        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        county = row[1];
        state = row[0];
        date = row[4];
        aqiString = row[5];

        //DEBUG: test variable assignments from read
        map.insert(county, state, date, stoi(aqiString));
        tree.insert(county, state, date, stoi(aqiString));
    }
    in.close();
    out.close();
}