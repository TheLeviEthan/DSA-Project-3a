#include "BTree.h"
#include <iostream>
#include <iomanip>
#include <sstream>

BTree::BTree(int degree) : root(nullptr), t(degree) {}

void BTree::deleteTree(BTreeNode* node) {
    if (!node) return;
    for (auto* child : node->children) {
        deleteTree(child);
    }
    delete node;
}

BTree::~BTree() {
    deleteTree(root);
}

// Insert data into B-tree
void BTree::insert(string county, string state, string date, int aqi) {
    AQIData data = AQIData(county, state, date, aqi);
    if (!root) {
        // If tree is empty new root is created
        root = new BTreeNode(true);
        root->keys.push_back(data);
    } else {
        if (root->keys.size() == 2 * t - 1) {
            // Must split if root is full (height increase)
            BTreeNode* newRoot = new BTreeNode(false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0, root);
            root = newRoot;
        }
        insertNonFull(root, data);
    }
}

// Splitting a full child node
void BTree::splitChild(BTreeNode* parent, int index, BTreeNode* child) {
    BTreeNode* newNode = new BTreeNode(child->isLeaf);

    // Move the second half of the keys to the new node
    newNode->keys.assign(child->keys.begin() + t, child->keys.end());
    child->keys.resize(t - 1);

    // Move the second half of the children if not leaf
    if (!child->isLeaf) {
        newNode->children.assign(child->children.begin() + t, child->children.end());
        child->children.resize(t);
    }

    // Insert new node into parents child
    parent->children.insert(parent->children.begin() + index + 1, newNode);

    // make middle key parent
    parent->keys.insert(parent->keys.begin() + index, child->keys[t - 1]);
}

// Insert into non full node
void BTree::insertNonFull(BTreeNode* node, const AQIData& data) {
    int i = node->keys.size() - 1;
    if (node->isLeaf) {
        while (i >= 0 && data < node->keys[i]) {
            i--;
        }
        node->keys.insert(node->keys.begin() + i + 1, data);
    } else {
        while (i >= 0 && data < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->keys.size() == 2 * t - 1) {
            splitChild(node, i, node->children[i]);
            if (data > node->keys[i]) i++;
        }
        insertNonFull(node->children[i], data);
    }
}

bool BTree::search(string county, string state, string date) {
    AQIData data = AQIData(county, state, date, 0);
    BTreeNode* curr = root;
    while (curr) {
        int i = 0;
        while (i < curr->keys.size() && data > curr->keys[i]) {
            i++;
        }
        if (i < curr->keys.size() && data == curr->keys[i]) {
            return true;
        }
        if (curr->isLeaf) return false;
        curr = curr->children[i];
    }
    return false;
}

std::vector<AQIData> BTree::searchByCounty(const std::string& state, const std::string& county) {
    std::vector<AQIData> results;
    searchByCountyHelper(root, state, county, results);
    return results;
}

void BTree::searchByCountyHelper(BTreeNode* node, const std::string& state, const std::string& county, std::vector<AQIData>& results) {
    if (!node) return;

    for (const auto& key : node->keys) {
        if (key.state == state && key.county == county) {
            results.push_back(key);
        }
    }

    if (!node->isLeaf) {
        for (auto* child : node->children) {
            searchByCountyHelper(child, state, county, results);
        }
    }
}

void BTree::traverse() {
    traverseHelper(root);
}

void BTree::traverseHelper(BTreeNode* node) {
    if (!node) return;
    for (const auto& key : node->keys) {
        std::cout << key.state << ", " << key.county << ", " << key.date << ": " << key.aqi << '\n';
    }
    for (auto* child : node->children) {
        traverseHelper(child);
    }
}
