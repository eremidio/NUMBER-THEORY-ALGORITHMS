//VAMOS ESCREVER UM PROGRAMA SIMPLES QUE QUE CALCULA O MMC DE DOIS NÚMEROS INTEIROS
/*
COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o lowest_common_multiple lowest_common_multiple.c
*/

/*CABEÇALHO*/
#include<stdio.h>
#include<stdlib.h>


//FUNÇÃO PRINCIPAL
int main(){
//DEFINIÇÃO DE VARIÁVEIS
long long int value1, value2, residue1, residue2, start_value1, start_value2, factor_number, counter, control, lcm;
long long int * factor_array=NULL;

//EXPLICAÇÃO DO ALGORITMO
printf("Este programa computa o mínimo múltiplo comum (MMC) de dois números inteiros.\nUm teorema em teoria de números grante que inteiros possuem uma decomposição em fatores primos.\nDados dois inteiros A e B e os respectivos conjuntos de fatores primos destes números A_p e B_p,\no MMC destes números corresponte ao produto de todos os fatores primos no conjunto (A_p)U(B_p).\n\n");

//ENTRADA DE DADOS
printf("Digite um número inteiro:\n");
scanf("%lld", &value1);
printf("Digite um número inteiro:\n");
scanf("%lld", &value2);

//AJUSTE DE VARIÁVEIS
start_value1=value1;
start_value2=value2;
counter=0; //NÚMERO DE FATORES PRIMOS EM (A_p)U(B_p)
control=2; //VARIÁVEL PARA ITERAÇÃO E TESTE DE FATORES PRIMOS
lcm=1;


//FATORANDO OS NÚMEROS E CRIANDO UM ARRAY DE FATORES COMUNS
do{
//CÁLCULO DOS RESÍDUOS DA DIVISÃO
residue1=value1%control;
residue2=value2%control;

//COMPUTANDO OS FATORES PRIMOS DO PRIMEIRO NÚMERO
if(residue1==0){
counter++;
value1=value1/control;
factor_array=(long long int*)realloc(factor_array, counter*sizeof(long long int));
factor_array[counter-1]=control;

//AJUSTANDO O VALOR DO SEGUNDO NÚMERO CASO TENHA ALGUM FATOR COMUM COM O PRIMEIRO NÚMERO
if(residue2==0){
value2=value2/control;
continue; //CASO AFIRMATIVO TESTAR NOVAMENTE SE HÁ MAIS FATORES PRIMOS IGUAIS (NÃO PROSSEGUIR COM O LOOP)
               };

//REINICIANDO O LOOP CASO O SEGUNDO NÚMERO NÃO FATORES PRIMOS COM O PRIMEIRO
continue;
               };

//COMPUTANDO OS FATORES PRIMOS EXCLUSIVOS DO SEGUNDO NÚMERO
if(residue1!=0 && residue2==0){
counter++;
value2=value2/control;
factor_array=(long long int*)realloc(factor_array, counter*sizeof(long long int));
factor_array[counter-1]=control;
continue;
               };
//CASO NÃO HAJA MAIS FATORES PRIMOS A VARIÁVEL DE TESTE É ATUALIZADA
if(residue1!=0 || residue2!=0)
control++;

  }while(value1+value2>2);

//CALCULANDO O MMC E EXIBINDO O RESULTADO NA TELA
printf("\nLista de fatores primos: ");

for(; counter>0; counter--){
lcm=lcm*factor_array[counter-1];
printf("%lld, ", factor_array[counter-1]);
                           };
printf("...\n\n");


printf("O MMC de %lld e %lld é %lld.\n", start_value1, start_value2, lcm);

//LIMPANDO O CACHÊ DE MEMORIA E ENCERRANDO O PROGRAMA
free(factor_array);
return 0;


          }; 
