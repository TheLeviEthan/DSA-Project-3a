/* Author: Ethan Ruddell, Bhavana Kavarthapu
 * Last Edited: 12/4/24
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

//include json implementation
using json = nlohmann::json;

using namespace std;

void getAQIs(std::vector<std::pair<std::string, int>> inputs) {
    std::vector<int> returnVect; // create an array of average AQIs for each month
    int monthAvg = 0;
    int monthTotal = 0;
    int monthsNum = 0;

    // for each month 1 through 12
    for (int i = 1; i <= 12; i++) {
        for (int j = 0; j < inputs.size(); j++) { // for every item in the input remaining
            if (std::stoi(inputs[j].first.substr(0, 2)) == i) { // if the month value matches the index
                monthTotal += inputs[j].second; // add AQI to month total
                monthsNum++; // increment number of AQIs in that month
                inputs.erase(inputs.begin() + j); // remove pair from input
            }
        }
        monthAvg = monthTotal / monthsNum; // calculate average for that month
        returnVect.push_back(monthAvg); // set month's index to its AQI average
    }

    // Specify the full path for the output file
    std::string filePath = "server/public/chartData.json";

    try {
        std::ofstream jsonOut(filePath);
        if (!jsonOut.is_open()) {
            throw std::ios_base::failure("Failed to open the file for writing.");
        }
        nlohmann::json j = returnVect; // Convert the vector to JSON format
        jsonOut << j;
        jsonOut.close();
        std::cout << "Data successfully written to: " << filePath << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error writing to file: " << e.what() << std::endl;
    }
}


int main() {
    //Data Structures
    HashMap map;
    BTree tree(3);
    fstream in;

    //opening files
    in.open("daily_aqi_by_county_2023.csv", ios::in);

    if (!in.is_open()) {
        cerr << "Error: Could not open input file!" << endl;
        return 1;
    }


    //strings from CSV read
    string county, state, date, aqiString;
    vector<string> row;
    string line, word, temp;

    getline(in, line);

    while (getline(in, line)) {
        row.clear();
        stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        county = row[1];
        state = row[0];
        date = row[4];
        aqiString = row[5];

        map.insert(county, state, date, stoi(aqiString));
        tree.insert(county, state, date, stoi(aqiString));
    }



    //variables
    int op = -1;
    string userState;
    string userCounty;
    string userDate;
    int userAQI;

    //>>>>>>>>HASH MAP IMPLEMENTATION<<<<<<<
    cout << "Welcome, to learn more about Air Quality Index(AQI) choose what you would to do!" << endl;
    while (op != 6) {
        cout << "----------------------------" << endl;
        cout << "Operations: (enter a number)\n" <<
             "1. Search for local AQI based on Date\n" <<
             "2. Graph Visualization local AQI\n" <<
             "3. Insert Data into Database\n" <<
             "4. Delete Data into Database\n" <<
             "5. References\n" <<
             "6. Exit" << endl;
        cin >> op;
        //Graph Visualization
        if (op == 1) {
            cout << "Enter your state" << endl;
            cin >> userState;
            cout << "Enter your county" << endl;
            cin >> userCounty;
            cout << "Enter your date" << endl;
            cin >> userDate;
            int foundAQI = map.search(userCounty, userState, userDate);
            if (foundAQI == -1) {
                cout << "Datapoint not found" << endl;
                continue;
            }
            cout << "Local AQI is " << foundAQI << endl;
        }
            //AQI Visualization
        else if (op == 2) {
            cout << "Enter your state" << endl;
            cin >> userState;
            cout << "Enter your county" << endl;
            cin >> userCounty;

            getAQIs(map.searchByCounty(userState, userCounty));

        }
            //Insert Data
        else if (op == 3) {
            cout << "Warning: All changes are permanent" << endl;
            cout << "Enter your state" << endl;
            cin >> userState;
            cout << "Enter your county" << endl;
            cin >> userCounty;
            cout << "Enter your Data (MM/DD/YYYY" << endl;
            cin >> userDate;
            cout << "date: " << date << endl;
            cout << "Enter your AQI (integer)" << endl;
            cin >> userAQI;
            if (map.insert(userCounty, userState, userDate, userAQI)) {
                cout << "Data Point Inserted!" << endl;
            } else { cout << "Insertion failed" << endl; }
        }
            //Delete Data
        else if (op == 4) {
            cout << "Warning: All changes are permanent" << endl;
            cout << "Enter your state" << endl;
            cin >> userState;
            cout << "Enter your county" << endl;
            cin >> userCounty;
            cout << "Enter your Data (MM/DD/YYYY" << endl;
            cin >> userDate;
            if (map.remove(userCounty, userState, userDate)) {
                cout << "Data Point Deleted!" << endl;
            } else { cout << "Deletion failed" << endl; }
        }
            //Show References
        else if (op == 5) {
            cout << "References\n" <<
                 " - https://aqs.epa.gov/aqsweb/airdata/download_files.html\n" <<
                 " - https://medium.com/@mohanakrishnakavali/about-hashmap-and-common-use-cases-d3e5134438e1\n" <<
                 " - https://www.pingcap.com/article/understanding-b-tree-and-hash-indexing-in-databases/#:~:text=B%2DTree%20indexing%20is"
                 <<
                 " - https://www.flaticon.com/free-icon/hash-browns_10773420?related_id=10773557&origin=search\n" <<
                 " - https://fonts.google.com/specimen/JetBrains+Mono\n" << endl;
        }

    }
    cout << "Program exited" << endl;

    //>>>>>>>>B TREE IMPLEMENTATION<<<<<
//    cout<<"Welcome, to learn more about Air Quality Index(AQI) choose what you would to do!"<<endl;
//    while(op != 6){
//        cout<<"----------------------------"<<endl;
//        cout<<"Operations: (enter a number)\n"<<
//            "1. Search for local AQI based on Date\n"<<
//            "2. Graph Visualization local AQI\n"<<
//            "3. Insert Data into Database\n"<<
//            "4. Delete Data into Database\n"<<
//            "5. References\n"<<
//            "6. Exit"<<endl;
//        cin >> op;
//        //Graph Visualization
//        if(op == 1){
//            cout<<"Enter your state"<<endl;
//            cin>>userState;
//            cout<<"Enter your county"<<endl;
//            cin>>userCounty;
//            cout<<"Enter your date"<<endl;
//            cin>>userDate;
//            int foundAQI = tree.search(userCounty, userState, userDate);
//            if(foundAQI==-1){
//                cout<<"Datapoint not found"<<endl;
//                continue;
//            }
//            cout<<"Local AQI is "<<foundAQI<<endl;
//        }
//            //AQI Visualization
//        else if(op == 2){
//            cout<<"Enter your state"<<endl;
//            cin>>userState;
//            cout<<"Enter your county"<<endl;
//            cin>>userCounty;
//            //getAQIs(tree.searchByCounty(userState, userCounty));
//
//        }
//            //Insert Data
//        else if(op == 3){
//            cout<<"Warning: All changes are permanent"<<endl;
//            cout<<"Enter your state"<<endl;
//            cin>>userState;
//            cout<<"Enter your county"<<endl;
//            cin>>userCounty;
//            cout<<"Enter your Data (MM/DD/YYYY"<<endl;
//            cin>>userDate;
//            cout<<"date: "<<date<<endl;
//            cout<<"Enter your AQI (integer)"<<endl;
//            cin>>userAQI;
//            tree.insert(userCounty, userState, userDate, userAQI);
//            if(tree.search(userCounty, userState, userDate)){
//                cout<<"Data Point Inserted!"<<endl;
//            }
//            else{cout<<"Insertion failed"<<endl;}
//        }
//            //Delete Data
//        else if(op == 4){
//            cout<<"Warning: All changes are permanent"<<endl;
//            cout<<"Enter your state"<<endl;
//            cin>>userState;
//            cout<<"Enter your county"<<endl;
//            cin>>userCounty;
//            cout<<"Enter your Data (MM/DD/YYYY"<<endl;
//            cin>>userDate;
//            if(tree.search(userCounty,userState,userDate)){
//
//                cout<<"Data Point Deleted!"<<endl;
//            }
//            else{cout<<"Deletion failed"<<endl;}
//        }
//            //Show References
//        else if(op == 5){
//            cout<<"References\n"<<
//                " - https://aqs.epa.gov/aqsweb/airdata/download_files.html\n"<<
//                " - https://medium.com/@mohanakrishnakavali/about-hashmap-and-common-use-cases-d3e5134438e1\n"<<
//                " - https://www.pingcap.com/article/understanding-b-tree-and-hash-indexing-in-databases/#:~:text=B%2DTree%20indexing%20is"<<
//                " - https://www.flaticon.com/free-icon/hash-browns_10773420?related_id=10773557&origin=search\n"<<
//                " - https://fonts.google.com/specimen/JetBrains+Mono\n"<<endl;
//        }
//
//    }
//    cout<<"Program exited"<<endl;
//}
}