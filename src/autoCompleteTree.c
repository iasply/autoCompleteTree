#include <assert.h>
#include <autoCompleteTree.h>
#include <dynamicArr.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>

#define EQUAL 0

int comp(char *a, char *b) { return strcmp((const char *)a, (const char *)b); }

Node *createNode(char *str) {
    Node *new = (Node *)calloc(1, sizeof(Node));
    new->str  = strdup(str);

    return new;
}

Tree *createTree() { return (Tree *)calloc(1, sizeof(Tree)); }

Node *insert(Node *node, char *str, size_t *size) {
    if (!node) {
        (*(size))++;
        return createNode(str);
    }

    // left -1
    // right +1
    //  equals 0 (dont add);
    int result = comp(node->str, str);

    if (result == EQUAL) {
        return node;
    }

    if (result > 0) {
        node->left = insert(node->left, str, size);
    } else {
        node->right = insert(node->right, str, size);
    }

    return node;
}

void inOrder(Node *node) {
    if (node) {
        inOrder(node->left);
        print(node->str);
        inOrder(node->right);
    }
}

void preOrder(Node *node) {
    if (node) {
        print(node->str);
        preOrder(node->left);
        preOrder(node->right);
    }
}

void posOrder(Node *node) {
    if (node) {
        posOrder(node->left);
        posOrder(node->right);
        print(node->str);
    }
}

void add(Tree *tree, char *str) {
    assert(tree);
    assert(str);
    tree->root = insert(tree->root, str, &tree->sizeTree);
}

Node *search(Node *node, char *str) {
    if (!node) {
        return NULL;
    }

    int result = comp(node->str, str);

    if (result == EQUAL) {
        return node;
    }

    if (result > 0) {
        return search(node->left, str);
    }

    return search(node->right, str);
}

bool isPrefix(char *prefix, char *str) {
    if (strlen(prefix) > strlen(str)) {
        return false;
    }

    while (*prefix) {
        if (*prefix != *str) {
            return false;
        }
        prefix++;
        str++;
    }

    return true;
}

void getAutoComplete(Node *node, char *prefix, DynamicArrChar *arr) {
    if (!node) {
        return;
    }

    int  cmp = comp(node->str, prefix);
    bool has = isPrefix(prefix, node->str);
    if (has) {
        da_append((*arr), strdup(node->str));
    }

    if (cmp > 0 && !has) {
        getAutoComplete(node->left, prefix, arr);
        return;
    }
    getAutoComplete(node->left, prefix, arr);
    getAutoComplete(node->right, prefix, arr);
}

void printTree(Node *node, int level) {
    if (node == NULL) {
        return;
    }

    printTree(node->right, level + 1);

    for (int i = 0; i < level; i++) {
        printf("     ");
    }

    printf("-> %s\n", node->str);

    printTree(node->left, level + 1);
}
