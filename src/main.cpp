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
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

void getAQIs(vector<pair<string, int>> inputs){
    vector<int> returnVect; //create an array of average AQIs for each month
    int monthAvg = 0;
    int monthTotal = 0;
    int monthsNum = 0;
    ofstream jsonOut("chartData.json");

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
        returnVect.push_back(monthAvg); //set month's index to its AQI average
    }

    json j = returnVect;
    jsonOut << j;
    jsonOut.close();
}

int main(){
    //DEBUG: clear test file upon start
    ofstream ofs;
    ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
    if (!ofs.is_open()) {
        cerr << "Error opening test.txt for clearing." << endl;
        return 1;
    }
    ofs.close();
    //create two data types for comparison
    HashMap map;
    //BTree tree = BTree(0);

    //create input and output strings
    fstream in;
    fstream out;

    //opening files
    in.open("daily_aqi_by_county_2023.csv", ios::in);
    out.open("test.txt", ios::out | ios::app);

    if (!in.is_open()) {
        cerr << "Error: Could not open input file!" << endl;
        return 1;
    }
    if (!out.is_open()) {
        cerr << "Error: Could not open output file!" << endl;
        return 1;
    }

    //strings from CSV read
    string county, state, date, aqiString;
    vector<string> row;
    string line, word, temp;

    getline(in, line);

    while(getline(in, line)){
        //DEBUG: write to test file
        //out << line << endl;
        row.clear();
        stringstream s(line);
        while(getline(s, word, ',')){
            row.push_back(word);
        }
        county = row[1];
        state = row[0];
        date = row[4];
        aqiString = row[5];
        //DEBUG: test variable assignments from read
        out << state << "," << county << "," << date << "," << aqiString << endl;

        map.insert(county, state, date, stoi(aqiString));
    }


    getAQIs(map.searchByCounty("Idaho", "Bannock"));

    in.close();
    out.close();

    return 0;
}