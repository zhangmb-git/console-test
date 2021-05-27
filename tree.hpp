#pragma once
#include <stdio.h>
#include <stack>
#include <queue>

struct Node {
    Node(int x): data(x), left(nullptr), right(nullptr) {};
    Node* left;
    Node* right;
    int data;
};

Node*    CreateTree(Node* root) {
    root = new Node(1);
    Node*  leaf2 = new Node(2);
    Node*  leaf3 = new Node(3);
    Node*  leaf4 = new Node(4);
    Node*  leaf5 = new Node(5);
    Node*  leaf6 = new Node(6);
    Node*  leaf7 = new Node(7);
    root->left = leaf2;
    root->right = leaf3;

    leaf2->left = leaf4;
    leaf2->right = leaf5;

    leaf3->left = leaf6;
    leaf3->right = leaf7;

    return root;
}

void preorder(Node* node) {
    if (node == nullptr) return;

    printf("%d \n", node->data);
    preorder(node->left);
    preorder(node->right);
}

void norecurse_preorder(Node* pNode) {
    if (pNode == nullptr) return;

    std::stack<Node*> stkNode;
    stkNode.push(pNode);

    while (!stkNode.empty()) {
        Node* tmp = stkNode.top();
        stkNode.pop();
        printf("%d \n", tmp->data);

        if (tmp->right)
            stkNode.push(tmp->right);

        if (tmp->left)
            stkNode.push(tmp->left);
    }

    return;
}

void  bfs_tree(Node* node) {
    if (node == nullptr)  return;

    std::queue<Node*> node_list;
    node_list.push(node);

    while (!node_list.empty()) {
        Node* pTmp = node_list.front();
        node_list.pop();
        printf("%d \n", pTmp->data);

        if (pTmp->left) {
            node_list.push(pTmp->left);
        }

        if (pTmp->right) {
            node_list.push(pTmp->right);
        }
    }

    return;

}

struct  graphNode {
    int label;
    std::vector<graphNode*> neighbours;
    graphNode(int x) : label(x) {
    }
};

void  BFS_Graph() {

}

bool   binary_search(std::vector<int>& sort_array, int begin, int end, int target ) {
    if (begin > end) return  false;  //×¢ÒâÃ»ÓÐ =

    int  i = begin;
    int j = end;
    int mid = (begin + end) / 2;

    if (sort_array[mid] == target)  return true;

    if (target < sort_array[mid]) {
        return  binary_search(sort_array, begin, mid - 1, target);

    } else {
        return binary_search(sort_array, mid + 1, end, target);
    }
}


bool   binary_search(std::vector<int>& sort_array, int target) {
    int begin = 0;
    int end = sort_array.size() - 1;

    while (begin <= end) {
        int mid = (begin + end) / 2;

        if (sort_array[mid] == target)  return true;

        if (target < sort_array[mid]) {
            end = mid - 1;

        } else {
            begin = mid + 1;
        }
    }

}










