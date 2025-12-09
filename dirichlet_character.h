//VAMOS CRIAR UM PROGRAMA QUE TABULA CARACTÉRES DE DIRICHLET MÓDULO POTÊNCIAS DE NÚMEROS PRIMOS

/*

CARACTÉRES DE DIRICHLET MÓDULO UM INTEIRO n DENOTADOS POR χ(m), COM m NO CONJUNTO Z/nZ É UM CONJUNTO DE FUNÇÕES χ:Z->C (TOMANDO VALORES NO
CONJUNTO DOS NÚMEROS COMPLEXOS) QUE SATISFAZEM AS SEGUINTES IDENTIDADES: χ(m)=0 SE mdc(m,n)>1, χ(pr)=χ(p)χ(r), χ(m)=χ(m+n), COM n, m, p, r
INTEIROS. DESTAS PROPRIEDADES BÁSICAS VÁRIAS OUTRAS PROPRIEDADES PODEM SER DIRETAMENTE DEMONSTRADAS COMO χ(p^r)=χ(p)^r, χ(p⁻¹)=χ(p)⁻¹,
ENTRE OUTRAS. PARA DOIS CARACTÉRES χ E χ' A RELAÇÃO χχ'(m)=χ(m)χ'(m) FAZ COM QUE O GRUPO DE CARACTÉRES MÓDULO UM INTEIRO n FORME UM GRUPO
ABELIANO FINITO.

SEJA q=p^k UM INTEIRO QUE É POTÊNCIA DE UM PRIMO p, E ω UMA RAÍZ DA UNIDADE DE ORDEM φ(q) (φ DENOTA A FUNÇÃO TOTIENTE DE EULER) ENTÃO UM
CARACTÉRE MÓDULO q PODE SER DEFINIDO PELA EXPRESSÃO χ(q, r; m) = ω^{ν(q, r)ν(q, m)), ONDE ν(q, m) DENOTA O INDEX DE m COM RESPEITO A q,
ISTO É, O LOGARITMO DISCRETO DE q NA BASE g(q), ONDE g(q) É UM GERADOR (RAÍZ PRIMITIVA) DE Z/qZ. PARA N=q(1)q(2)..q(N) COMPOSTO (CADA q(1)
DENOTANDO UMA POTÊNCIA DE UM PRIMO) χ(n, r; m) PODE SER DECOMPOSTO EM UM PRODUTO DIRETO DE VÁRIOS CARACTÉRES DE DIRICHLET MÓDULO POTÊNCIAS
DE PRIMOS DIVIDINDO n, COMPUTADOS USANDO-SE O TEOREMA DE RESTO CHINÊS. 

CARACTÉRES DE DIRICHLET SATISFAZEM RELAÇÕES DE ORTOGONALIDADE NO SENTIDO EM QUE PARA q POTÊNCIA DE PRIMO, A SOMA DE CARACTÉRES PARA CERTOS
ELEMENTOS a EM Z/qZ SATISFAZENDO CERTAS RELAÇÕES DE CONGRUÊNCIA IGUALA φ(q). SE PARA DOIS ELEMENTOS DISTINTOS m, n SATISFAZENDO m=n (mod d)
χ(q, r; m)=χ(q, r; n), ENTÃO χ É DITO TER QUASIPERÍODO d, O MENOR QUASIPERÍODO DE χ É DENOMINADO O CONDUTOR DE χ. SE q É IGUAL AO CONDUTOR
DE χ ENTÃO χ É DITO SER PRIMITIVO. CARACTÉRES NÃO PRIMITIVOS SÃO DITOS SEREM INDUZIDOS POR CARACTÉRES DE MENORES MÓDULOS MENORES. A ORDEM
DE χ É DEFINIDA COMO O MENOR INTEIRO k TAL QUE PARA TODOS ELEMENTOS m EM Z/qZ [χ(q, r; m)]^k=1. O VALOR DE χ(q, r; -1) DEFINE A PARIDADE 
DE χ.

CASOS PARTICULARES DE GRANDE INTERESSE SÃO OS CARACTÉRES χ(q, r; m) REAIS QUE SÃO OS SÍMBOLOS DE KRONECKER E O CARACTÉRE TRIVIAL χ(q, 0; m)
QUE É DEFINIDO PELA IDENTIDADE χ(q, 0; m)=1 SE mdc(q, m)=1 E χ(q, 0; m)=0 SE mdc(q, m)>1.

CARACTÉRES DE DIRICHLET APARACEM EM VÁRIAS SOMAS DE INTERESSE EM TEORIA DE NÚMEROS ANÁLITICA COMO SOMAS DE GAUSS E DE JACOBI
(GENERALIZADAS), SOMAS DE KLOOSTERMAN, NA TEORIA DE SÉRIES L, NA TEORIA DE FORMAS E FUNÇÕES MODULARES, ENTRE OUTROS. TAIS CONSTRUÇÕES SÃO
EXTREMAMENTE ÚTEIS EM CONTEXTOS COMPUTACIONAIS COMO NO TESTE DE PRIMALIDADE APR-CL.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Dirichlet_character#Applications
                          https://reference.wolfram.com/language/ref/DirichletCharacter.html
                          https://mathworld.wolfram.com/NumberTheoreticCharacter.html


*/



