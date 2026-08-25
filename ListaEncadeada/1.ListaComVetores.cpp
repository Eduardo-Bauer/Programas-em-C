#include <stdio.h>

/*
Você vai receber cartas de um baralho,  e deve pegar uma a uma e ir colocando lado a lado (ou na sua mão),
em ordem de valores numéricos, do menor para o maior (a carta "ás" (A ou 1) é o menor valor. 
Os naipes podem ou não ser considerados.
 
TAD jogo{
Dados: cartas
Operações:
    recebe_carta(E: carta);
    ver_lista_cartas(S: lista de cartas);
    remover_carta(E: carta; S: lista de cartas);
}
Tarefa:

Considere a implementação das cartas recebidas em um jogo como um vetor (máximo de 20 posições). 
Fazer um menu de operações, para o usuário selecionar:

    - implementar a operação de recebe_carta(...), na qual é realizada a inserção de um valor
        de forma ordenada no vetor (não utilize um método de ordenação, 
        cada inserção deve ser feita na sua posição considerando a ordem). 
        A ordenação deve ser em ordem crescente de valores, ou seja, a cada inserção de uma nova carta, 
        ela deve ser colocada na sua posição correta na lista. Pode haver valores repetidos na lista, 
        cada baralho tem 4 cartas de mesmo valor (cada valor pode ser repetido no máximo 4 vezes. 
        O valor das cartas deve estar entre 1 e 13.

Deve ser controlado o número de cartas inserido, para não ultrapassar 20 (se ultrapassar, mostrar mensagem de erro). 

 - implementar a operação ver_lista_cartas(...), que exiba a lista de cartas armazenada.
 - implementar a operação remover_carta(...), que remove a carta do valor informado. 
*/


void tratarErros(int erro){
    switch(erro){
    case 0:
        printf("voce ja tem 4 dessa carta\n");
        break;

    case 1:
        printf("voce ja recebeu 20 cartas\n");
        break;

    case 2:
        printf("voce nao tem essa carta ainda para retirar\n");
        break;

    case 3:
        printf("voce nao tem nenhuma carta\n");
        break;

    case 4:
        printf("numero da carta nao identificado\n");
        break;
    }
}

void receberCarta(int *listaCartas, int i){
    if(i > 0 && listaCartas[i] < listaCartas[i - 1]){
        int aux;
        aux = listaCartas[i];
        listaCartas[i] = listaCartas[i - 1];
        listaCartas[i - 1] = aux;
        receberCarta(listaCartas, i - 1);
    }
}

void moverCatas(int *listaCartas, int ListaTamanho, int i){
    if(i < ListaTamanho){
        listaCartas[i] = listaCartas[i + 1];
        moverCatas(listaCartas, ListaTamanho, i + 1);
    }
}

void removerCarta(int carta, int *listaCartas, int listaTamanho, int i){
    if(carta != listaCartas[i]){
        removerCarta(carta, listaCartas, listaTamanho, i + 1);
    }else{
        moverCatas(listaCartas, listaTamanho, i);
    }
}

void verListaCartas(int *listaCartas, int listaTamanho, int i){
    if(i < listaTamanho){
        printf("%d ", listaCartas[i]);
        verListaCartas(listaCartas, listaTamanho, i + 1);
    }else{
        printf("\n");
    }
}

int main(){
    int opcao = 1;
    int tamanho = 0;
    int carta;
    int cartasRecebidas[13] = {0};
    int cartas[20];

    while(opcao != 0){
        printf("\n----Bem vindo----\n");
        printf("O que voce gostaria de fazer?\n");
        printf("1 - receber uma nova carta\n");
        printf("2 - remover uma carta\n");
        printf("3 - ver suas cartas\n");
        printf("0 - sair do programa\n");
        printf("Opcao selecionada: ");
        scanf("%d", &opcao);

        switch(opcao){
        case 1:
            if(tamanho == 20){
                tratarErros(1);
                break;
            }

            printf("Qual a carta que voce recebeu?: ");
            scanf("%d", &carta);

            if(carta < 1 || carta > 13){
                tratarErros(4);
                break;
            }

            if(cartasRecebidas[carta - 1] == 4){
                tratarErros(0);
                break;
            }

            cartas[tamanho++] = carta;
            receberCarta(cartas, tamanho - 1);
            cartasRecebidas[carta - 1]++;
            printf("carta recebida com sucesso!\n");
            break;

        case 2:
            if(tamanho == 0){
                tratarErros(3);
                break;
            }

            printf("Qual a carta que voce quer remover?: ");
            scanf("%d", &carta);

            if(carta < 1 || carta > 13){
                tratarErros(4);
                break;
            }

            if(cartasRecebidas[carta - 1] == 0){
                tratarErros(2);
                break;
            }

            removerCarta(carta, cartas, tamanho, 0);
            cartasRecebidas[carta - 1]--;
            tamanho--;
            printf("carta removida com sucesso!\n");
            break;

        case 3:
            if(tamanho == 0){
                tratarErros(3);
                break;
            }

            printf("----------------------Suas cartas----------------------\n");
            verListaCartas(cartas, tamanho, 0);
            break;

        case 0:
            printf("---------------------\nPrograma finalizado!\n---------------------\n");
            return 0;

        default:
            printf("---------------------\nOpcao nao encontrada\n---------------------\n");
            break;
        }
    }
}