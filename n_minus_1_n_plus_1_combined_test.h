//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UM TESTE DE PRIMALIDADE BASEADO NA FATORAÇÃO PARCIAL DE (n+1) E (n-1) DE UM INTEIRO n

/*

ALGUNS TEOREMAS IMPORTANTES PERMITEM ASSEGURAR A PRIMALIDADE DE UM INTEIRO n SE UMA FATORAÇÃO PARCIAL DE (n-1) E/OU (n+1) FOR
CONHECIDA, ISTO É, SE (n-1)=F1.R1 E (n+1)=F2.R2 ONDE A DECOMPOSIÇÃO DE F1 E F2 EM FATORES PRIMOS É CONHECIDA. SE B1 E B2
FOREM LIMITANTES PARA OS FATORES PRIMOS DE R1 E R2, EXSITE UM CONJUNTO DE PARÂMETROS TAIS QUE SE CERTAS DESIGUALDADES SÃO
SATISFEITAS, UM CERTIFICADO DE PRIMALIDADE PARA O NÚMERO EM QUESTÃO É OBTIDO POR MEIO DE COMBINAÇÕES DE MÚLTIPLOS TESTES 
USANDO RELAÇÕES DE CONGRUÊNCIA NO GRUPO Z/nZ.

AO CONTRÁRIO DE TESTE DE LUCAS/POCKLINGTON QUE GERAM UM CERTIFICADO DE PRATT E DE VARIANTES DE TESTES ENVOLVENDO SEQUÊNCIAS
DE LUCAS QUE REQUER UMA FATORAÇÃO COMPLETA DE (n-1) E (n+1) (OU PELO MENOS QUE A PARTE FATORADA EXCEDA √n), O TESTE 
COMBINADO REQUER UMA DECOMPOSIÇÃO APENAS PARCIAL EM FATORES PRIMOS, O QUE AUMENTA A PROBABILIDADE DE SUCESSO DA OBTENÇÃO DE
UM CERTIFICADO DE PRIMALIDADE. 

VAMOS IMPLEMENTAR UM VARIANTE SIMPLES DO TESTE COMBINADO ENVOLVENDO FATORAÇOES PARCIAIS DE (n+1) E (n-1). VARIANTES MAIS
ROBUSTAS DO TESTE ENVOLVENDO FATORAÇÃO DE (n-1) REQUEREM QUE A DESIGUALDADE F1>n^(3/10) SEJA SATISFEITA. ESTES TIPOS DE
TESTES PERMITEM DETERMINAR A PRIMALIDADE DE NÚMEROS DA ORDEM DE 10^40 -- 10^100 EM ALGUNS CASOS.


PARA MAIORES INFORMAÇÕES: Prime Numbers And Computer Methods For Factorization, by Hans Riesel
                          Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance

*/


//**********************************************************************************************************************************
//CABEÇALHO
#ifndef N_MINUS_ONE_N_PLUS_ONE_COMBINED_PRIMALITY_TEST_H
#define N_MINUS_ONE_N_PLUS_ONE_COMBINED_PRIMALITY_TEST_H
#include"lucas_sequence_matrix.h"
#include<string>
#include<iostream>
#include<vector>
#include<cstdint>
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/cstdint.hpp>
using namespace boost::multiprecision;


