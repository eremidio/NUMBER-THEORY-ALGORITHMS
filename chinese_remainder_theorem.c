//VAMOS CRIAR UM PROGRAMA PARA TESTAS AS ROTINAS CRIADAS NO ARQUIVO chinese_remainder_theorem.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o chinese_remainder_theorem chinese_remainder_theorem.c


//Cabeçalho
#include"chinese_remainder_theorem.h"
#include<stdio.h>

//Função principal
int main(){
//Variáveis locais
int64_t k, i;
int64_t N=1;

//Procedimentos
//Recebendo input do usuário
printf("Usuário digite o número de equações modulares: ");
scanf("%li",&k);

//Preenchendo os arrays contendo os valores de a(i) e n(i)
int64_t a[k], n[k];

for(i=0; i<k; ++i){
printf("Entre com o valor de n(%li): ", i);
scanf("%li", &n[i]);
printf("Entre com o valor de a(%li): ", i);
scanf("%li", &a[i]);
N*=n[i];//Ajuste de variável
                  }; 

for(i=0; i<k; ++i)
printf("x ≡ %li mod(%li)\n", a[i], n[i]);

//Computando valor de x e exibindo o resultado
printf("x = %li+%lik\n", chinese_remainder_theorem(a, n, k), N);

//Finalizando a palicação
return 0;
          };
