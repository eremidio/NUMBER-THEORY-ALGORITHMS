//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA A VARIANTE DE MCKEE DO ALGORITMO DE FATORAÇÃO VIA FRAÇÕES CONTINUADAS 

/*
SEJA b UM LIMITANTE SUPERIOR DA RAÍZ QUADRADA DE UM NÚMERO n A SER FATORADO. SE n NÃO TIVER FATORES PRIMOS
INFERIORES A 2n^(1/4) (FATORES DESTA MAGNITUDE PODEM SER REMOVIDOS POR DIVISÃO), PODEMOS USAR SOLUÇÕES DA 
EQUAÇÃO DIOFANTINA Q(x,y)=(x+by)²-z² PARA FATORAR n, TOMANDO mdc(n, x+by-z) COM y≲n^(1/4) |x|y≲2n^(1/2),
z≲2n^(1/4). UMA BUSCA DIRETA POR VALORES x,y DE MODO QUE (x+by)²=z²(mod n) SEJA UM QUADRADO PERFEITO LEVARIA
O(n^(1/2)) OPERAÇÕES. A IDEIA DO ALGORITMO DE MCKEE É RESOLVER UM PROBLEMA SIMILAR TRABALHANDO mod m², ONDE
m É UM INTEIRO QUE DIVIDE z. NESTA SITUAÇÃO PODE-SE APROXIMAR OS VALORES DE x,y POR MEIO DO CÁLCULO DE
CONVERGENTES λ/y DA EXPANSÃO EM FRAÇÕES CONTÍNUAS DE x0/m², ONDE x0=xy⁻¹ (mod m²) SÃO SOLUÇÕES DA EQUAÇÃO
Q(x0, 1)=0 (mod m²). PARA CADA PAR (λ,y) AS CONDIÇÕES y≲n^(1/4) E Q((x0y-λm²), y)=z² (QUADRADO PERFEITO)
DEVEM SER CHECADAS. UM FATOR NÃO TRIVIAL DE n É OBTIDO POR MEIO DO DO CÁLCULO DO mdc.

PARA MAIORES INFORMAÇÕES: The Joy Of Factoring by Samuel Wagstaff Jr
                          https://www.ams.org/journals/mcom/1999-68-228/S0025-5718-99-01133-3/S0025-5718-99-01133-3.pdf


*/

//*************************************************************************************************************************
//CABEÇALHO
#ifndef MCKEE_CONTINUED_FRACTION_FACTORIZATION_H
#define MCKEE_CONTINUED_FRACTION_FACTORIZATION_H
#include"prime_power_detection.h"
#include"polynomial_root_modular.h"
#include<stdint.h>
#include<cmath>
#include<vector>
#include<iostream>

//*************************************************************************************************************************
//ESTRUTURAS USADAS NO ALGORITMO
struct mx_pair{
  int64_t m;
  int64_t x0;

};

//*************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t gcd_s64(int64_t, int64_t);
bool fast_prime_checking(int64_t);
void trial_division(int64_t&);
void compute_polynomial_roots(std::vector<struct mx_pair>&, int64_t, int64_t);
bool parameter_selection(struct mx_pair, int64_t&, int64_t&, int64_t&, int64_t, int64_t);
void mckee_continued_fraction_factorization(int64_t);

//*************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides para inteiros de 64 bits
int64_t gcd_s64(int64_t a, int64_t b){

  if(b==0) return a;
  else return gcd_s64(b, (a%b));

};

//Função que detecta compostos e potenciais pseudoprimos
bool fast_prime_checking(int64_t n){
    // Variáveis locais
    int prime_seed[30] = {2,  3,  5,  7,  11, 13,  17,  19,  23,  29,
                        31, 37, 41, 43, 47, 53,  59,  61,  67,  71,
                        73, 79, 83, 89, 97, 101, 103, 107, 109, 113};

   // Procedimentos: teste de divisibilidade por primos inferiores a 100
   for (auto prime:prime_seed) {
     if (n == prime) return true;
     if ((n % prime) == 0) return false;
     if (mod_bin_pow(prime, (n - 1), n) != 1) return false; //Teste de Fermat

   };

  // Resultado caso o número passe nos testes acima
  return true;

};

//Função que performa divisão por tentativa e erro até 2N^(1/4)
void trial_division(int64_t& N){

  //Variáveis locais
  int64_t N_=N;
  int64_t bound=2*std::sqrt(std::sqrt(N));

  //Procedimentos
    //Divisores 2 e 3
    if(!(N_&1)){
      std::cout<<"Fator de "<<N<< " encontrado: 2\n";
      while(!(N_&1)) N_>>=1;
    }

    if((N_%3)==0){
      std::cout<<"Fator de "<<N<< " encontrado: 3\n";
      while((N_%3)==0) N_/=3;
 
    }

    //Loop principal
    for(int64_t i=5; i<(bound+2); i+=6){
      if((N_%i)==0){
        std::cout<<"Fator de "<<N<< " encontrado: "<<i<<'\n';
        while((N_%i)==0) N_/=i;
 
      }

      if((N_%(i+2))==0){
        std::cout<<"Fator de "<<N<< " encontrado: "<<(i+2)<<'\n';
        while((N_%(i+2))==0) N_/=(i+2);
 
      }
    }


  //Ajuste de variáveis
  if(N_<N) std::cout<<"Cofator: "<<N_<<'\n';
  N=N_;

};


