//VAMOS CRIAR UM PROGRAMA QUE COMPUTA POLINÔMIOS CICLOTÔMICOS USANDO INTEIROS DE 32 BITS

/*
DADO UM INTEIRO POSITIVO n, UMA RÁIZ DA UNIDADE DE ORDEM n É UMA SOLUÇÃO DA EQUAÇÃO (x^n)-1=0, SOLUÇÕES DESTA EQUAÇÃO TEM A FORMA ζ(n)=exp(2πk/n), PARA k INTEIRO
POSITIVO. CONSIDERANDO VALORES k NO INTERVALO k=1,2,..., n-1; DEFINIMOS O n-ÉSIMO POLINÔMIO CICLOTÔMICO COMO Φ(n)=Π(x-ζ(k)) COM A RESTRIÇÃO A k: mdc(k,n)=1.

POLINÔMIOS CICLOTÔMICOS SÃO IRREDUTÍVEIS NO ANEL DE INTEIROS RACIONAIS. A SEGUINTE RELAÇÃO É VÁLIDA PARA DIVISORES PRÓPRIOS d DE UM INTEIRO n: (x^n)-1=ΠΦ(d) E
Φ(n)=[(x^n)-1]/ΠΦ(d). TAIS EXPRESSÕES PERMITEM O CÁLCULO SIMPLES DO n-ÉSIMO POLINÔMIO CICLOTOMICO PROVIDO A DECOMPOSIÇÃO DE n EM FATORES PRIMOS E OPERAÇÃO DE DIVISÃO
DE POLINÔMIOS. O GRAU DO n-ÉSIMO POLINÔMIO CICLOTOMICO É IGUAL A φ(n) ONDE φ É A FUNÇÃO TOTIENTE DE EULER.

POLINÔMIOS CICLOTÔMICOS SÃO DIRETAMENTE RELACIONADO AO CORPO DOS INTEIROS EM CORPOS NÚMERICOS CICLOTÔMICOS Q(ζ(n)). ALGORITMOS MODERNOS DE TESTAGEM DE PRIMALIDADE E
FATORAÇÃO (QUE GENERALIZAM OS CHAMADOS MÉTODOS n-1, n+1, ETC) EXISTEM QUE USAM POLINÔMIOS CICLOTÔMICOS. TAIS POLINÔMIOS SÃO DE GRANDE INTERSSE PARA TEORIA DOS NÚMEROS.

PARA MAIORES REFERÊNCIAS: https://en.wikipedia.org/wiki/Cyclotomic_polynomial#Further_reading
                          https://www.calstatela.edu/sites/default/files/cyclotomic.pdf
                          https://www.ams.org/journals/mcom/1989-52-185/S0025-5718-1989-0947467-1/S0025-5718-1989-0947467-1.pdf
                          https://math.stackexchange.com/questions/3769737/primality-testing-using-cyclotomic-polynomials

*/


//***************************************************************************************************************************
//CABEÇALHO
#ifndef CYCLOTOMIC_POLYNOMIALS_H
#define CYCLOTOMIC_POLYNOMIALS_H
#include"polynomials.h"
#include"gauss_euler_primality_test.h"
#include<numeric>



//***************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void factor(int32_t, std::vector<int32_t>&, bool&);
bool power_prime_test(int32_t, int32_t&);
polynomial<int32_t> prime_cyclotomic_polynomial(int32_t);
polynomial<int32_t> prime_power_cyclotomic_polynomial(int32_t);
polynomial<int32_t> generate_product_polynomial(int32_t);
polynomial<int32_t> generate_cyclotomic_polynomial(int32_t);

bool cyclotomic_polynomial_prime_test(int32_t);

//***************************************************************************************************************************
//FUNÇÕES

//Função que calcula os divisores de um inteiro de 32 bits e determina se o mesmo é primo ou não
void factor(int32_t n, std::vector<int32_t>& divisors_vector, bool& is_prime){

 // Caso trivial: n é primo e nenhuma fatoração é necessária
 if(gauss_euler_primality_test(n)==true)
  is_prime=true;
 else 
  is_prime=false;


 //Ajuste de variáveis
 divisors_vector.resize(0);

 //Variáveis locais
 int32_t i;

 
 //Procedimentos
  //Loop principal: computando os fatores do número em questão
  for(i=1; i<n; ++i){

   if((n%i)==0)
    divisors_vector.push_back(i);

                    };

 
                                                                             };


//Função que testa se n é um potência de um primo
bool power_prime_test(int32_t n, int32_t& prime){

 //Variáveis locais
 int32_t tester=2;
 int32_t sqrt_n=sqrt(n); 

 //Procedimentos 
  //Caso particular números da forma 2^N e 3^N

  while(tester<n){

   tester<<=1;
   if(tester==n){
    prime=2;
    return true;
                }

                 };

  if(n%3==0){
    while(n%3==0)
     n/=3;

    if(n==1){
     prime=3;
     return true;
            }
    else
     return false;

            };


  //Loop principal
 for(int32_t i=5; i<=sqrt_n; i+=6){

  if(n%i==0){
    while(n%i==0)
     n/=i;

    if(n==1){
     prime=i;
     return true;
            }
    else
     return false;

            };

  if((n%(i+2))==0){
    while((n%(i+2))==0)
     n/=(i+2);

    if(n==1){
     prime=(i+2);
     return true;
            }
    else
     return false;

                  };

 
                                  };

 //Resultado
 return false;
                                                };


