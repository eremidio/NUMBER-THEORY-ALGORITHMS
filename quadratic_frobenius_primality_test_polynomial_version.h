//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE PRIMALIDADE DE FRÖBENIUS USANDO POLINÔMIOS

/*
O TESTE DE PRIMALIDADE DE FRÖBENIUS É O MAIS EFICAZ TESTE DE PRIMALIDADE PARA
DETECÇÃO DE PSEUDOPRIMOS, COM PROBALIDADE QUE NÚMEROS COMPOSTOS PASSEM NO 
TESTE INFERIOR A 1/7710. EXISTEM DUAS VERSÕES DO TESTE UMA USANDO SEQUÊNCIAS 
DE LUCAS E OUTRA QUE EMPREGA POLINÔMIOS DE SEGUNDO GRAU f(x)=x²-bx-c, COM
((b²+ac)|n)=(-1) E (-c|n)=1, ONDE (|) DENOTA O SÍMBOLO DE JACOBI.

A VERSÃO USANDO POLINÔMIOS CHECA CONDIÇÕES SIMILARES A DO TESTE DE MILLER-
RABIN NO CORPO FINITO Z/nZ mod(f(x)), COMBINADO COM TESTES ENVOLVENDO PEQUENOS 
NÚMEROS PRIMOS.

PARA MAIORES INFORMAÇÕES: https://www.sciencedirect.com/science/article/pii/S0022314X98922478?via%3Dihub
                          https://arxiv.org/pdf/1908.02394


*/


//****************************************************************************************************
//CABEÇALHO
#ifndef QUADRATIC_FROBENIUS_PRIMALITY_TEST_POLYNOMIAL_H
#define QUADRATIC_FROBENIUS_PRIMALITY_TEST_POLYNOMIAL_H
#include"int128.h"
#include"prime_power_detection.h"
#include"binary_jacobi_symbol.h"
#include"mod_bin_exponentiation.h"


//CONSTANTES GLOBAIS
const int64_t B=50000;


//****************************************************************************************************
//ESTRUTURAS E FUNÇÕES AUXILIARES USADAS NO ALGORITMO
/*
  NOTA: No algoritmo de Fröbenius trabalhamos com o corpo finito Q[x]/(x²-bx-c, n) todas as operações
        são reduzidas mod (x²-bx-c) o que equivale a substituição x²=(bx+c) e também são reduzidas 
        (mod n) nesse caso uma redução modular simples sobre dos coeficientes dos polinômios. Por essa
        razão podemos usar uma estruturas simples sem a necessidade de estocar os coeficientes
        polinômiais em um array.

        A regra de multiplicação fica assim:
        (rx+s)(tx+u)=(rt)x²+(ru+st)x+(su)=(rt)(bx+c)+(ru+st)x+(su)=(rtb+ru+st)x+(su+rtc) com todos 
        os coeficientes reduzidos mod n (operador %) ao final.

*/

struct frobenius_polynomial{

  __int128_t x1;
  __int128_t x0;


};


//Função que multiplica dois polinômios no corpo finito Q[x]/(x²-bx-c, n) 
struct frobenius_polynomial frobenius_multiplication(struct frobenius_polynomial p1, struct frobenius_polynomial p2,
                                                     int64_t field_characteristic, int64_t b, int64_t c){

  //Variáveis locais
  struct frobenius_polynomial result;

  //Procedimentos
    //Calculando os coeficientes do produto
    result.x1 = ((p1.x1*p2.x0) + (p1.x0*p2.x1))%field_characteristic;
    result.x1 = result.x1+ (((p1.x1*p2.x1)%field_characteristic)*b)%field_characteristic;

    result.x0=(p1.x0*p2.x0)%field_characteristic;
    result.x0 = result.x0+ (((p1.x1*p2.x1)%field_characteristic)*c)%field_characteristic;


    result.x0%=field_characteristic; if(result.x0<0) result.x0+=field_characteristic;
    result.x1%=field_characteristic; if(result.x1<0) result.x1+=field_characteristic;


  //Resultado
  return result;

};


