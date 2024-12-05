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
    AQIData() : state(""), county(""), date(""), aqi(0) {}
    AQIData(string county, string state, string date, int aqi){
        this->county = county;
        this->state = state;
        this->date = date;
        this->aqi = aqi;
    }

    bool operator<(const AQIData& other) const {
        if (state != other.state) return state < other.state;
        if (county != other.county) return county < other.county;
        return date < other.date; // Compare date as the next priority
    }

    bool operator>(const AQIData& other) const {
        if (state != other.state) return state > other.state;
        if (county != other.county) return county > other.county;
        return date > other.date; // Compare date as the next priority
    }

    bool operator==(const AQIData& other) const {
        return state == other.state && county == other.county && date == other.date;
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
    void searchByCountyHelper(BTreeNode* node, const std::string& state, const std::string& county, vector<pair<string, int>>& results);
    void traverseHelper(BTreeNode* node);
    void deleteNodeHelper(BTreeNode* node, const AQIData& target);
    void removeInternalNode(BTreeNode* node, int idx);
    AQIData getPredecessor(BTreeNode* node, int idx);
    AQIData getSuccessor(BTreeNode* node, int idx);
    void fill(BTreeNode* parent, int idx);
    void borrowFromPrev(BTreeNode* parent, int idx);
    void borrowFromNext(BTreeNode* parent, int idx);
    void merge(BTreeNode* parent, int idx);

public:
    BTree(int degree);
    ~BTree();
    void insert(string county, string state, string date, int aqi);
    int search(string county, string state, string date);
    vector<pair<string, int>> searchByCounty(const string& state, const string& county);
    void traverse();
};

#endif // BTREE_H
