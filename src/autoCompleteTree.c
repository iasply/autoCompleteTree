#include <assert.h>
#include <autoCompleteTree.h>
#include <ctype.h>
#include <dynamicArr.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>
#include <word_arrays.h>

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

void getAutoComplete(Node *node, char *prefix, DynamicArrChar *arr,
                     size_t maxFetch) {
    if (!node) {
        return;
    }
    if (arr->count >= maxFetch && maxFetch != UNLIMITED_FETCH) {
        return;
    }
    int  cmp = comp(node->str, prefix);
    bool has = isPrefix(prefix, node->str);
    if (has) {
        da_append((*arr), strdup(node->str));
    }

    if (cmp > 0 && !has) {
        getAutoComplete(node->left, prefix, arr, maxFetch);
        return;
    }
    getAutoComplete(node->left, prefix, arr, maxFetch);
    getAutoComplete(node->right, prefix, arr, maxFetch);
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

void loadTreeA(Tree *tree) {
    for (size_t i = 0; i < A_MAX_COUNT; i++) {
        add(tree, a_palavras[i]);
    }
    for (size_t i = 0; i < À_MAX_COUNT; i++) {
        add(tree, a_palavras[i]);
    }
    for (size_t i = 0; i < Á_MAX_COUNT; i++) {
        add(tree, a_palavras[i]);
    }
    for (size_t i = 0; i < Ã_MAX_COUNT; i++) {
        add(tree, a_palavras[i]);
    }
    for (size_t i = 0; i < Ã_MAX_COUNT; i++) {
        add(tree, a_palavras[i]);
    }
}

void loadTreeB(Tree *tree) {
    for (size_t i = 0; i < B_MAX_COUNT; i++) {
        add(tree, a_palavras[i]);
    }
}

void loadTreeC(Tree *tree) {
    for (size_t i = 0; i < C_MAX_COUNT; i++) {
        add(tree, a_palavras[i]);
    }
}

void loadTreeD(Tree *tree) {
    for (size_t i = 0; i < D_MAX_COUNT; i++) {
        add(tree, a_palavras[i]);
    }
}

void loadTree(Tree *tree, char **words, size_t count) {
    for (size_t i = 0; i < count; i++) {
        add(tree, words[i]);
    }
}

Tree **loadDictionary() {
    Tree **trees = (Tree **)malloc(ALPHABET_SIZE * sizeof(Tree *));

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        trees[i] = createTree();
    }

    loadTree(trees[A_VALUE], a_palavras, A_MAX_COUNT);
    loadTree(trees[A_VALUE], à_palavras, À_MAX_COUNT);
    loadTree(trees[A_VALUE], á_palavras, Á_MAX_COUNT);
    loadTree(trees[A_VALUE], â_palavras, Â_MAX_COUNT);
    loadTree(trees[A_VALUE], ã_palavras, Ã_MAX_COUNT);

    loadTree(trees[B_VALUE], b_palavras, B_MAX_COUNT);
    loadTree(trees[C_VALUE], c_palavras, C_MAX_COUNT);
    loadTree(trees[D_VALUE], d_palavras, D_MAX_COUNT);
    loadTree(trees[E_VALUE], e_palavras, E_MAX_COUNT);
    loadTree(trees[E_VALUE], é_palavras, É_MAX_COUNT);
    loadTree(trees[E_VALUE], ê_palavras, Ê_MAX_COUNT);

    loadTree(trees[F_VALUE], f_palavras, F_MAX_COUNT);
    loadTree(trees[G_VALUE], g_palavras, G_MAX_COUNT);
    loadTree(trees[H_VALUE], h_palavras, H_MAX_COUNT);
    loadTree(trees[I_VALUE], i_palavras, I_MAX_COUNT);
    loadTree(trees[I_VALUE], í_palavras, Í_MAX_COUNT);

    loadTree(trees[J_VALUE], j_palavras, J_MAX_COUNT);
    loadTree(trees[K_VALUE], k_palavras, K_MAX_COUNT);
    loadTree(trees[L_VALUE], l_palavras, L_MAX_COUNT);
    loadTree(trees[M_VALUE], m_palavras, M_MAX_COUNT);
    loadTree(trees[N_VALUE], n_palavras, N_MAX_COUNT);
    loadTree(trees[O_VALUE], o_palavras, O_MAX_COUNT);
    loadTree(trees[O_VALUE], ô_palavras, Ô_MAX_COUNT);
    loadTree(trees[O_VALUE], ó_palavras, Ó_MAX_COUNT);

    loadTree(trees[P_VALUE], p_palavras, P_MAX_COUNT);
    loadTree(trees[Q_VALUE], q_palavras, Q_MAX_COUNT);
    loadTree(trees[R_VALUE], r_palavras, R_MAX_COUNT);
    loadTree(trees[S_VALUE], s_palavras, S_MAX_COUNT);
    loadTree(trees[T_VALUE], t_palavras, T_MAX_COUNT);
    loadTree(trees[U_VALUE], u_palavras, U_MAX_COUNT);
    loadTree(trees[U_VALUE], ú_palavras, Ú_MAX_COUNT);

    loadTree(trees[V_VALUE], v_palavras, V_MAX_COUNT);
    loadTree(trees[W_VALUE], w_palavras, W_MAX_COUNT);
    loadTree(trees[X_VALUE], x_palavras, X_MAX_COUNT);
    loadTree(trees[Y_VALUE], y_palavras, Y_MAX_COUNT);
    loadTree(trees[Z_VALUE], z_palavras, Z_MAX_COUNT);

    return trees;
}

