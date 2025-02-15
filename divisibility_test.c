//VAMOS CRIAR UM PROGRAMA PARA TESTAR ALGUMAS ROTINAS DISPONÍVEIS NO ARQUIVO divisibility.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o divisibility_test divisibility_test.c -lm



//Cabeçalho
#include<stdio.h>
#include"divisibility.h"


//Função principal
int main(){

  //Variáveis locais
  uint64_t number;
  int digit, start, end;

  //Procedimentos
    //Recebendo input do usuário
    printf("Usuário digite um número: ");
    scanf("%li", &number);

    printf("Usuário selecione um dígito deste número: ");
    scanf("%d", &digit);

    printf("Usuário selecione um intervalo de dígitos deste número: ");
    scanf("%d %d", &start, &end);

  //Testes
    //Testando função de con tagem de dígitos
    printf("Números de dígitos: %d\n", digits_counter (number));

    //Testando o valor posicional de um dígito
    printf("Valor posicional do %d-ésimo dígito do número %li é %li\n", digit, number, positional_value(number, digit));


    //Testando a extração de dígitos para outro inteiro
    printf("Os dígitos da posição %d-%d formam o número %li\n", start, end, extract_digits_interval(number, start, end));
    printf("Os primeiros 3 dígitos de %li formam o número %li\n", number, extract_first_digits(number, 3));
    printf("Os últimos 3 dígitos de %li posição formam o número %li\n", number, extract_last_digits(number, 3));
    printf("Os últimos 3 dígitos de %li posição formam o número %li\n", number, extract_last_digits(number, 3));
    printf("O primeiro dígito de %li é %li\n", number, extract_first_digits(number, 1));
    printf("O último dígito de %li é %li\n", number, extract_last_digits(number, 1));

  //Encerrando a aplicação
  return 0;

}

