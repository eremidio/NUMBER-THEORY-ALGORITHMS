//VAMOS IMPLEMENTAR UM CONJUNTO DE SUBROTINAS ÚTEIS NO ALGORITMO DEFATORAÇÃO DE INTEIROS USANDO CURVAS ELÍPTICAS

/*

ARTIGOS DE REFERÊNCIA: https://www.ams.org/journals/mcom/2013-82-282/S0025-5718-2012-02633-0/S0025-5718-2012-02633-0.pdf
                       https://en.wikipedia.org/wiki/Edwards_curve

*/



//***************************************************************************************************************************
//CABEÇALHO
#ifndef EDWARDS_ELLIPTIC_CURVE_ARITHMETIC_H
#define EDWARDS_ELLIPTIC_CURVE_ARITHMETIC_H
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<stdbool.h>
#include<math.h>
#include<gmp.h> 


//***************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void setup_edwards_curve_parameters(mpz_t, mpz_t, mpz_t, mpz_t, mpz_t, uint64_t);
void pointwise_addition(mpz_t, mpz_t, mpz_t, mpz_t, mpz_t, mpz_t, mpz_t, mpz_t, mpz_t);
void point_scalar_multiplication(mpz_t, mpz_t, mpz_t, mpz_t, mpz_t, mpz_t, mpz_t, uint64_t);


//***************************************************************************************************************************
//FUNÇÕES
//Função que computa parâmetros de curva de Edwards com grupo de torsão isomófico a Z/12Z 
void setup_edwards_curve_parameters(mpz_t x0, mpz_t y0, mpz_t d, mpz_t n, mpz_t factor, uint64_t u){

 //Restrição
 if(u==0 || (u*u)==1){
  u=rand()%10000;
  u=(u*u*u)%10000;
 }

  //Variáveis locais
  mpz_t v1, v2, v3, v4, u0, one;

  //Inicializando variáveis
  mpz_init(v1); mpz_init(v2); mpz_init(v3); mpz_init(v4); mpz_init(u0); mpz_init(one);


  //Procedimentos
    //Ajuste de variáveis
    mpz_set_ui(u0, u); mpz_set_ui(one, 1);
    mpz_set_ui(v1, 1); mpz_set_ui(v2, 1); mpz_set_ui(v3, 1); mpz_set_ui(v4, 1);

    //Cálculos dos parâmetros de uma curva e de um ponto na curva
    reset:
    mpz_set(v1, u0); mpz_mul(v1, v1, u0); mpz_sub(v1, v1, one); mpz_mod(v1, v1, n);//v1=(u²-1) mod n
    mpz_mul(v2, v2, u0); mpz_mul(v2, v2, u0); mpz_add(v2, v2, one); mpz_mod(v2, v2, n);//v2=(u²+1) mod n     

    if(mpz_invert(v3, v2, n)==0){
      mpz_gcd(factor, v2, n); //Fator primo encontrado
      goto memory_cache_cleaning;
    };//v3 =(u²+1)⁻¹ mod n 
    mpz_mul(x0, v1, v3); mpz_mod(x0, x0, n); //x0=(u²-1)/(u²+1) em Z/nZ


    mpz_set(v1, u0); mpz_sub(v1, v1, one); mpz_powm_ui(v2, v1, 2, n); //v2=(u-1)² mod n
    mpz_mul(y0, v2, v3); mpz_mod(y0, y0, n); mpz_sub(y0, n, y0); //y0=-(u-1)²/(u²+1) em Z/nZ


    mpz_pow_ui(v1, u0, 2); mpz_add(v1, v1, one); mpz_pow_ui(v1, v1, 3); //v1=(u²+1)³
    mpz_pow_ui(v2, u0, 2); mpz_sub(v2, v2, u0);  mpz_sub(v2, v2, u0); mpz_sub(v2, v2, u0); mpz_sub(v2, v2, u0);  mpz_add(v2, v2, one);;//v2=(u²-4u+1)
    mpz_mul(v3, v1, v2); mpz_mod(v3, v3, n);//v3=(u²+1)³(u²-4u+1) mod n
  
    mpz_set(v1, u0); mpz_sub(v1, v1, one); mpz_pow_ui(v4, v1, 6);//v4=(u-1)⁶
    mpz_set(v2, u0); mpz_add(v2, v2, one);//v2=(u+1)
    mpz_mul(v4, v4, v2); mpz_mul(v4, v4, v2); mpz_mod(v4, v4, n);//v4=(u-1)⁶(u+1)² mod n

    if(mpz_invert(v1, v4, n)==0){
      mpz_gcd(factor, v4, n);  //Fator primo encontrado
      goto memory_cache_cleaning;
    };//v1 = [(u-1)⁶(u+1)²]⁻¹ mod n 
    mpz_mul(d, v3, v1); mpz_mod(d, d, n);//d=(u²+1)³(u²-4u+1)/(u-1)⁶(u+1)² em Z/nZ


    if(mpz_cmp_ui(d,0)==0 || mpz_cmp_ui(d,1)==0 || mpz_jacobi(d, n)==1){
      u=rand()%10000;
      u=(u*u*u)%10000;
      mpz_set_ui(u0, u);
      goto reset;
    }
    

    //Limpando o cachê de memória
    memory_cache_cleaning: 
    mpz_clear(v1); mpz_clear(v2); mpz_clear(v3); mpz_clear(v4); mpz_clear(u0); mpz_clear(one);

};


