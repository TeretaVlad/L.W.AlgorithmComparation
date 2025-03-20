#ifndef BINTREENODE_H
#define BINTREENODE_H
#include <cstdint>
#include <QVector>

class BinTreeNode
{
private:
    int m_data;
    BinTreeNode* left;
    BinTreeNode* right;
public:
    BinTreeNode(int data);

    static BinTreeNode* insert(BinTreeNode* root, int data);
    static void vectorToTree(BinTreeNode* root, QVector<int> &vector);
    static void TreeToVector(BinTreeNode* root, QVector<int> &vector);

    static void deleteTree(BinTreeNode* root);
};

#endif // BINTREENODE_H
