//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE SHANKS PARA FATORAR NÚMEROS INTEIROS DE 64 BITS

/*
USANDO IDEAIS DE GRUPOS DE CLASSES EM CORPOS ALGÉBRICOS NÚMERICOS, É POSSÍVEL FATORAR NÚMEROS INTEIROS. DE FATO SENDO f(x,y)=ax²+bxy+cy²,
UMA FORMA QUADRÁTICA (REPRESENTADO POR UMA TRIPLA f=(a, b, c)) DE DISCRIMINANTE Δ=b²-4ac, DEFINIMOS e=(1, 0, |Δ|/4) PARA -Δ PAR E
e=(1, 1, |1-Δ|/4) PARA -Δ ÍMPAR COMO A UNIDADE RELATIVA A OPERAÇÃO DE COMPOSIÇÃO DE FORMA QUADRÁTICAS. f=(a, b, c) É UMA FORMA AMBÍGUA
SE f FOR EQUIVALENTE A SUA INVERSA g=(a, -b, c) A MENOS DE UMA TRANSFORMAÇÃO LINEAR. 

PARA FORMAS AMBÍGUAS TRÊS CASOS SÃO POSSÍVEIS: [1] SE b=0, ENTÃO Δ=-4ac; [2] SE a=b, ENTÃO Δ=b(b-4c); [3] SE a=c, ENTÃO Δ=(b-2a)(b+2a).
SEJA n UM NÚMERO A SER FATORADO ENTÃO DEFINIMOS O DISCRIMINANTE FUNDAMENTAL Δ = (-n) SE n=3 (mod 4) OU Δ = (-4n) NO CASO GERAL. O
PROBLEMA DE FATORAR UM NÚMERO INTEIRO É ENTÃO REDUZIDO A COMPUTAR FORMAS AMBÍGUAS. AS FORMAS QUADRÁTICAS e LISTADAS ACIMA PRODUZEM
FATORAÇÕES TRIVIAIS.

A ORDEM DO GRUPO DE FORMAS QUADRÁTICAS É IDENTIFICADO COM O NÚMERO DE CLASSE h(-Δ) DE UM CORPO ALGÉBRICO QUADRÁTICO Q(√-Δ). NESTE PROGRAMA
USAREMOS A REGRA DE COMPOSIÇÃO DE GAUSS VÁLIDAS APENAS EM CERTOS CASOS, PORÉM FACILMENTE COMPUTÁVEL.


PARA MAIORES REFERÊNCIAS: A Course In Computational Algebraic Number Theory by Henri Cohen
                          Primes of the Form x² + ny² : Fermat, Class Field Theory, and Complex Multiplication by D. A. Cox
                          https://pages.cs.wisc.edu/~cs812-1/lec40.pdf

*/


//******************************************************************************************************************************************************************
//CABEÇALHO
#ifndef SHANKS_CLASS_GROUP_FACTORIZATION_H
#define SHANKS_CLASS_GROUP_FACTORIZATION_H
#include"quadratic_form_composition.h"
#include"binary_jacobi_symbol.h"
#include<time.h>
#include<stdio.h>


//CONSTANTES GLOBAIS
const int primes_500[168]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101,
                          103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
                          211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317,
                          331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443,
                          449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577,
                          587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701,
                          709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839,
                          853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983,
                          991, 997};


//******************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t generate_fundamental_discriminant(int64_t);
struct binary_quadratic_form generate_unit_form(int64_t); 
struct binary_quadratic_form generate_prime_form(int64_t, int);
struct binary_quadratic_form generate_random_form(int64_t);
struct binary_quadratic_form quadratic_form_exponentiation(struct binary_quadratic_form, int64_t, int64_t);
bool is_ambiguous_form(struct binary_quadratic_form*, int64_t*, int64_t*);
void shanks_class_group_factorization(int64_t, int64_t, int64_t);


//******************************************************************************************************************************************************************
//FUNÇÕES
//Função que computa um discriminante fundamental associado a um inteiro
int64_t generate_fundamental_discriminant(int64_t N){

  //Resultado
  if(N%4==3) return (-N);
  else return (-4)*N;

};


//Função que gera uma unidade no grupo cl(D) de forma quadráticas de discriminante negativo
struct binary_quadratic_form generate_unit_form(int64_t D){

  //Variáveis locais
  struct binary_quadratic_form one;

  //Procedimento
    //Calculando os coeficientes da forma quadrática unitária
    if(D%4==0){
      one.a=1; one.b=0; one.c=(-D/4);    
    }
    else{
      one.a=1; one.b=1; one.c=((1-D)/4);
    }

  //Resultado
  return one;

};


//Função que gera uma forma quadrática prima f(p)=(p, b(p), (b(p)²-D)/(4p)) soluções de b(p)²= D mod(4p)
struct binary_quadratic_form generate_prime_form(int64_t D, int prime_index){

  //Variáveis locais
  struct binary_quadratic_form prime_form={0,0,0};
  int64_t p=primes_500[prime_index], p4=(p<<2);
  int64_t bp;

  //Procedimentos
    //Checado a condição de solvalibilidade de b(p)²= D mod(4p)
    if(binary_jacobi(D, p)==(-1))
      return prime_form; //bp=0 indica falha

    //Computando raízes quadradas modulares b(p)²= D mod(4p)
    int64_t r=D%p4;
    if(r<0) r+=p4;
    bool found=false;

    for(int64_t i=0; i<p4; ++i){
      if((i*i)%p4==r){
        bp=i;
        found=true;
        break;
      }


    }

