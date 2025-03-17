#include <autoCompleteTree.h>
#include <dynamicArr.h>
#include <util.h>

void test() {
    Tree *tree = createTree();
    add(tree, "apple");
    add(tree, "banana");
    add(tree, "grape");
    add(tree, "orange");
    add(tree, "pear");
    add(tree, "peach");
    add(tree, "plum");
    add(tree, "melon");
    add(tree, "kiwi");
    add(tree, "cherry");
    print(tree->sizeTree);

    DynamicArrChar arr = {0};
    getAutoComplete(tree->root, "p", &arr);

    printTree(tree->root, 0);

    for (size_t i = 0; i < arr.count; i++) {
        print(arr.items[i]);
    }
}

int main() {
    test();
    return 0;
}
