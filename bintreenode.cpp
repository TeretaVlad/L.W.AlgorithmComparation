#include "bintreenode.h"

BinTreeNode::BinTreeNode(int data): m_data(data), left(nullptr), right(nullptr){}

BinTreeNode* BinTreeNode::insert(BinTreeNode *root, int data){
    if(!root){
        return new BinTreeNode(data);
    }
    if(data < root->m_data){
        insert(root->left, data);
    }else{
        insert(root->right, data);
    }

    return root;
}

void BinTreeNode::vectorToTree(BinTreeNode *root, QVector<int>& vector){
    for(int value : vector){
        BinTreeNode::insert(root, value);
    }
}

void BinTreeNode::TreeToVector(BinTreeNode *root, QVector<int>& vector){
    if (!root) return;

    TreeToVector(root->left, vector);
    vector.append(root->m_data);
    TreeToVector(root->right, vector);
}

void BinTreeNode::deleteTree(BinTreeNode *root){
    if (!root) return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