//Função que computa o n-ésimo polinômio ciclotômico quando n é primo
polynomial<int32_t> prime_cyclotomic_polynomial(int32_t n){

 //Variáveis locais
 polynomial<int32_t> cyclotomic_polynomial;


 //Procedimentos
  //Ajuste do array de coeficientes, de potências e do grau do polinômio ciclotômico
  cyclotomic_polynomial.degree=(n-1);
  
  for(int32_t i=(n-1); i>=0; --i){
  
   cyclotomic_polynomial.polynomial_powers.push_back(i);
   cyclotomic_polynomial.polynomial_coefficients.push_back(1);

                                 };


 //Resultado
 return cyclotomic_polynomial;

                                                          };


//Função que calcula o n-ésimo polinômio ciclôtomico quando N é uma potência de um número primo
polynomial<int32_t> prime_power_cyclotomic_polynomial(int32_t n, int32_t prime){

 //Variáveis locais
 int32_t prime_power=n/prime;
 int32_t index=(prime_power*(prime-1));
 polynomial<int32_t> cyclotomic_polynomial;


 //Procedimentos
  //Ajuste do array de coeficientes, de potências e do grau do polinômio ciclotômico
  cyclotomic_polynomial.degree=index;
  
  for(int32_t i=index; i>=0; --i){
  
   if(i==index){
    cyclotomic_polynomial.polynomial_powers.push_back(i);
    cyclotomic_polynomial.polynomial_coefficients.push_back(1);
    index-=prime_power;
               }

   else{
    cyclotomic_polynomial.polynomial_powers.push_back(i);
    cyclotomic_polynomial.polynomial_coefficients.push_back(0);
       };


                                 };


 //Resultado
 return cyclotomic_polynomial;
 
                                                                               };



//Função que gera o polinômio P(x)=(x^n)-1 para n (função intermediária para o cálculo de um polinômio ciclotômico)
polynomial<int32_t> generate_product_polynomial(int32_t n){

 //Variáveis locais
 polynomial<int32_t> product_polynomial;


 //Procedimentos
  //Ajuste do array de coeficientes, de potências e do grau do polinômio ciclotômico
  product_polynomial.degree=n;
  
  for(int32_t i=n; i>=0; --i){
 
   product_polynomial.polynomial_powers.push_back(i);

   if(i==0 || i==n)
    product_polynomial.polynomial_coefficients.push_back(1);
   else
    product_polynomial.polynomial_coefficients.push_back(0);

                             };


 //Resultado
 return product_polynomial;
 
                                                          };


//Função que calcula um polinômio ciclotômico para um inteiro qualquer
polynomial<int32_t> generate_cyclotomic_polynomial(int32_t n){

 //Variáveis locais 
 std::vector<int32_t> divisors_vector;
 int32_t prime_base;
 bool is_prime, is_power_prime;


 //Procedimentos 
  //Casos especiais:
   //n=1
   if(n==1){
    polynomial<int32_t> cyclotomic_polynomial;
   
    //Ajuste do polinômio 
    cyclotomic_polynomial.degree=1;
    cyclotomic_polynomial.polynomial_powers={1,0};
    cyclotomic_polynomial.polynomial_coefficients={1,(-1)};

    //Resultado
    return cyclotomic_polynomial;
   
           };


   //n=2
   if(n==2){

    polynomial<int32_t> cyclotomic_polynomial;
   
    //Ajuste do polinômio 
    cyclotomic_polynomial.degree=1;
    cyclotomic_polynomial.polynomial_powers={1,0};
    cyclotomic_polynomial.polynomial_coefficients={1,1};

    //Resultado
    return cyclotomic_polynomial;
   
           };

   //Checando se n é uma potência de número primo
   if(power_prime_test(n, prime_base)==true)
    return prime_power_cyclotomic_polynomial(n, prime_base);
  
   //Checando se n é primo e computando possíveis divisores
   factor(n, divisors_vector, is_prime);
   
   if(is_prime==true)
    return prime_cyclotomic_polynomial(n);


   //Caso geral computando o polinômio ciclotômico quando n é composto
    //Variáveis locais
    polynomial<int32_t> product_polynomial=generate_product_polynomial(n);
    

    //Procedimentos
     //Loops sobre os divisores do número em questão
     for(auto divisor:divisors_vector){
      polynomial<int32_t> temp=generate_cyclotomic_polynomial(divisor);
      polynomial<int32_t> temp2=product_polynomial/temp;

      //Ajuste de variáveis para a próxima iteração
      product_polynomial=temp2;
      
                                      };

    
     //Resultado
     return product_polynomial;  
 
                                                             };




//Função que testa a primalidade de um inteiro n usando polinômios ciclotômicos
bool cyclotomic_polynomial_prime_test(int32_t n){

 //Variáveis locais
 polynomial<int32_t> cyclotomic_polynomial=generate_cyclotomic_polynomial((n-1));
 int32_t i;

 //Procedimentos
  //Teste: um número é primo se e somente para algum inteiro a tal que 1<a<n Φ((n-1))=0 (mod n)
  for(i=2; i<n; ++i){
    if( ((cyclotomic_polynomial.evaluate_polynomial(i))%n)==0)
     return true;
                    };

  return false;

                                                }; 




//***************************************************************************************************************************
//FIM DO HEADER
#endif
