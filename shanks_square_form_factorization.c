//VAMOS CRIAR UM PROGRAMA QUE EMPREGA O ALGORITMO DE FORMAS QUADRÁTICAS DE SHANK PARA FATORAR NÚMEROS INTEIROS
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o shanks_square_form_factorization shanks_square_form_factorization.c -lm -O2

/*
O ALGORITMO DE SHANKS É UM APRIMORAMENTO DO TESTE DE FERMAT PARA FATORAR NÚMEROS INTEIROS E USA O FATOR DE SE FOREM ENCONTRADOS
a E b SATISFAZENDO a²=b² (mod n), COM n SENDO O NÚMERO A SER FATORADO ENTÃO POSSÍVEIS FATORES NÃO TRIVIAIS TEM A SEGUINTE FORMA
mdc(a+b, n) OU mdc(|a-b|, n). 

ESTE ALGORITMO NÃO FUNCIONA PARA NÚMEROS DA FORMA n=p^k, COM p PRIMO E k INTEIRO POSITIVO.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Shanks%27s_square_forms_factorization

*/ 

//***************************************************************************************************************************
//CABEÇALHO
#include"prime_power_detection.h"
#include<stdio.h>


//VARIÁVEIS GLOBAIS
const int64_t multiplicatives[]={1, 3, 5, 7, 11, 15, 21, 35, 55, 77, 105, 165, 231, 385, 1155};
int multiplicatives_size=sizeof(multiplicatives)/sizeof(multiplicatives[0]);

//***************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool perfect_square_checker(int64_t);
int64_t gcd(int64_t, int64_t);
void shanks_square_form_factorization(int64_t);

//***************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides
int64_t gcd(int64_t a, int64_t b){

  if(b==0)
    return a;
  else
    return gcd(b, a%b);

};



//Função que implementa o algoritmo de formas quadráticas de Shanks
void shanks_square_form_factorization(int64_t n){

  //Caso base : n é primo
  if(baillie_psw_test(n)==true){
    printf("%li é primo\n", n);
    return;
  }

  //Caso base: n é um quadrado perfeito
  int64_t sqrt_n;

  if(fast_square_detection(n, &sqrt_n)){
    printf("%li é um quadrado perfeito\n", n);
    return;
  }

  //Definindo um fator multiplicativo
  rerun:
  int k_index=0;
  if(k_index==multiplicatives_size){
    printf("O algoritmo não foi capaz de fatorar o número em questão!\n");
  };

  int64_t k=multiplicatives[k_index];



  //Variáveis locais
  int64_t factor1=0, factor2=0, root;
  int64_t i;//Variável de iteração
  int64_t b0, b, p0, p1, p2, q0, q1, q2;//Variáveis usadas nos loops


  //Procedimentos

    

    //Ajustando variáveis para o loop 
    i=0;
    p0=floor(sqrt(k*n));
    p1=p0;
    q0=1;
    q1=(k*n-(p0*p0));


    //Loop1
    while(fast_square_detection(q1, &root)==false){
      ++i;
      if(n>1000000 && i>sqrt(n)) break;

      //Cálculo das variáveis
      b=floor((p0+p1)/q1);
      p2=(b*q1)-p1;
      q2=q0 +(b*(p1-p2));


      //Atualizando variáveis para a proxima iteração
      q0=q1;
      q1=q2;
      p1=p2;

    };



    //Reajuste de variáveis para o loop retrógado
    b0=floor((p0-p1)/sqrt(q2));
    p0=b0*sqrt(q2)+p2;
    p1=p0;
    q0=sqrt(q2);
    q1=((k*n)-(p0*p0))/q0;
    i=0;


    //Loop retógrado
    do{
      ++i;
      if(n>1000000 && i>sqrt_n) break;

      b=floor((p0+p1)/q1);
      p2=b*q1-p1;
      q2= q0+(b*(p1-p2));


      //Fim do loop retrogrado
      if(p1==p2) break;

      //Atualizando variáveis para a proxima iteração
      q0=q1;
      q1=q2;
      p1=p2;
    }while(true);

    //Calculando os fatores primos
    factor1=gcd(p1, n);

    if(factor1>1 && factor1<n){
      factor2=n/factor1;
      printf("Fatores encontrados: %li e %li\n", factor1, factor2);
    }
    else{
      factor1=0;
      k_index++;
      goto rerun;
    };

};

//***************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){

  //Variáveis locais
  int64_t number;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro a ser fatorado: ");
    if(scanf("%li", &number)!=1) return 0;

    //Fatorando o número em questão
    shanks_square_form_factorization(number);

  //Finalizando a aplicação
  return 0;


}
