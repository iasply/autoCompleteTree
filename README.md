# autoCompleteTree

Este projeto implementa um dicionário com funcionalidade de autocompletar e busca de definições utilizando a API `api.dicionario-aberto.net`. O programa pode buscar palavras semelhantes a partir de um prefixo e, opcionalmente, buscar definições online.

## Estrutura do Projeto

```
.
├── src/            # Código-fonte
├── include/        # Arquivos de cabeçalho (.h)
├── build/          # Arquivos compilados
├── Makefile        # Arquivo para compilação e automação
└── README.md       # Documentação
```

## Compilação e Execução

O projeto utiliza `make` para facilitar a compilação. Certifique-se de ter `clang` ou `gcc` instalado.

### Comandos disponíveis
```sh
make        # Compila o projeto
make run    # Executa o programa
make clean  # Remove arquivos compilados
```

## Uso

O programa aceita os seguintes argumentos:

- `-s=<PREFIXO>` : Busca palavras no dicionário que começam com o prefixo informado.
- `-f=<NUMERO>` : Define o número máximo de palavras a serem retornadas.
- `-h` : Exibe a ajuda.
- `-r` : Busca a definição da primeira palavra mais semelhante (requer `CURL_ON`).
- `-r=<PALAVRA>` : Busca a definição da palavra informada (requer `CURL_ON`).

### Exemplos de uso

Buscar palavras que começam com "auto":
```sh
./build/dic -s=auto
```

Buscar as 5 palavras mais semelhantes a "pre":
```sh
./build/dic -s=pre -f=5
```

Buscar a definição da primeira palavra mais semelhante a "casa":
```sh
./build/dic -s=casa -r
```

Buscar a definição de "amor":
```sh
./build/dic -r=amor
```

## Makefile

O `Makefile` utiliza as seguintes tags de compilação:

```make
CC := clang
CFLAGS := -Wall -Wextra -O1 -I./include -v -L/usr/lib 
```
# Explicação das Flags de Compilação

## `$DEBUG_FLAG`
- Essa flag ativa a definição da macro `DEBUG_ON` durante a compilação.
- Logs extras para depuração

## `$CURL_FLAG`
- Quando você define `CURL_ON` com esta flag, o código irá incluir funcionalidades relacionadas à biblioteca `libcurl` e à API `api.dicionario-aberto.net` para buscar definições de palavras na web.
- Com a flag `-DCURL_ON` ativada, o programa terá a capacidade de fazer requisições HTTP para a API, obter o conteúdo e processá-lo. Sem ela, essas funcionalidades serão desativadas e o programa funcionará apenas com o dicionário local.
- Para usar essa funcionalidade, é necessário ter a biblioteca `libcurl` e `libcjson` instalada no sistema.
