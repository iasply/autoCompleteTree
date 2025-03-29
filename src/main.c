#include <api.h>
#include <autoCompleteTree.h>
#include <dynamicArr.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <util.h>
#include <word_arrays.h>

void test1() {
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
    getAutoComplete(tree->root, "p", &arr, 0);

    printTree(tree->root, 0);

    for (size_t i = 0; i < arr.count; i++) {
        print(arr.items[i]);
    }
}

void test2() {
    clock_t startTime   = clock();
    Tree  **dictionary  = loadDictionary();
    double  elapsedTime = getElapsedTime(startTime);

    printf("Dicionário carregado com sucesso!\n");
    printf("Tempo de carregamento: %.6f segundos\n", elapsedTime);

    DynamicArrChar arr = {0};
    startTime          = clock();
    getAutoComplete(dictionary[Q_VALUE]->root, "a", &arr, 0);
    elapsedTime = getElapsedTime(startTime);

    printf("Tempo de busca: %.6f segundos\n", elapsedTime);
    printf("Sugestões de auto-complete para 'a':\n");

    for (size_t i = 0; i < arr.count; i++) {
        print(arr.items[i]);
    }
}

void test3() { print("Caractere acentuado: á é í ó ú à ê ô ü ñ ç\n"); }

void test4() {
#ifdef CURL_ON
    char *buffer = malloc(1024);
    if (!buffer) {
        fprintf(stderr, "Erro de alocação de memória\n");
        return;
    }

    if (request("abelha", &buffer)) {
        parseAndDisplayDef(buffer);
    } else {
        printf("Falha na requisição ou resposta inválida\n");
    }

    free(buffer);
#endif
}

void test5() {
    Tree *tree = createTree();
    add(tree, "apple");
    add(tree, "banana");
    add(tree, "grape");
    add(tree, "orange");
    add(tree, "pear");

    printf("Before deletion:\n");
    printTree(tree->root, 0);

    delete (tree, "banana");
    printf("After deleting 'banana':\n");
    printTree(tree->root, 0);

    delete (tree, "orange");
    printf("After deleting 'orange':\n");
    printTree(tree->root, 0);

    delete (tree, "apple");
    printf("After deleting 'apple':\n");
    printTree(tree->root, 0);

    free(tree);
}

void runTests() {
#ifdef DEBUG_ON
    test1();
    test2();
    test3();
    test4();
    test5();
#endif
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "C.UTF-8");

    processInputAndExecute(argc, argv);

    // Descomente para rodar testes no modo debug
    // runTests();

    return 0;
}