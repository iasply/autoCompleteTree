#ifdef CURL_ON
#include <cjson/cJSON.h>
#include <curl/curl.h>
#endif
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>

const char *API_URL     = "https://api.dicionario-aberto.net/word/";
const char *DISPLAY_URL = "api.dicionario-aberto.net";

size_t write_callback(void *ptr, size_t size, size_t nmemb, char **buffer) {
    size_t total_size = size * nmemb;
    printDebug("Callback: recebendo %zu bytes", total_size);

    *buffer = realloc(*buffer, total_size + 1);
    if (*buffer == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o buffer\n");
        return 0;
    }

    memcpy(*buffer, ptr, total_size);
    (*buffer)[total_size] = '\0';
    printDebug("Buffer atualizado: %s", *buffer);

    return total_size;
}

int request(char *word, char **buffer) {
#ifdef CURL_ON
    CURL    *curl;
    CURLcode res;
    char     url[256];

    snprintf(url, sizeof(url), "%s%s", API_URL, word);
    printDebug("URL formatada: %s", url);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (!curl) {
        fprintf(stderr, "Erro ao inicializar o curl\n");
        return 0;
    }

#ifdef DEBUG_ON
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);

    printDebug("Enviando requisição para a API...");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Erro na requisição: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return 0;
    }

    printDebug("Requisição concluída com sucesso");

    curl_easy_cleanup(curl);
    curl_global_cleanup();
#endif
    return 1;
}

void parseAndDisplayDef(const char *jsonData) {
#ifdef CURL_ON
    printDebug("Recebendo JSON para parse: %s", jsonData);

    cJSON *json = cJSON_Parse(jsonData);
    if (json == NULL) {
        fprintf(stderr, "Erro ao parsear o JSON\n");
        return;
    }

    cJSON *entry = cJSON_GetArrayItem(json, 0);
    if (entry == NULL) {
        fprintf(stderr, "Nenhuma descrição encontrada em %s\n", DISPLAY_URL);
        cJSON_Delete(json);
        return;
    }

    printDebug("Entrada JSON encontrada");

    cJSON *xmlItem = cJSON_GetObjectItem(entry, "xml");
    if (xmlItem == NULL) {
        fprintf(stderr, "Campo 'xml' não encontrado no JSON\n");
        cJSON_Delete(json);
        return;
    }

    const char *xmlData = cJSON_GetStringValue(xmlItem);
    if (!xmlData) {
        fprintf(stderr, "Erro ao obter string XML\n");
        cJSON_Delete(json);
        return;
    }

    printDebug("XML extraído: %s", xmlData);

    const char *start = xmlData;
    while ((start = strstr(start, "<def>")) != NULL) {
        start += 5;
        const char *end = strstr(start, "</def>");
        if (end == NULL) break;

        char   definition[512];
        size_t length = end - start;
        if (length >= sizeof(definition)) length = sizeof(definition) - 1;

        strncpy(definition, start, length);
        definition[length] = '\0';

        printf("Definição: %s\n", definition);
        start = end + 6;
    }

    cJSON_Delete(json);
#endif
}