    //Checado a condição de solvalibilidade de b(p)²= D mod(4p)
    if(!found) return prime_form; //bp=0 indica falha

    //Calculando os coeficientes das formas primas
    if(bp>p) bp-=p4;
    prime_form.a=p; prime_form.b=bp;
    prime_form.c=(bp*bp-D)/p4;
    if(is_reduced(prime_form)==false) prime_form=reduce_quadratic_form(prime_form);


  //Resultado
  return prime_form;

};


//Função que gera uma forma quadrada aleatória de um determinado discriminate
struct binary_quadratic_form generate_random_form(int64_t D){

  //Semente para geração de números aleatórios
  srand(time(NULL));

  //Variáveis locais
  struct binary_quadratic_form result;
  double c;
  int64_t a, b;
  int64_t B=sqrt(D/3);

  //Procedimentos
   rerun:

    //Definindo os parâmetros a, b
    a=2+rand()%B;
    b=2+rand()%a;

    //Definindo o parâmetro c
    c=(b*b-D)/(4.0*a);

    while(b>0){
      if(floor(c)==ceil(c)) break;
      else b--;
      c=(b*b-D)/(4.0*a);
    };
    if(b==0) goto rerun;

    //Ajuste dos coeficientes da forma quadrática 
    result.a=a;
    result.b=b;
    result.c=round(c);

  
  //Resultado
  return result;

};

//Função que calcula a exponencial de uma forma quadrática binária
struct binary_quadratic_form quadratic_form_exponentiation(struct binary_quadratic_form f, int64_t D, int64_t exponent){

  //Variáveis locais
  struct binary_quadratic_form q=f;
  struct binary_quadratic_form result=generate_unit_form(D);


  //Procedimento
    //Loop sobre os bits do expoente
    while(exponent>0){

      //Checando a paridade do bit atual
      if(exponent&1) result=quadratic_form_composition(result, q);

      //Atualizando variáveis para apróxima iteração
      exponent>>=1;
      q=quadratic_form_composition(q, q);

    }


  //Resultado
  return result;

};


//Função que checa se um fator não trivial foi obtido
bool is_ambiguous_form(struct binary_quadratic_form* f, int64_t* factor1, int64_t* factor2){

  //Resultado
    //Caso 1: b==0
    if(f->b==0){
      print_binary_quadratic_form(*f); printf("\n");
      (*factor1)= f->a;
      (*factor2)= f->c;
      return true;
    }

    //Caso 2: a==b
    if(f->b==f->a){
      print_binary_quadratic_form(*f); printf("\n");
      if((f->b&1)){
        (*factor1)= f->b;
        (*factor2)= ((4*f->c)-f->b);
      }
      else{
        (*factor1)= f->b/2;
        (*factor2)= ((2*f->c) - (f->b/2));
      };     
      return true;
    }

    //Caso 3: a==c
    if(f->c==f->a){
      print_binary_quadratic_form(*f); printf("\n");
      if((f->b&1)){
        (*factor1)= ((2*f->a)-f->b);
        (*factor2)= (f->b+(2*f->a));
      }
      else{
        (*factor1)= (f->b+(2*f->a));
        (*factor2)= ((2*f->a)-f->b);
      };      
      return true;
    }

  //Em caso de falha
  return false;

};


//Algoritmo de Shanks para fatorar números inteiros usando grupos de classes de ideais em corpos algébricos quadráticos imaginários
/*
  NOTA: Outras estratégias para computar formas ambíguas podem ser adotadas. Aqui implemento a sugestão na seção 8.6 do livro
        "A Course In Computational Algebraic Number Theory" de H. Cohen.
*/
void shanks_class_group_factorization(int64_t N, int64_t D/*discriminante*/, int64_t hD/*número de classe*/){ 

  //Variáveis locais
  int64_t r=hD, s=0;
  int64_t factor1=1, factor2=1;


  //Procedimentos
    //Ajuste de variáveis
    while((r%2)==0){
      r>>=1;
      s++;
    }

    //Loop principal
      //Iterando sobre grupo cl(D) de formas quadráticas
      for(int i=1; i<168; ++i){

        //Ajuste de variáveis
        int64_t p=primes_500[i];

        //Caso base divisão por pequenos primos (esta etapa não é necessária, mas é útil em muitos casos)
        if(N%p==0){
          factor1=p;
          factor2=N/factor1;
          break;
        } 

        //Computando formas ambíguas
        struct binary_quadratic_form fp = generate_prime_form(D, i);
        if(fp.a==0 && fp.b==0 && fp.c==0) continue;//Falha em gerar formas primas

        if(is_ambiguous_form(&fp, &factor1, &factor2))
          break;

        struct binary_quadratic_form power_form = quadratic_form_exponentiation(fp, D, r);
        if(is_ambiguous_form(&power_form, &factor1, &factor2))
          goto result_analysis;


        for(int64_t j=0; j<=s; ++j){ //Computando subgrupos de Sylow de ordem 2 em cl(D)
          power_form=quadratic_form_composition(power_form, power_form);
          if(is_ambiguous_form(&power_form, &factor1, &factor2))
            goto result_analysis;
        }

      } 


    //Análise do resultado
    result_analysis:

    if(factor1==1 && factor2==1)
      printf("Algoritmo falhou\n");
    else
      printf("Fatores de %li encontrados: %li e %li\n", N, factor1, factor2);

};


//******************************************************************************************************************************************************************
//FIM DO HEADER
#endif