//Função que implementa rotina para adição de pontos em uma curva de Edwards P+Q->R (fórmula válida para a duplicação)
void pointwise_addition(mpz_t xr, mpz_t yr, mpz_t xp, mpz_t yp, mpz_t xq, mpz_t yq, mpz_t d, mpz_t n, mpz_t factor){

  //Variáveis locais
  mpz_t den1, den2, num1, num2, one, temp, inv;

  //Inicializando variáveis
  mpz_init(den1); mpz_init(den2); mpz_init(num1); mpz_init(num2); mpz_init(one); mpz_init(temp); mpz_init(inv);


  //Procedimentos
    //Ajuste de variáveis
    mpz_set_ui(den1, 1); mpz_set_ui(den2, 1); mpz_set_ui(num1, 1); mpz_set_ui(num2, 1);
    mpz_set_ui(one, 1); mpz_set_ui(temp, 1); mpz_set_ui(inv, 1);


    //Cálculando as variáveis intermediárias usadas no cálculo
    mpz_set(temp, d); mpz_mul(temp, temp, xp); mpz_mul(temp, temp, yp); mpz_mul(temp, temp, xq); mpz_mul(temp, temp, yq);
    mpz_mod(temp, temp, n); 

    mpz_add(den1, temp, one); mpz_mod(den1, den1, n); //den1=(1+dxpypxqyq)
    mpz_sub(den2, one, temp); mpz_mod(den2, den2, n); //den2=(1-dxpypxqyq)


    mpz_mul(num1, xp, yq); mpz_mul(temp, xq, yp); mpz_add(num1, num1, temp); mpz_mod(num1, num1, n);// num1 =(xpyq+xqyp) mod n
    mpz_mul(num2, yp, yq); mpz_mul(temp, xq, xp); mpz_sub(num2, num2, temp);  mpz_mod(num1, num1, n);//num2 = (ypyq-xpxq) mod n

    //Cálculo coordenadas do ponto resultante
    if(mpz_invert(temp, den1, n)==0){
      mpz_gcd(factor, den1, n); //Fator primo encontrado
      goto memory_cache_cleaning;
    };
  
    mpz_mul(xr, num1, temp); mpz_mod(xr, xr, n);//xr=(xpyq+xqyp)/(1+dxpypxqyq) em Z/nZ

    if(mpz_invert(temp, den2, n)==0){
      mpz_gcd(factor, den2, n); //Fator primo encontrado
      goto memory_cache_cleaning;
    };
  
    mpz_mul(yr, num2, temp); mpz_mod(yr, yr, n);//yr=(ypyq-axpxq)/(1-dxpypxqyq) em Z/nZ

    

    //Limpando o cachê de memória
    memory_cache_cleaning: 
    mpz_clear(den1); mpz_clear(den2); mpz_clear(num1); mpz_clear(num2);
    mpz_clear(one); mpz_clear(temp); mpz_clear(inv);

};


//Função que calcula múltiplos escalares de um ponto em  uma curva de Edwards P->[k]P
void point_scalar_multiplication(mpz_t xr, mpz_t yr, mpz_t x0, mpz_t y0, mpz_t d, mpz_t n, mpz_t factor, uint64_t k){

  //Variáveis locais
  mpz_t Qx, Qy;

  //Inicializando variáveis
  mpz_init(Qx); mpz_init(Qy); 

  //Procedimentos
    //Ajuste de variáveis
    mpz_set(Qx, x0); mpz_set(Qy, y0);
    mpz_set_ui(xr, 0); mpz_set_ui(yr, 1);//(0,1) é o elemento identidade

    //Loop principal: iterando sobre os bits do escalar
    while(k>0){

      //Iterando sobre os bits do expoente
      if((k&1)){
        pointwise_addition(xr, yr, xr, yr, Qx, Qy, d, n, factor);
        if(mpz_cmp(factor, n)<0 && mpz_cmp_ui(factor, 1)>0)
          goto memory_cache_cleaning; //Fator primo encontrado
      }

      //Atualizando variáveis para a próxima iteração
      k>>=1;
      pointwise_addition(Qx, Qy, Qx, Qy, Qx, Qy, d, n, factor);
      if(mpz_cmp(factor, n)<0 && mpz_cmp_ui(factor, 1)>0)
        goto memory_cache_cleaning; //Fator primo encontrado

    };

    //Limpando o cachê de memória
    memory_cache_cleaning: 
    mpz_clear(Qx); mpz_clear(Qy);

};

//***************************************************************************************************************************
//FIM DO HEADER
#endif
