#ifndef BTREE_H
#define BTREE_H

#include <vector>
#include <string>
#pragma once
using namespace std;

struct AQIData {
    string state;
    string county;
    string date; //YYYY-MM-DD format for parsing
    int aqi;

    AQIData(string county, string state, string date, int aqi){
        this->county = county;
        this->state = state;
        this->date = date;
        this->aqi = aqi;
    }

    // Comparison operator for sorting and searching
    bool operator<(const AQIData& other) const {
        return aqi < other.aqi;
    }

    bool operator>(const AQIData& other) const {
        return aqi > other.aqi;
    }

    bool operator==(const AQIData& other) const {
        return state == other.state && county == other.county && date == other.date && aqi == other.aqi;
    }
};

struct BTreeNode {
    vector<AQIData> keys;  //AQIData objects in the node
    vector<BTreeNode*> children; //Children pointers
    bool isLeaf; //True if leaf node

    BTreeNode(bool leaf) : isLeaf(leaf) {}
    ~BTreeNode() {
        for (auto child : children) {
            delete child;
        }
    }
};

class BTree {
private:
    BTreeNode* root;
    int t; // min degree of tree (max keys per node)

    // Helper functions
    void deleteTree(BTreeNode* node);
    void insertNonFull(BTreeNode* node, const AQIData& data);
    void splitChild(BTreeNode* parent, int index, BTreeNode* child);
    void searchByCountyHelper(BTreeNode* node, const string& state, const string& county, vector<AQIData>& results);
    void traverseHelper(BTreeNode* node);

public:
    BTree(int degree);
    ~BTree();
    void insert(string county, string state, string date, int aqi);
    bool search(string county, string state, string data);
    vector<AQIData> searchByCounty(const string& state, const string& county);
    void traverse();
};

#endif // BTREE_H
