#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
Implementar uma tabela hash (por endereçamento aberto - as listas encadeadas armazenam as colisões) 
para incluir nomes de cidades brasileiras:

- defina o tamanho da tabela a partir de algum critério que faça sentido (!)

- defina uma função hashpara transformar o nome da cidade (que é a chave) em um endereço da tabela

- insira pelo menos uns 50 nomes de cidades na tabela hash, e depois pesquise alguns nomes.
*/

typedef struct lista{
    char cidade[50];
    struct lista *prox;
}LISTA;

void inicializarTabela(LISTA **cidades){
    int i;
    for(i = 0; i < 26; i++){
        cidades[i] = NULL;
    }
}

int hash(const char *cidade){
    int alfabeto = tolower(cidade[0]) - 'a';
    return alfabeto % 26;
}

void inserirCidade(const char *cidade, LISTA **cidades){
    int pos = hash(cidade);
    LISTA *novo = (LISTA *)malloc(sizeof(LISTA));
    strcpy(novo->cidade, cidade);
    novo->prox = NULL;

    if(cidades[pos] == NULL){
        cidades[pos] = novo;
        return;
    }

    novo->prox = cidades[pos];
    cidades[pos] = novo;
}

int conferirCidade(const char *cidade, LISTA **cidades){
    int pos = hash(cidade);
    LISTA *aux = cidades[pos];

    while(aux != NULL && strcmp(aux->cidade, cidade) != 0){
        aux = aux->prox;
    }

    if(aux != NULL){
        return pos;
    }

    return -1;
}

int main(){
    int i;

    const char *cidadesInserir[50] = {
        "São Paulo", "Rio de Janeiro", "Salvador", "Brasília", "Fortaleza",
        "Belo Horizonte", "Manaus", "Curitiba", "Recife", "Goiânia",
        "Belém", "Porto Alegre", "Guarulhos", "Campinas", "São Luís",
        "São Gonçalo", "Maceió", "Duque de Caxias", "Natal", "Teresina",
        "Campo Grande", "Nova Iguaçu", "João Pessoa", "São Bernardo do Campo",
        "Santo André", "Osasco", "Jaboatão dos Guararapes", "Ribeirão Preto",
        "Uberlândia", "Contagem", "Aracaju", "Feira de Santana", "Sorocaba",
        "Joinville", "Cuiabá", "Juiz de Fora", "Londrina", "Aparecida de Goiânia",
        "Porto Velho", "Niterói", "Ananindeua", "Campos dos Goytacazes",
        "Florianópolis", "Mauá", "São José dos Campos", "Vila Velha",
        "Serra", "Betim", "Caxias do Sul", "Diadema"
    };

    const char *cidadesConferir[6]  = {
        "Curitiba",
        "São Paulo",
        "Florianópolis",
        "Paris",
        "Nova Petrópolis",
        "Salvador"
    };
    LISTA *cidades[26];

    inicializarTabela(cidades);

    for(i = 0; i < 50; i++){
        inserirCidade(cidadesInserir[i], cidades);
    }

    for(i = 0; i < 6; i++){
        int pos = conferirCidade(cidadesConferir[i], cidades);

        if(pos != -1){
            printf("cidade %s encontrada em %d\n", cidadesConferir[i], pos);

        }else{
            printf("cidade %s não encontrada\n", cidadesConferir[i]);
        }
    }
}
