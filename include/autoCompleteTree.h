#pragma once

#include <dynamicArr.h>
#include <stddef.h>

typedef struct Node {
    char        *str;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct Tree {
    Node  *root;
    size_t sizeTree;
    Node  *nodeWalker;
} Tree;

Tree *createTree();

void add(Tree *tree, char *str);

Node *search(Node *node, char *str);

void getAutoComplete(Node *node, char *prefix, DynamicArrChar *arr);

void printTree(Node *node, int level);