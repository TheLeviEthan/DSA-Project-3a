/* Author: Ethan Ruddell
 * Last Edited: 12/2/24
 *
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "BTree.h"
#include "Bridges.h"
#include "LineChart.h"
#include "hashMap.h"

using namespace std;

int main(){
    //DEBUG: clear test file upon start
    ofstream ofs;
    ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    //create two data types for comparison
    HashMap map;
    //BTree tree = BTree(0);

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
    }

    in.close();
    out.close();
}