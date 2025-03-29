#include <autoCompleteTree.h>
#include <dictionary.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <util.h>

bool splitArg(const char *arg, const char delimiter, char **buffer) {
    if (arg == NULL) {
        return false;
    }

    const char *temp  = arg;
    size_t      start = 0;
    size_t      end   = 0;

    while (temp[start] != '\0' && temp[start] != delimiter) {
        start++;
    }

    if (temp[start] == '\0') {
        return false;
    }

    end = start + 1;
    while (temp[end] != '\0') {
        end++;
    }

    size_t length = end - (start + 1);
    char  *str    = (char *)calloc(length + 1, sizeof(char));

    if (!str) {
        return false;
    }

    memcpy(str, arg + start + 1, length);
    str[length] = '\0';

    *buffer = str;
    return true;
}

void toStringArgs(Args *args) {
    printDebug("==== Argumentos ====");

    printDebug("Search String: %s",
               args->searchString ? args->searchString : "NULL");
    printDebug("Max Fetch: %zu", args->maxFetch);

    printDebug("Flags:");
    printDebug(" - isSearch: %s", args->isSearch ? "true" : "false");
    printDebug(" - isFetch: %s", args->isFetch ? "true" : "false");

#ifdef CURL_ON
    printDebug(" - isRequestFirst: %s",
               args->isRequestFirst ? "true" : "false");
    printDebug(" - isRequestTarget: %s",
               args->isRequestTarget ? "true" : "false");

#endif
    printDebug("====================");
}

void printHelp() {
    print("Manual:");
    print("-----");
    printf("%s<PREFIXO>\n", ARG_SEARCH);
    print(
        "Prefixo usado na busca para retornar uma lista de palavras que mais "
        "se assemelha.");
    print("-----");
    printf("%s<NUMERO INTEIRO>\n", ARG_FETCH);
    print(
        "Valor inteiro usado para delimitar a quantidade máxima de valores a "
        "serem retornados.");
    print("Caso não utilizado irá retornar todas as palavras semelhantes.");

#ifdef CURL_ON
    print("-----");
    printf("%s\n", ARG_REQUEST_FIRST);
    print(
        "Utiliza a API do api.dicionario-aberto.net para buscar o significado "
        "da primeira palavra mais semelhante.");
    print("-----");
    printf("%s<PALAVRA>\n", ARG_REQUEST_TARGET);
    print(
        "Utiliza a API do api.dicionario-aberto.net para buscar o "
        "significado.");
#endif
}

void parse(Args *args, char *argv) {
    if (strstr(argv, ARG_HELP)) {
        printHelp();
        exit(0);
    }

    if (strstr(argv, ARG_SEARCH)) {
        char *buffer = NULL;

        if (splitArg(argv, ARG_DELIMITER, &buffer) && buffer) {
            args->searchString = buffer;
            args->isSearch     = true;
        } else {
            printf("Parametro %s invalido", ARG_SEARCH);
            exit(0);
        }
    }

    if (strstr(argv, ARG_FETCH)) {
        char *buffer = NULL;

        if (splitArg(argv, ARG_DELIMITER, &buffer) && buffer) {
            int num;

            if (!stringToInt(buffer, &num)) {
                printf("Erro no parametro %s , valor invalido", ARG_FETCH);
                exit(0);
            }
            if (num > 0) {
                args->maxFetch = num;
                args->isFetch  = true;
            } else {
                args->maxFetch = num;
                args->isFetch  = true;
            }

        } else {
            printf("Parametro %s invalido", ARG_FETCH);
            exit(0);
        }
    }

#ifdef CURL_ON
    if (strstr(argv, ARG_REQUEST_FIRST) != NULL
        && strstr(argv, ARG_REQUEST_TARGET) == NULL) {
        args->isRequestFirst = true;
    }

    if (strstr(argv, ARG_REQUEST_TARGET) != NULL) {
        char *buffer = NULL;

        if (splitArg(argv, ARG_DELIMITER, &buffer) && buffer) {
            args->searchString    = buffer;
            args->isRequestTarget = true;
        } else {
            printf("Parametro %s invalido", ARG_REQUEST_TARGET);
            exit(0);
        }
    }

    if (args->isSearch && args->isRequestTarget) {
        printf("Parametro %s e %s são incompativeis", ARG_REQUEST_TARGET,
               ARG_SEARCH);
        exit(0);
    }
    if (args->isRequestFirst && args->isRequestTarget) {
        printf("Parametro %s e %s são incompativeis", ARG_REQUEST_TARGET,
               ARG_REQUEST_FIRST);
        exit(0);
    }
#endif
}

void processArguments(Args *argList, int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        parse(argList, argv[i]);
    }
}

void processInputAndExecute(int argc, char *argv[]) {
    if (argc <= 1) {
        printHelp();
        exit(0);
    }

    Args argList = {0};
    processArguments(&argList, argc, argv);

    if (argList.isSearch) {
        executeSearch(&argList);
    }

#ifdef CURL_ON
    if (argList.isRequestTarget) {
        printf("Buscando o significado de %s\n", argList.searchString);
        handleRequest(argList.searchString);
    }
#endif
}

void executeSearch(Args *argList) {
    clock_t startTime  = clock();
    Tree  **dictionary = loadDictionary();
    printDebug("Dicionário carregado com sucesso!");
    printDebug("Tempo de carregamento: %.6f segundos",
               getElapsedTime(startTime));

    Tree *letterTree = getTreeForWord(dictionary, argList->searchString);
    if (!letterTree) {
        printf("Nenhuma correspondência encontrada para '%s'\n",
               argList->searchString);
        return;
    }

    DynamicArrChar arr = {0};
    startTime          = clock();
    getAutoComplete(letterTree->root, argList->searchString, &arr,
                    argList->maxFetch);
    printDebug("Tempo de busca: %.6f segundos", getElapsedTime(startTime));

    if (arr.count == 0) {
        printf("Nenhuma palavra corresponde a '%s'\n", argList->searchString);
        return;
    }

    for (size_t i = 0; i < arr.count; i++) {
        printf("%zu - %s\n", i + 1, arr.items[i]);
    }

#ifdef CURL_ON
    if (argList->isRequestFirst && arr.count >= 1) {
        printf("Buscando as definições de %s\n", arr.items[0]);
        handleRequest(arr.items[0]);
    }
#endif
}

#ifdef CURL_ON
void handleRequest(const char *word) {
    if (!word) return;

    char *buffer = malloc(1);
    if (!buffer) {
        fprintf(stderr, "Erro de alocação de memória\n");
        return;
    }

    if (request(word, &buffer)) {
        parseAndDisplayDef(buffer);
    } else {
        print("Falha na requisição ou resposta inválida");
    }

    free(buffer);
}
#endif