//Função que computa raízes da forma quadrática Q(x0, 1)=0 (mod m²) com m|z
void compute_polynomial_roots(std::vector<struct mx_pair>& poly_root_vector, int64_t N, int64_t b){

  //Variáveis locais
  polynomial<int64_t> Q_poly;
  int64_t limit=std::cbrt(N);
  struct  mx_pair poly_root;

  //Procedimentos
    //Ajuste do polinômio Q(x0, 1)=(x0+b)²-N=x0²+2x0b+(b²-N)
    Q_poly.degree=2;
    Q_poly.polynomial_coefficients.push_back(1); Q_poly.polynomial_coefficients.push_back(2*b); Q_poly.polynomial_coefficients.push_back(((b*b)-N));
    Q_poly.polynomial_powers.push_back(2); Q_poly.polynomial_powers.push_back(1); Q_poly.polynomial_powers.push_back(0);


    //Loop principal
    mainloop:
    for(int64_t m1=2; m1<=limit; m1++){
      if(fast_prime_checking(m1)==true){
        poly_root.m=m1;
        poly_root.x0=polynomial_root_modulo_prime_power(Q_poly, m1, 2);
        if(poly_root.x0>0) poly_root_vector.push_back(poly_root);
        
                                       }
    }

    //Reinicializando o loop caso raízes não tenham sido encontradas no limite acima
    if(poly_root_vector.size()<1){
      limit*=100;
      goto mainloop;
    }

};


//Função que computa valores de x, y, z tais que (x+by)²=z² (mod N) (variante greedy descrita no artigo)
bool parameter_selection(struct mx_pair mx, int64_t& x, int64_t& y, int64_t& z, int64_t N, int64_t b){

  //Variáveis locais
  __int128_t Q;
  int64_t bound=2*std::cbrt(N);
  int64_t Q_, z_;
  int64_t r1, x1, y1, r2, x2, y2;

  //Procedimentos 
    //Testando se os valores x=x0, y=1 Fazem com que Q(x, y) (mod N) seja um quadrado perfeito
    Q=((mx.x0+b)*(mx.x0+b))%N; 
    Q_=Q;
    if(fast_square_detection(Q_, &z_)==true){
      x=mx.x0; y=1; z=z_;
      return true;    
    }

    //1ªiteração
    r1=std::ceil((mx.m*mx.m*1.0)/mx.x0);
    x1=(mx.x0*r1)-((mx.m*mx.m));
    y1=r1;
      //Teste
    Q=((x1+b*y1)*(x1+b*y1))%N; 
    Q_=Q;
    if(fast_square_detection(Q_, &z_)==true){
      x=x1; y=y1; z=z_;
      return true;    
    }

    //Loop principal
    while(1){
      //Cálculo dos parâmetros x2, y2, r2
      r2=std::ceil((mx.m*mx.m*1.0)/x1);
      x2 = (x1*r2)-((mx.m*mx.m));
      y2 = y1*r2;

      //Teste
      Q=((x2+b*y2)*(x2+b*y2))%N; 
      Q_=Q;
      if(fast_square_detection(Q_, &z_)==true){
        x=x2; y=y2; z=z_;
        return true;    
      }
    
      //Condição que determina
      if(y2>bound) break;

      //Atualizandovariáveis para a próxima iteração
      x1=x2; y1=y2; r1=r2;

    }
          


  //Resultado em caso de falha
  return false;

};

//Função que implementa o algoritmo de Mckee usando frações continuadas
void mckee_continued_fraction_factorization(int64_t N){

  //Etapa 1: removendo fatores primos pequenos
  trial_division(N);
  if(N==1 || fast_prime_checking(N)==true) return;

  //Variáveis locais
  int64_t b=std::ceil(std::sqrt(N));
  int64_t x, y, z;
  int64_t Q, factor, cofactor;
  std::vector<struct mx_pair> poly_root_vector;

  //Procedimentos
    //Etapa2: Computando raízes da forma quadrática Q(x0, 1)=0 (mod m²) com m|z
    poly_root_vector.resize(0);
    compute_polynomial_roots(poly_root_vector, N, b);


    //Etapa 3: computando valores de x, y, z tais que  Q(x, y)=z² mod N
    for(auto mx:poly_root_vector){
        if(parameter_selection(mx, x, y, z, N, b)==true){

          //Etapa 4: cálculo dos fatores primos
          Q=(x+(b*y)-z);
          factor=gcd_s64(Q, N);
          if(factor>1 && factor<N){
            cofactor=N/factor;
            std::cout<<"Fatores de "<< N << " encontrados: "<<factor<<" e "<<cofactor<<'\n';
            return;
          }

        }
    }



  //Em caso de falha do algoritmo
  std::cout<<"O algoritmo não encotrou fatores primos do número em questão\n";
   


};

//*************************************************************************************************************************
//FIM DO HEADER
#endif