//******************************************************************************************************************************************************
//CABEÇALHO
#ifndef DIRICHLET_CHARACTER_H
#define DIRICHLET_CHARACTER_H
#include"least_primitive_root.h"
#include"euler_totient_function.h"
#include"prime_power_detection.h"
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>
#include<complex.h>


//******************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t find_index(int64_t, int64_t, int64_t);
void tabulate_dirichlet_character_modulo_two_power(int64_t);
void tabulate_dirichlet_character_modulo_prime_power(int64_t, int64_t);


//******************************************************************************************************************************************************
//ESTRUTURAS USADAS NO ALGORITMO
struct int_index_pair{
  int64_t a;
  int64_t va;

};


//******************************************************************************************************************************************************
//FUNÇÕES
//Função que computa o logaritmo discreto (valuação p-ádica) de um inteiro n em Z/pZ
int64_t find_index(int64_t base, int64_t m, int64_t ord){

  //Variáveis locais
  int64_t result=0;

  //Procedimentos 
    //Loop principal
    for(result=0; result<ord; ++result){
      if(mod_bin_pow(base, result, ord)==m) return result;
    }

  //Resultado (caso de falha)
  return 0;

};


//Função que computa caractéres de Dirchlet módulo potência de 2
void tabulate_dirichlet_character_modulo_two_power(int64_t power){

  //Variáveis locais
  int64_t prime_power = bin_pow(2, power);
  int64_t root_order  = euler_totient_function(prime_power);
  int64_t primitive_root = 5; //Gerador da parte cíclica
  int64_t cycle_size = bin_pow(2, power - 2); //Ordem de g=5 igual 2^(power-2)

  struct int_index_pair* index_array  = (struct int_index_pair*) malloc(root_order * sizeof(struct int_index_pair));
  struct int_index_pair* index_array0 = (struct int_index_pair*) malloc(root_order * sizeof(struct int_index_pair));


  //Procedimentos
    //----Definição dos argumentos usados na construção da tabela----
    printf("Parâmetros para construção de caractéres de Dirichlet módulo %li\n\n", prime_power);
    printf("Ordem [módulo]:%li\n", prime_power);
    printf("g=%li\n", primitive_root);

    //Preenchendo arrays com unidades mod 2^k
    int64_t k = 0;
    for(int64_t a = 1; a < prime_power; a += 2){
      index_array[k].a  = a;
      index_array0[k].a = a;

      //----Componente ν0(a): detecta a paridade----
        index_array0[k].va = (a % 4 == 3 ? 1 : 0);

      //----Removendo a componente (-1)^ν0(a)----
      int64_t normalized = a;
      if(index_array0[k].va == 1)
        normalized = (prime_power - a);

      //----Calculando ν(a): log discreto base 5----
      int64_t cur = 1;
      int64_t s = 0;
      for(s = 0; s < cycle_size; s++){
        if(cur == normalized) break;
        cur = (cur * primitive_root) % prime_power;
      }

      index_array[k].va = s;  // ν1(a)
      k++;
    }

  
    for(k=0; k<root_order; ++k)
      printf("a:%li -->ν(a):%li; ", index_array[k].a, index_array[k].va);
    printf("\n");

    for(k=0; k<root_order; ++k)
      printf("a:%li -->ν0(a):%li; ", index_array0[k].a, index_array0[k].va);
    printf("\n");

    //----Definição dos argumentos usados na construção da tabela----
    printf("[Unidade imáginária] ω=i=e^iπ/2\n\n");

    //----Tabela de caractéres de Dirichlet----
    for(int64_t a = 0; a < root_order; ++a){
      for(int64_t r = 0; r < root_order; ++r){

        int64_t xi_power = (index_array[a].va * index_array[r].va) % cycle_size;//ν(a)*ν1(r) dá o expoente cíclico
        int64_t xi_power0 = (index_array0[a].va * index_array0[r].va);        //ν0(a)*ν0(r) dá o sinal

        printf("χ(%li, %li;%li)=", prime_power, index_array[r].a, index_array[a].a);
        if(xi_power0 & 1) printf("-");
        printf("ω^%li ", xi_power);
      }
      printf("\n");
    }

    printf("\n");

    //Limpando o cachê de memória
    if(index_array) free(index_array); index_array=NULL;
    if(index_array0) free(index_array0); index_array0=NULL;

};