//CONSTANTES GLOBAIS
const int residues30[8]={1,7,11,13,17,19,23,29};
const int primes100[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
const int tab8[8]={0, 1, 0, (-1), 0, (-1), 0, 1};


//**********************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int jacobi_symbol(cpp_int, cpp_int);
cpp_int mod_bin_pow(cpp_int, cpp_int, cpp_int);
cpp_int gcd_boost(cpp_int, cpp_int);

bool lucas_pocklington_test(cpp_int,cpp_int, std::vector<cpp_int>&);
void setup_lucas_sequence_parameters(cpp_int&, cpp_int&, cpp_int&, cpp_int);
bool lucas_sequence_test(cpp_int,cpp_int,std::vector<cpp_int>&);

bool setup_test_parameters(cpp_int, int64_t, cpp_int&, cpp_int&, cpp_int&, cpp_int&, std::vector<cpp_int>&, std::vector<cpp_int>&);
bool n_minus_one_n_plus_one_combined_primality_test(cpp_int, int64_t);


//**********************************************************************************************************************************
//FUNÇÕES AUXILIARES
//Função que calcula o símbolo de Jacobi de dois inteiros de precisão arbitrária
int jacobi_symbol(cpp_int a , cpp_int b){

  //Restrição
  assert((b&1)==1); //O segundo termo deve ser ímpar

  //Variáveis locais
  cpp_int x=a, y=b, z=1;
  cpp_int t;


  //Procedimento
    //Loop principal
    while(1){

      //Resultado
      if(x==0 || x==1){
        cpp_int r = (x*z);
        return (static_cast<int>(r));
      }
  
      //Checando o sinal do primeiro argumento
      if(x<0){
        x*=(-1);
        t=((y-1)>>1);//(-1)^[y-1]/2
        if(t&1) z*=(-1);
        continue;
      }

      //Reduzindo os coeficientes
      if(x>=y){
        x%=y;
        continue;
      }
 
      //Checando a paridade do primeiro termo
      if(!(x&1)){
        x>>=1;
        int tt=tab8[(int)(y/8)];
        t=tt;//(-1)^[y²-1]/8
        z*=t;
        continue;
      }
      
      if((x&1)){

        t=(((x-1)>>1)&1)*(((y-1)>>1)&1);//(-1)^[(x-1)(y-1)]/4
        cpp_int temp=x;

        x=(y%x);
        y=temp;
        if(t&1) z*=(-1);  

      }
      

    };//Fim do loop principal
    

  //Em caso de erro
  return 0; 

};

//Função que computa uma exponencial binária modular
cpp_int mod_bin_pow(cpp_int a, cpp_int b, cpp_int m){

  // Variáveis locais
  cpp_int result = 1;

  //Procedimentos: loop prncipal
  while (b > 0) {

    //Checando a paridade do bit do expoente
    if (b & 1) result = (result*a) % m;

    //Atualizando variáveis para a próxima iteração
    a = (a*a) % m;
    b >>= 1;

  };

  // Resultado
  return result;

};

//Função que computa mdc de dois inteiros de precisão arbitrária usando o algoritmo de Euclides
cpp_int gcd_boost(cpp_int a, cpp_int b){

  //Variáveis locais
  cpp_int t=0;


  //Procedimento: loop principal
  while(b>0){

    t=b;
    b=(a%b);
    a=t;

  }

  //Resultado
  return a;

};


//**********************************************************************************************************************************
//FUNÇÕES 
//Função que determina as condições de aplicabilidade do teste de primalidade

/*
  NOTA: Usamos nessa implementação o algoritmo de divisão simples com pequena otimização no loop principal razoável
        para encontrar divisores da ordem de 10^9 ~10^10. Como apenas uma fatoração parcial é requerida valores da
        ordem de 10^50 podem ser testados em um tempo relativamente curto. Outros algoritmo de fatoração como
        Pollard (p-1) e o método de curvas elíticas podem ser empregados para buscar fatores primos maiores.

*/
bool setup_test_parameters(cpp_int n, int64_t B, cpp_int& F1, cpp_int& F2, cpp_int& R1, cpp_int& R2,
                           std::vector<cpp_int>& factors_minus, std::vector<cpp_int>& factors_plus){

  //Variáveis locais
  cpp_int G, F0, Nm, Np, temp;


  //Procedimentos
    //Ajuste de variáveis
    R1=(n-1); R2=(n+1); F1=1; F2=1;
    Nm=R1; Np=R2;


    //Etapa 1: determinando fatores primos inferiores a 30
    for(int i=0; i<10; ++i){
      while(R1%primes100[i]==0){
        R1=R1/primes100[i];
        F1=F1*primes100[i];
      }

      while(R2%primes100[i]==0){
        R2=R2/primes100[i];
        F2=F2*primes100[i];
      }
      if(R1<Nm){
        factors_minus.push_back(static_cast<cpp_int>(primes100[i]));
        Nm=R1;
      }
      if(R2<Np){
        factors_plus.push_back(static_cast<cpp_int>(primes100[i]));
        Np=R2;
      }

    };

    //Etapa 2: checando por fatores primos até um limite especificado usando um loop 30k+r
    for(int64_t i=30; i<B; i+=30){
      for(int j=0; j<8; ++j){

        int64_t d=i+residues30[j];//Divisores

        while(R1%d==0){
          R1=R1/d;
          F1=F1*d;
        }

        while(R2%d==0){
          R2=R2/d;
          F2=F2*d;
        }
        if(R1<Nm){
          factors_minus.push_back(static_cast<cpp_int>(d));
          Nm=R1;
        }
        if(R2<Np){
          factors_plus.push_back(static_cast<cpp_int>(d));
          Np=R2;
        }

      }
    };

    //Etapa 3: Calulando os parâmetros usados no teste
    G=B*F1+1;
    F0=B*F2-1;
    if(F0>G) G=F0;
    F0 = G*(((F1*F2*B*B)/2)+1);


  //Resultado
  if( F0 > n) return true;
  return false; //O teste é inconclusivo

};


//Função que define parâmetros da sequência de Lucas usadas no Teste
void setup_lucas_sequence_parameters(cpp_int& P, cpp_int& Q, cpp_int& D, cpp_int n){


  //Propceimentos
    //Ajuste de variáveis
    P=5; Q=1;

    //Loop principal selecionamado os parâmetros para parao teste da sequência de Lucas    
    for(int64_t i=0; ; ++i){

      D=(P*P)-(4*Q);
      if(jacobi_symbol(D, n)<0) return;
      else{
        P+=2;
        if((i%100)==0) Q+=1;
      }

    };

};


//Teste 1: teste de primalidade envolvendo exponenciais modulares
bool lucas_pocklington_test(cpp_int n, cpp_int F1, std::vector<cpp_int>& factors_minus){

  //Variáveis locais
  int index;  

  //Procedimento
    //Teste 1: teste de Fermat e de raízes quadradas da unidade em Z/nZ
    for(index=0; ; ++index){

      //Restrição
      if(index>=25){
        std::cout<<"Teste inconclusivo!\n";
        return false;
      };

      //Ajuste de variáveis
      cpp_int a=primes100[index];
      cpp_int t0=mod_bin_pow(a, F1, n);
      cpp_int t1=gcd_boost((t0-1), n);

      //Testes
      if(mod_bin_pow(a, (n-1), n)!=1) return false;
      if(t1>1 && t1<n){
        std::cout<<"Fator primo de "<<n<<" encontrado: "<< t1 << '\n';
        return false;
      }

      if(t1==1) break; //Resultado positivo no primeiro teste

    }


    //Teste 2: teste envolvendo a ordem do grupo Z/nZ (inteiros a menos uma relação de congruência)
    for (auto p:factors_minus){
      for(index=0; index<25; ++index){

        cpp_int a=primes100[index];
        cpp_int t0=mod_bin_pow(a, (n-1)/p, n);
        cpp_int t1=gcd_boost((t0-1), n);

        if(mod_bin_pow(a, (n-1), n)!=1) return false; //Teste de Fermat
        if(t1>1 && t1<n){
          std::cout<<"Fator primo de "<<n<<" encontrado: "<< t1 << '\n';
          return false;
        }
        if(t1==1) break; //mdc(a^(n-1)/q[i] mod n, n)=1 --> resultado positivo para o fator primo testado
  
      }
    };


  //Resultado
  return true;

};

//Função que implementa um teste de primalidade usando sequências de Lucas
bool lucas_sequence_test(cpp_int n, cpp_int F2, std::vector<cpp_int>& factors_plus){


  //Variáveis locais
  cpp_int P, Q, D;
  cpp_int t0, t1;


  //Procedimentos
    //Definição dos parâmetros da sequência de Lucas
    setup_lucas_sequence_parameters(P, Q, D, n);

    //Testes de primalidade
    while(P<10000){
      
      //Teste 1: Verificando a relação de congruência U(n+1) mod n==0
      Matrix<cpp_int> lucas_matrix1=lucas_sequence_modular_matrix<cpp_int, cpp_int>(P, Q, n, n);
      if(lucas_matrix1.matrix[0][0]!=0){
        //Reajuste de variáveis
        P=P+2;
        Q=Q+(P+1);
        continue;
      }      

      //Teste 2: Verificando a relação mdc( U(F2), n)=1 para a parte F2 completamente fatorada de F2
      Matrix<cpp_int> lucas_matrix2=lucas_sequence_modular_matrix<cpp_int, cpp_int>(P, Q, F2, n);
      t0 = lucas_matrix2.matrix[1][0]-1;
      t1 = gcd_boost(t0, n);

      if(t1>1 && t1<n){
        std::cout<<"Fator primo de "<<n<<" encontrado: "<< t1 << '\n';
        return false;
      }

     //Teste 3: Verificando a relação mdc( U((n+1)/q[i]), n)=1 para os fatores primos encontrados de (n+1)
     for(auto p:factors_plus){
       cpp_int index=(n+1)/p;
       Matrix<cpp_int> lucas_matrix3=lucas_sequence_modular_matrix<cpp_int, cpp_int>(P, Q, index, n);
       t0 = lucas_matrix3.matrix[1][0]-1;
       t1 = gcd_boost(t0, n);

       if(t1>1 && t1<n){
         std::cout<<"Fator primo de "<<n<<" encontrado: "<< t1 << '\n';
         return false;
       }

     };
      
      //Caso passenos testes acima um primo foi encontrado
      if(P<10000) break;
    };


  //Resultado
  return true;

};



//Função que implementa o teste de primalidade usando fatorações parciais de números inteiros
bool n_minus_one_n_plus_one_combined_primality_test(cpp_int n, int64_t B){

  //Caso base: primos inferiores a 100
  for(auto p:primes100){
    if((n-p)==0) return true;
    if((n%p)==0){
         std::cout<<"Fator primo de "<<n<<" encontrado: "<< p << '\n';
         return false;
    }
  }


  //Variáveis locais
  std::vector<cpp_int> factors_plus, factors_minus;
  cpp_int G, F1, F2, R1, R2;


  //Procedimentos
    //Checando condições de aplicabilidade do teste
    if(setup_test_parameters(n, B, F1, F2, R1, R2, factors_minus, factors_plus)==false){
      std::cout<<"Teste inconclusivo!\n";
      return false;
    };  

    //Testes de primalidade usando aritmética em Z/nZ e sequências de Lucas
    if(lucas_sequence_test(n, F2, factors_plus)== false ||
      lucas_pocklington_test(n, F1, factors_minus) == false)
      return false;


  //Resultado
  return true;

};


//**********************************************************************************************************************************
//FIM DO HEADER
#endif
