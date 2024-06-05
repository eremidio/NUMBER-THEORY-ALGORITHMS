//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS PARA CALCULAR RAÍZES DE POLINÔMIOS A MENOS DE UMA RELAÇÃO DE CONGRUÊNCIA PARA INTEIROS DE 64 BITS

/*
SEJA UM POLINÔMIO f(x) DEFINIDO EM UM CORPO FINITO DO TIPO INTEIRO A MENOS DE UMA CONGRUẼNCIA.
DE GRANDE INTERESSE TEÓRICO É O ESTUDO DE SOLUÇÕES DA EQUAÇÃO DIOFANTINA f(x)=0 (mod n).

OS SEGUINTES RESULTADOS SÃO DE INTERESSE TEÓRICO:

LEMA DE HENSEL: SE UM POLINÔMIO f(x) POSSUI UMA SOLUÇÃO EM F(p), ISTO É, f(x)=0 (mod p). ENTÃO EXISTE UMA SOLUÇÃO PARA QUALQUER
POTÊNCIA DE, ISTO É, UMA SOLUÇÃO PARA f(x)=0 (mod p^k) COM k INTEIRO MAIOR QUE 1. ESPECIFICAMENTE SE f(r)=0 (mod p^k) E
f'(x)≠0 (mod p), ENTÃO EXISTE UM m INTEIRO TAL QUE f(s)=0 (mod p^(k+m)) E s=r (mod p^k) s É ÚNICO A MENOS DE UMA CONGRUÊNCIA
mod(p^(m+k)).

TAL TEOREMA É PARTICULARMENTE ÚTIL PARA ENCONTRAR RAÍZES DE UMPOLINÕMIO A MENOS DE UMA CONGRUÊNCIA MÓDULO UMA POTÊNCIA
DE UM NÚMERO PRIMO, COMBINANDO ESTE RESULTADO COM O TEOREMA DE RESÍDUO CHINÊS CONGRUÊNCIAS MÓDULO NÚMEROS COMPOSTOS
PODEM SER FACILMENTE COMPUTADAS.

USAREMOS UMA ABORDAGEM RECURSIVA NA IMPLEMENTAÇÃO DESSA ROTINA.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Hensel%27s_lemma#Hensel_lifting
                          https://brilliant.org/wiki/hensels-lemma/

*/

//*****************************************************************************************************************************************************
//CABEÇALHO
#ifndef POLYNOMIAL_ROOT_MODULAR_H
#define POLYNOMIAL_ROOT_MODULAR_H
#include"polynomial_root.h"
#include"mod_bin_exponentiation128.h"


//*****************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t gcd_hensel(int64_t, int64_t);
bool hensel_condition(polynomial<int64_t>&, int64_t, int64_t);
int64_t polynomial_root_modulo_prime(polynomial<int64_t>&, int64_t);
int64_t polynomial_root_modulo_prime_power(polynomial<int64_t>&, int64_t, int64_t);


//*****************************************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides
int64_t gcd_hensel(int64_t a, int64_t b){

  if(b==0)
    return a;
  else
    return gcd_hensel(b, (a%b));
                                        };


//Função que checa se uma dada solução r de f(x)=0 (mod p) satifaz a condição f'(x)≠0 (mod p)
bool hensel_condition(polynomial<int64_t>& p1, int64_t solution, int64_t prime){

  //Variáveis locais
  polynomial<int64_t> poly_der = polynomial_derivative<int64_t>(p1);
 

  //Resultado da execução do algoritmo
  if(gcd_hensel(poly_der.evaluate_polynomial(solution), prime)==1 || poly_der.evaluate_polynomial(solution)%prime==0)
    return true;
  else
    return false;
                                                                               };


//Função que calcula uma solução da equação f(x)=0 (mod p), com p primo por força bruta
int64_t polynomial_root_modulo_prime(polynomial<int64_t>& p1, int64_t prime){
 
  //Procedimento
    //Busca por uma solução: nota o intervalo de buscas é limitado pela relação k>p --> l=k(mod p)<p
    for(int64_t i = 1; i<prime; ++i){
    
      if(p1.evaluate_polynomial(i)%prime==0 && hensel_condition(p1, i, prime)==true)
        return i;
                                    };


    //Caso uma solução não seja encontrada
    return 0;

                                                                             };


//Função que calcula uma solução da equação f(x)=0 (mod p^k), com p primo e k inteiro
int64_t polynomial_root_modulo_prime_power(polynomial<int64_t>& p1, int64_t prime, int64_t power){

  //Casos base: expoente 1
  if(power==1)
    return polynomial_root_modulo_prime(p1, prime);


  //Chamada recursiva do algoritmo
  int64_t r=polynomial_root_modulo_prime_power(p1,prime, (power-1));
  int64_t s=r;
  int64_t modulus=bin_pow(prime, power);
  

  

  //Procedimento
    //Cálculo de uma solução
    while(s<modulus){

      if(p1.evaluate_polynomial(s)%modulus==0 && hensel_condition(p1, s, prime)==true)
        return s;
      else
        s+=(modulus/prime);
                    };


    //Caso uma solução não seja encontrada
    return 0;  
                                                                                                };


//*****************************************************************************************************************************************************
//FIM DO HEADER
#endif
