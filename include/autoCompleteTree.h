#pragma once

#include <dynamicArr.h>
#include <stddef.h>

#define UNLIMITED_FETCH 0

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

void getAutoComplete(Node *node, char *prefix, DynamicArrChar *arr,
                     size_t maxFetch);

void printTree(Node *node, int level);

Tree **loadDictionary();

Tree *getTreeForWord(Tree **trees, const char *word);

void delete(Tree *tree, char *str);