//Função que computa caractéres de Dirchlet módulo potência de um primo
void tabulate_dirichlet_character_modulo_prime_power(int64_t prime, int64_t power){

  //Caso base: potÊncias de 2 superiores a 4
  if(prime==2 && power>2){
    tabulate_dirichlet_character_modulo_two_power(power);
    return;
  };


  //Variáveis locais
  int64_t prime_power=bin_pow(prime, power);
  int64_t root_order=euler_totient_function(prime_power);
  int64_t minus_order_reducer = (!(root_order&1))?(root_order>>1):0;
  int64_t primitive_root=find_primitive_root(prime_power);
 
  struct int_index_pair* index_array=(struct int_index_pair*) malloc(root_order*sizeof(struct int_index_pair));


  //Procedimentos
    //----Definição dos argumentos usados na construção da tabela----
    printf("Parâmetros para construção de caractéres de Dirichlet módulo %li\n\n", prime_power);
    printf("Ordem [módulo]:%li\n",prime_power);
    printf("g=%li\n", primitive_root);

    //Preenchendo um array de logaritmos discretos: usados no cálculo
    index_array[0].a=1; index_array[0].va=0;

    int64_t k=1;
    for(int64_t i=2; i<prime_power; ++i){
      if(gcd_euclides(i, prime_power)==1){
        index_array[k].a=i;
        index_array[k].va=find_index(primitive_root, i, prime_power);
        ++k;
      }
    }


    for(k=0; k<root_order; ++k)
      printf("a:%li -->ν(a):%li; ", index_array[k].a, index_array[k].va);
    printf("\n");
  
    //----Definição dos argumentos usados na construção da tabela----
    printf("ω=ζ(φ(%li))=e^2iπ/%li\n", prime_power, root_order);
    if((!(root_order&1)))printf("ω^%li=(-1)\n\n", minus_order_reducer);


    //----Tabela de caractéres de Dirichlet----
    for(int64_t a=0; a<root_order; ++a){
      for(int64_t r=0; r<root_order; ++r){
        int64_t xi_power=(index_array[a].va*index_array[r].va)%root_order;

        printf("χ(%li, %li;%li)=", prime_power, index_array[r].a, index_array[a].a);
        if(xi_power>=minus_order_reducer){
          xi_power-=minus_order_reducer;
          printf("-");
        }
        printf("ω^%li ", xi_power);

      }
      printf("\n");
    }
    printf("\n");
  
    //Limpando o cachê de memória
    if(index_array) free(index_array); index_array=NULL;

};


/*
  NOTA: Devido a complexidade do código não providenciei uma tabela de Caractéres módulo números compostos. Tal fato pode ser feito
        usando-se o teorema do resto chinês e os caractéres módulos potências de primos.

        Exemplo: módulo 15
                 15=3¹x5¹
                            χ(5,1)   χ(5,2)   χ(5,3)    χ(5,4)
                          -----------------------------------------
                  χ(3,1)|  χ(15,1)   χ(15,7)  χ(15,13)  χ(15,4) 
                  χ(3,2)|  χ(15,11)  χ(15,2)  χ(15,8)   χ(15,14)

                  Para obter a entrada χ(15,11) calculamos
                  x=1 (mod 5)
                  x=2 (mod 3)
                  De forma que x = 11 (mod 15)

                  Para obter a entrada χ(15,14) calculamos
                  x=4 (mod 5)
                  x=2 (mod 3)
                  De forma que x = 14 (mod 15)

                  E assim sucessivamente.

                  Para inteiros n com Ω(n)>2 a construção da tabela e o código final ficam complicados, além disso a exibição da mesma
                  em um array 2D fica mais difícil de se visualizar. Mas tais tabelas podem ser reconstruidas manualmente usando-se a
                  lógica acima e outras rotinas providas neste repositório.

*/

//******************************************************************************************************************************************************
//FIM DO HEADER
#endif
