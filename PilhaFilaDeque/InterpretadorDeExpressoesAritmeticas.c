#include <stdio.h>
#include <stdlib.h>

/******************************************************************************

4) Implementar o interpretador de expressões aritméticas, 
com uso de duas pilhas (pilha de operandos e pilha de operadores).
A expressão aritmética pode ser lida como um string, 
os números da expressão podem ter apenas um dígito 
(ou não, talvez dois ou mais, decida como for mais adequado). 
Pode incluir a divisão entre os operadores, 
mas não esqueça de testar o divisor para que não seja igual a zero.

*******************************************************************************/

typedef struct numbers{
    float number;
    struct numbers *next;
}NUMBERS;

typedef struct operators{
    char operator;
    struct operators *next;
}OPERATORS;

void pushNumber(NUMBERS **startNumber, float number){
    NUMBERS *new = (NUMBERS *)malloc(sizeof(NUMBERS));
    new->number = number;
    new->next = NULL;
    
    if(*startNumber == NULL){
       *startNumber = new;
       return;
    }
    
    new->next = *startNumber;
    *startNumber = new;
}

void pushOperator(OPERATORS **startOperator, char operator){
    OPERATORS *new = (OPERATORS *)malloc(sizeof(OPERATORS));
    new->operator = operator;
    new->next = NULL;
    
    if(*startOperator == NULL){
        *startOperator = new;
        return;
    }
    
    new->next = *startOperator;
    *startOperator = new;
}

float popNumber(NUMBERS **startNumber){
    float number;
    NUMBERS *aux = *startNumber;
    
    if(*startNumber != NULL){
        number = (*startNumber)->number;
        *startNumber = (*startNumber)->next;
        free(aux);
        return number;
    }
}

char popOperator(OPERATORS **startOperator){
    char operator;
    OPERATORS *aux = *startOperator;
    
    if(*startOperator != NULL){
        operator = (*startOperator)->operator;
        *startOperator = (*startOperator)->next;
        free(aux);
        return operator;
    }
}

float calculate(NUMBERS **startNumber, OPERATORS **startOperator, char *expression){
    char operator;
    int i = 0;
    float final = 0, number1, number2;
    
    for(i; expression[i] != '\0'; i++){
        if(expression[i] >= '0' && expression[i] <= '9'){
            final *= 10;
            final += (expression[i] - '0');
            continue;
        }
        
        if(expression[i] == ')'){
            number1 = popNumber(&*startNumber);
            number2 = final;
            operator = popOperator(&*startOperator);
            
            switch(operator){
                case '+':
                    final = number1 + number2;
                    break;
                
                case '-':
                    final = number1 - number2;
                    break;
                    
                case '*':
                    final = number1 * number2;
                    break;
                    
                case '/':
                    if(number2 == 0){
                        return -1;
                    }
                    final = number1 / number2;
                    break;
                
                default:
                    return -1;
            }
            continue;
        }
        
        if(expression[i] != '(' && expression[i] != ' '){
            pushNumber(&*startNumber, final);
            pushOperator(&*startOperator, expression[i]);
            final = 0;
            continue;
        }
    }
    return final;
}

int main(){
    NUMBERS *startNumber = NULL;
    OPERATORS *startOperator = NULL;
    char expression[50] = "((25 + 5) / 10)";
    
    printf("resultado = %.2f\n", calculate(&startNumber, &startOperator, expression));
    return 0;
}