//Função que exponencia um polinômio no corpo finito Q[x]/(x²-bx-c, n) 
struct frobenius_polynomial frobenius_automorphism(struct frobenius_polynomial p1, __int128_t exponent,
                                                     int64_t field_characteristic, int64_t b, int64_t c){


  //Variáveis locais
  struct frobenius_polynomial q=p1, result={0,1}/*identidade no corpo finito f(x)=0x+1*/;


  //Procedimentos
    //Loop sobre os bits do expoente
    while(exponent>0){
      
      //Checando a paridade do bit
      if(exponent&1) result=frobenius_multiplication(result, q, field_characteristic, b, c);

      //Atualizando variáveis  para a próxima iteração
      q=frobenius_multiplication(q, q, field_characteristic, b, c);
      exponent>>=1;

    };


  //Resultado
  return result;


};


//****************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool trial_division(int64_t, int64_t);
void set_frobenius_parameters(int64_t, int64_t*, int64_t*);
bool quadratic_frobenius_test(int64_t);

//****************************************************************************************************
//FUNÇÕES
//Função que implementa o teste de divisão por tentativa e erro
bool trial_division(int64_t n, int64_t minimum){

  //Procedimentos
    //Fatores 2,3
    if(!(n&1) || (n%3)==0) return false;
   
    //Loop principal
    for(int64_t i=5; i<=minimum; i+=6){
        if((n%i)==0 || (n%(i+2))==0) return false;
    }

  //Resultado
  return true;

};

//Função que define parâmetros b, c usados no teste de Fröbenius
void set_frobenius_parameters(int64_t n, int64_t* b, int64_t* c){

  //Variáveis locais
  int64_t b_=1, c_=1, D=0;

  //Procedimentos
    //Escolhendo um valor de c tal que (-c|n)=1
    while(binary_jacobi(((-1)*c_), n)!=1) (c_)++;

    //Escolhendo um valor de b tal que (D|n)=(-1) com D=b²+4c
    while(1){

      D =(b_*b_)+(c_<<2);
      if(binary_jacobi(D, n)==(-1)) break;
      else (b_)++;

    };


  //Resultado
  (*b)=b_%n;
  (*c)=c_%n;

};  


//Função que implementa o teste de primalidade de Fröbenius em corpos finitos
bool quadratic_frobenius_test(int64_t n){

  //Casos bases
  if(n<2) return false;
  if(n==2 || n==3) return true;

  //Teste 1: testando se n é um quadrado perfeito ou potência de um primo
  int64_t sqrt_n;
  if(fast_square_detection(n, &sqrt_n)==true) return false;
  
  
  //Variáveis locais
  struct frobenius_polynomial f={1,0}/*f(x)=1x+0*/, frobenius_power_poly;
  int64_t minimum=(sqrt_n<B)?sqrt_n:B;
  int64_t b, c;

  //Procedimentos
    //Teste 2: teste de divisão por pequenos primos
    if(trial_division(n, minimum)==false) return false;
    if(n<(B*B)) return true; //Condição suficiente para a primalidade

    //Selecionando os parâmetros do teste de Fröbenius
    set_frobenius_parameters(n, &b, &c);
    printf("b, c: %li, %li\n", b, c);

    //Teste 3: checando a relação de congruência x^((n+1)/2) mod (n, x²-bx-c) ∈ Z
    frobenius_power_poly=frobenius_automorphism(f, ((n+1)>>1), n, b, c);
    if(frobenius_power_poly.x1!=0) return false;

    //Teste 4: checando a relação de congruência x^(n+1) mod (n, x²-bx-c) =(-c)
    frobenius_power_poly=frobenius_automorphism(f, (n+1), n, b, c);
    if(frobenius_power_poly.x1!=0 || frobenius_power_poly.x0!=(n-c)) return false;  
  

    //Teste 5: teste para raizes quadradas não triviais em Q[x]/(x²-bx-c, n) 
      //5.1: seleção dos parâmetros r, s
      __int128_t s=(n*n)-1;
      __int128_t r=0;

      while(!(s&1)){
        s>>=1;
        r++;

      };

      //5.2: teste
      frobenius_power_poly=frobenius_automorphism(f, s, n, b, c);
      if(frobenius_power_poly.x1==0 && (frobenius_power_poly.x0==1 || frobenius_power_poly.x0==(n-1)) ) return false;  

      while((r-2)>=0){

        s<<=1;
        r--;

        frobenius_power_poly=frobenius_automorphism(f, s, n, b, c);
        if(frobenius_power_poly.x1==0 && frobenius_power_poly.x0==(n-1)) return false;  

      }


  //Caso passe nos testes acima um primo ou pseudoprimo para os parâmetros b, c foi encontrado
  return true;

};

//****************************************************************************************************
//FIM DO HEADER
#endif
