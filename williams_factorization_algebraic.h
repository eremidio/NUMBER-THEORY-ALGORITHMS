//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA VARIANTE DO ALGORITMO (p+1) DE WILLIAMS USANDO ARITMÉTICA EM CORPOS FINITOS DO SEGUNDO TIPO

/*

O ALGORITMO DE FATORAÇÃO (p+1) PODE SER REEXPRESSO EM TERMOS DE ARITMÉTICA USANDO CORPOS NÚMERICOS QUADRÁTICOS Q(√n) CUJOS ELEMENTOS
SÃO DA FORMA z=a+b√n.

ESTE ALGORITMO É PARTICULARMENTE ÚTIL PARA SEMIPRIMOS (PRODUTOS DE DOIS FATORES PRIMOS). GENERALIZAÇÕES INCLUEM A FATORAÇÃO VIA
POLINÔMIOS CICLOTÔMICOS.


PARA MAIORES INFORMAÇÕES: https://www.semanticscholar.org/paper/Factoring-with-cyclotomic-polynomials-Bach-Shallit/b47948d1d665cb8276bc638d5fca6eabd23806c7
                          https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/williams_factorization.c

*/

//******************************************************************************************************************************************************************
// CABEÇALHO
#ifndef WILLIAM_FACTORIZATION_ALGEBRAIC_H
#define WILLIAM_FACTORIZATION_ALGEBRAIC_H
#include"cipolla_algorithm.h"
#include"fast_perfect_square_detection.h"
#include<stdlib.h>
#include<time.h>


//******************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
bool* power_prime_sieve_setup(int64_t);
__int128_t modular_inverse(__int128_t, __int128_t);
void setup_williams_parameters(int64_t*, int64_t*, int64_t*, int64_t);
struct algebraic_quadratic_number algebraic_quadratic_number_rationalization(struct algebraic_quadratic_number, int64_t);
int64_t  gcd_s64(int64_t, int64_t);
void williams_factorization_algebraic(int64_t, int64_t);


//******************************************************************************************************************************************************************
//FUNÇÕES
//Função que computa uma lista de números primos usando a peneira de Eratóstenes
bool* power_prime_sieve_setup(int64_t n){

  //Variáveis locais
  bool* number_array=(bool*)malloc((n+1)*sizeof(bool));
  

  //Procedimentos
    //Inicializando o array de booleanos
    number_array[0]=false; number_array[1]=false;
    for(int64_t i=2; i<=n; ++i) number_array[i]=true;

    //Loop principal: identificando números primos
    for(int64_t i=2; (i*i)<=n; ++i){

      if(number_array[i]==false) continue;
      for(int64_t j=(i*i); j<=n; j+=i) number_array[j]=false;

    }

    //Loop principal: identificando potências de números primos
    for(int64_t i=2; (i*i)<=n; ++i){

      if(number_array[i]==false) continue;
      int64_t power_prime=i;

      while(power_prime<n){
        power_prime*=i;
        number_array[i]=true;
      }


    }
    


  //Resultado
  return number_array;  

};


// Função que calcula o inverso modular de um número inteiro a (mod n) usando o algoritmo extendido de Euclides
__int128_t modular_inverse(__int128_t a, __int128_t n) {

  //Variáveis Locais
  __int128_t t = 0, newt = 1;
  __int128_t r = n, newr = a % n;


  //Procedimentos
    //Loop principal
    while (newr != 0) {
    
      __int128_t q = r / newr;
      __int128_t temp = newt;
      newt = t - q * newt;
      t = temp;

      //Atualizando variáveis para a próxima iteração
      temp = newr;
      newr = r - q * newr;
      r = temp;
    }

    //Checando se a, n são coprimos
    if(r!=1)
      return (-1);  //Inversa não existe

  //Resultado
  if(t<0) t+=n;
  return t;

}


//Função que define os parâmetros usados no algoritmo
void setup_williams_parameters(int64_t* a, int64_t*  b, int64_t* d, int64_t N){

  //Semente para  geração de números aletórios
  srand(time(NULL));


  //Procedimentos
    //Gerando números aleatórios usados no algoritmo
    reselect_parameters:
    int64_t a_=rand()%N;
    int64_t b_=rand()%N;
    int64_t d_=rand()%N ;
    
    int64_t r=0;    
    if(perfect_square_detection_64bits(d_, &r)) goto reselect_parameters;
    else{
      (*a)=a_; (*b)=b_; (*d)=d_;
      return;
    };

};


//Função que racionaliza um número algébrico quadrático
struct algebraic_quadratic_number algebraic_quadratic_number_rationalization(struct algebraic_quadratic_number z0, int64_t N){

  //Variáveis locais
  struct algebraic_quadratic_number z1; 
  __int128_t den=(z0.a*z0.a)-(z0.b*z0.b*z0.d); if(den<0) den+=N;
  __int128_t inv=modular_inverse(den, N);


  //Procedimentos
    //Ajuste de variáveis
    z1.a=(z0.a*z0.a)+(z0.b*z0.b*z0.d); z1.b=(-2)*z0.a*z0.b; z1.d=z0.d;
    z1.a=(z1.a*inv)%N;  z1.b=(z1.b*inv)%N;
    z1.a=z1.a%N;  z1.b=z1.b%N;
    if(z1.a<0)  z1.a=z1.a+N;
    if(z1.b<0)  z1.b=z1.b+N;  

  //Resultado
  return z1;

};


//Função que calcula o mdc de dois números inteiros de 128 bits
int64_t gcd_s64(int64_t a, int64_t b){

  //Resultado
  if(b==0) return a;
  else return gcd_s64(b, a%b);

};


//Função nque fatora um minteiro de 64 bits usando a variante algébrica do algoritmo (p+1) de Williams
void williams_factorization_algebraic(int64_t N, int64_t B){

  //Variáveis locais
  bool* power_prime_array = power_prime_sieve_setup(B); //Buffer de números primos até B
  struct algebraic_quadratic_number z, zp;
  int64_t a, b, d, factor, power_prime;

  
  //Procedimento
    //Determinando os paramêtros usados no algoritmo
    setup_williams_parameters(&a, &b, &d, N);
    z.a=a; z.b=b; z.d=d;
    z=algebraic_quadratic_number_rationalization(z, N);  //A descrição do algoritmo no artigo sugere racionalizar o inteiro algébrico
                                                           
    //Loop principal
    for(int64_t i=2; i<=B; ++i){
      
      //Restrição
      if(power_prime_array[i]==false) continue;
      
      //Computando z^q (mod n) para potência de números primos
      zp=algebraic_quadratic_pow_mod(z, i, N);

      //Testando se um fator primo foi encontrado
      factor=gcd_s64(N, zp.a-1);
      if(factor>1 && factor<N) break;
      factor=gcd_s64(N, zp.b);
      if(factor>1 && factor<N) break;


      //Ajuste de variáveis para a próxima iteração
      z.a=zp.a; z.b=zp.b;

    }

    //Limpando o cachê de memória
    if(power_prime_array){
     free(power_prime_array); power_prime_array=NULL;
    }

     
  //Resultado
  printf("Fator de %li encontrado: %li.\n", N, factor);

};

//******************************************************************************************************************************************************************
// FIM DO HEADER
#endif