#include <ctype.h>
#include <stdio.h>
#include <string.h>

Tree *getTreeForWord(Tree **trees, const char *word) {
    if (!word || word[0] == '\0') {
        printf("Erro: Palavra inválida\n");
        return NULL;
    }

    char firstChar = tolower(
        (unsigned char)
            word[0]);  // Garante que caracteres acima de 127 não causem erro

    if (isdigit(firstChar)) {
        printf("Erro: Não é permitido iniciar com número (%c)\n", firstChar);
        return NULL;
    }

    switch (firstChar) {
        case 'a':
            return trees[A_VALUE];
        case 'b':
            return trees[B_VALUE];
        case 'c':
            return trees[C_VALUE];
        case 'd':
            return trees[D_VALUE];
        case 'e':
            return trees[E_VALUE];
        case 'f':
            return trees[F_VALUE];
        case 'g':
            return trees[G_VALUE];
        case 'h':
            return trees[H_VALUE];
        case 'i':
            return trees[I_VALUE];
        case 'j':
            return trees[J_VALUE];
        case 'k':
            return trees[K_VALUE];
        case 'l':
            return trees[L_VALUE];
        case 'm':
            return trees[M_VALUE];
        case 'n':
            return trees[N_VALUE];
        case 'o':
            return trees[O_VALUE];
        case 'p':
            return trees[P_VALUE];
        case 'q':
            return trees[Q_VALUE];
        case 'r':
            return trees[R_VALUE];
        case 's':
            return trees[S_VALUE];
        case 't':
            return trees[T_VALUE];
        case 'u':
            return trees[U_VALUE];
        case 'v':
            return trees[V_VALUE];
        case 'w':
            return trees[W_VALUE];
        case 'x':
            return trees[X_VALUE];
        case 'y':
            return trees[Y_VALUE];
        case 'z':
            return trees[Z_VALUE];
    }

    if (strncmp(word, "à", 2) == 0 || strncmp(word, "á", 2) == 0
        || strncmp(word, "â", 2) == 0 || strncmp(word, "ã", 2) == 0) {
        return trees[A_VALUE];
    }
    if (strncmp(word, "é", 2) == 0 || strncmp(word, "ê", 2) == 0) {
        return trees[E_VALUE];
    }
    if (strncmp(word, "í", 2) == 0) {
        return trees[I_VALUE];
    }
    if (strncmp(word, "ó", 2) == 0 || strncmp(word, "ô", 2) == 0) {
        return trees[O_VALUE];
    }
    if (strncmp(word, "ú", 2) == 0) {
        return trees[U_VALUE];
    }

    printf("Erro: Caractere não suportado (%c)\n", firstChar);
    return NULL;
}

Node *findMin(Node *node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

Node *deleteNode(Node *node, char *str, size_t *size) {
    if (!node) {
        return NULL;
    }

    int result = comp(node->str, str);

    if (result > 0) {
        node->left = deleteNode(node->left, str, size);
    } else if (result < 0) {
        node->right = deleteNode(node->right, str, size);
    } else {
        if (!node->left) {
            Node *temp = node->right;
            free(node->str);
            free(node);
            node->str = NULL;
            node = NULL;
            (*size)--;
            return temp;
        } else if (!node->right) {
            Node *temp = node->left;
            free(node->str);
            free(node);
            node->str = NULL;
            node = NULL;
            (*size)--;
            return temp;
        }

        Node *temp = findMin(node->right);
        free(node->str);
        node->str   = strdup(temp->str);
        node->right = deleteNode(node->right, temp->str, size);
    }
    return node;
}

void delete(Tree *tree, char *str) {
    assert(tree);
    assert(str);
    tree->root = deleteNode(tree->root, str, &tree->sizeTree);
}
