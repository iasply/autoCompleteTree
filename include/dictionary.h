#pragma once

#include <stdbool.h>
#include <stddef.h>

#define ARG_SEARCH "-s="
#define ARG_FETCH "-f="
#define ARG_HELP "-h"
#define ARG_DELIMITER '='

#ifdef CURL_ON
#define ARG_REQUEST_FIRST "-r"
#define ARG_REQUEST_TARGET "-r="
#endif

typedef struct Args {
    char  *searchString;
    size_t maxFetch;
    bool   isSearch;
    bool   isFetch;
#ifdef CURL_ON
    bool isRequestFirst;
    bool isRequestTarget;
#endif
} Args;

void processInputAndExecute(int argc, char *argv[]);
void executeSearch(Args *argList);
#ifdef CURL_ON
void handleRequest(const char *word);
#endif