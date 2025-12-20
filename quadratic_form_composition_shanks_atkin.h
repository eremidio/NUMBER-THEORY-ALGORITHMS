//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A COMPOSIÇÃO DE FORMAS QUADRÁTICAS BINÁRIAS USANDO O ALGORITMO DE SHANKS-ATKIN

/*

O ALGORITMO DE SHANKS-ATKINS PARA COMPUTAR A COMPOSIÇÃO DE FORMAS QUADRÁTICAS BINÁRIAS DE DISCRIMINANTE D. ESTE ALGOPRITMO É UMA
REELABORAÇÃO DO MÉTODO DE GAUSS QUE É MUITO MAIS EFICIENTE E QUE TEM A VANTAGEM DE TRABALHAR COM TERMOS DA ORDEM √|D| EVITANDO
OVERFLOW DE COEFICIENTES.

PARA MAIORES INFORMAÇÕES: A Course In Computational Algebraic Number Theory by Henri Cohen

*/


//**********************************************************************************************************************************************
//CABEÇALHO
#ifndef BINARY_QUADRATIC_FORMS_COMPOSITION_SHANKS_ATKIN_H
#define BINARY_QUADRATIC_FORMS_COMPOSITION_SHANKS_ATKIN_H
#include "quadratic_form_composition.h"


//**********************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
struct binary_quadratic_form generate_unity_form(int64_t); 
int64_t compute_L_const(int64_t);
struct binary_quadratic_form NUDUPL(struct binary_quadratic_form); 
struct binary_quadratic_form NUCOMP(struct binary_quadratic_form, struct binary_quadratic_form); 
struct binary_quadratic_form quadratic_form_exponentiation_fast(struct binary_quadratic_form, int64_t);


//**********************************************************************************************************************************************
//FUNÇÕES
//Função que gera uma unidade no grupo cl(D) de forma quadráticas de discriminante negativo
struct binary_quadratic_form generate_unity_form(int64_t D){

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


//Função que computa a constante L =|D|^(1/4)
int64_t compute_L_const(int64_t D){

  //Variáveis locais
  int64_t absD=(D>0)?(D/4):((-D)/4);
  int64_t L=floor(sqrt(absD));

  
  //Resultado
  return L;

};


//Programa que computa o quadrado f² de uma forma quadrática reduzida f(x,y)=ax²+bxy+cy²
struct binary_quadratic_form NUDUPL(struct binary_quadratic_form f){

  //Variáveis locais
  int64_t D = binary_quadratic_form_discriminant(f);
  int64_t L = compute_L_const(D);
  int64_t a=f.a, b=f.b, c=f.c;
  int64_t a2=0, b2=0, c2=0;
  int64_t A=0, B=0, C=0, C1=0;
  int64_t u=0, v=0, d=0, e=0, g=0, q=0, z=0, d1=0, v2=0, v3=0, t2=0, t3=0;
  

  //Procedimentos
    //Redução euclidiana
    extended_euclidean_algorithm(b, a, &d1, &u, &v);
    A=a/d1; B=b/d1; C=(((-c)*u)%A+A)%A; C1=A-C;
    if(C1<C) C=(-C1);

    //---------------------------------------------------------------------------------------
      //SUBALGORITMO PARTEUCL: algoritmo de Euclides extendido parcial

      //Ajuste de variáveis 
      v=0; d=A; v2=1; v3=C; z=0;
 
  
      while(1){
     
        int64_t abs_v3=(v3>0)?v3:(-v3);

        if(abs_v3<=L){
          if((z%2)==1){
            v2=(-v2); v3=(-v3); 
          };
          break;//Fim do subalgoritmo PARTEUCL
        }

        //Redução euclidiana
        t3=d%v3; /*0≲t3<|v3|*/ 
        q=(d-t3)/v3;
        t2=v-q*v2; v=v2; d=v3;
        v2=t2; v3=t3; z++;

      };      

    //---------------------------------------------------------------------------------------

    //Caso especial:
    if(z==0){

      g=(B*v3+c)/d; a2=d*d; c2=v3*v3; b2=b+(d+v3)*(d+v3)-a2-c2;
      c2=c2+g*d1;
      goto final_result;

    };

  
    //Ajuste de variáveis
    e=(c*v+B*d)/A; g=(e*v2-B)/v;
    b2=(e*v2+v*g);

    if(d>d1){
      b2=d1*b2; v=d1*v; v2=d1*v2;
    };

    a2=d*d; c2=v3*v3; b2=b+(d+v3)*(d+v3)-a2-c2;
    a2=a2+e*v; c2=c2+g*v2;


  //Resultado
  final_result:
  struct binary_quadratic_form dupl_f={a2,b2,c2};
  if(is_reduced(dupl_f)==false) dupl_f=reduce_quadratic_form(dupl_f);
  if(dupl_f.a < 0){
    dupl_f.a = -dupl_f.a;
    dupl_f.b = -dupl_f.b;
    dupl_f.c = -dupl_f.c;
  }
  return dupl_f;

}; 


//Função que calcula a composição de duas formas quadráticas
struct binary_quadratic_form NUCOMP(struct binary_quadratic_form f1, struct binary_quadratic_form f2){

  //Variáveis locais
  int64_t D = binary_quadratic_form_discriminant(f1);
  int64_t L = compute_L_const(D);
  int64_t a1=0, b1=0, c1=0;
  int64_t a2=0, b2=0, c2=0;
  int64_t a3=0, b3=0, c3=0;
  int64_t s=0, n=0;
  int64_t A=0, A1=0, B=0, C=0, C1=0;
  int64_t Q1=0, Q2=0, Q3=0, Q4=0;
  int64_t u=0, u1=0, v=0, b=0, d=0, e=0, f=0, g=0, q=0, l=0, z=0, d1=0, v1=0, v2=0, v3=0, t2=0, t3=0;


  //Procedimento
    //Ajuste de variáveis 
    if(f1.a<f2.a){
      struct binary_quadratic_form t=f1;
      f1=f2; f2=t;
    } 

    a1=f1.a, b1=f1.b, c1=f1.c;
    a2=f2.a, b2=f2.b, c2=f2.c;
    s=(b1+b2)/2;
    n=b2-s;

    //Loop euclidiano 1: definição de parâmetros 
    extended_euclidean_algorithm(a2, a1, &d, &u, &v);
    if(d==1){
      A=(-u)*n; d1=d;
      goto partial_reduction_step;
    }
    if(s%d==0 && d!=1){
      A=(-u)*n; d1=d; a1=a1/d1; a2=a2/d1; s=s/d1;
      goto partial_reduction_step;
    }

    //Loop euclidiano 2: definição de parâmetros
    extended_euclidean_algorithm(s, d, &d1, &u1, &v1);
    if(d1>1){
      a1=a1/d1; a2=a2/d1;
      s=s/d1; d=d/d1;
    }

    //Redução inicial
    c1 = (c1 % d + d) % d;  // evita negativos
    c2 = (c2 % d + d) % d;
    l = ((-u1) * (( (u * c1) % d + (v * c2) % d + d ) % d) ) % d; // modulo seguro
    A = (-u)*(n/d) + l*(a1/d); 

    //Redução parcial 
    partial_reduction_step:
    A = (A % a1 + a1) % a1;  // modulo seguro
    A1 = a1 - A;
    if(A1 < A) A = -A1;

    //---------------------------------------------------------------------------------------
      //SUBALGORITMO PARTEUCL: algoritmo de Euclides extendido parcial

      //Ajuste de variáveis 
      v = 0; d = a1; v2 = 1; v3 = A; z = 0;
   
      while(1){
        int64_t abs_v3 = (v3>0)?v3:(-v3);

        if(abs_v3 <= L){
          if((z%2) == 1){
            v2 = -v2; v3 = -v3; 
          }
          break; //Fim do subalgoritmo PARTEUCL
        }

        //Redução euclidiana
        t3 = d % v3; if(t3<0) t3 += abs_v3; /*0≲t3<|v3|*/
        q = (d - t3) / v3;
        t2 = v - q*v2; v = v2; d = v3;
        v2 = t2; v3 = t3; z++;
      }      

    //---------------------------------------------------------------------------------------

    //Caso especial
    if(z==0){
      Q1 = a2*v3; Q2 = Q1 + n;  
      f = Q2 / d; g = (v3*s + c2) / d;
      a3 = d*a2; c3 = v3*f + g*d1;
      b3 = 2*Q1 + b2;
      goto final_result;
    }

    //Ajuste de variáveis
    b = (a2*d + n*v) / a1; 
    Q1 = b*v3; Q2 = Q1 + n;
    f = Q2 / d; 
    e = (s*d + c2*v) / a1; 
    Q3 = e*v2;
    Q4 = Q3 - s; 
    g = Q4 / v;
    if(d1>1){
      v2 = d1*v2; v = d1*v;
    }

    a3 = d*b + e*v;
    c3 = v3*f + g*v2;
    b3 = Q1 + Q2 + d1*(Q3 + Q4);

  //Resultado
  final_result:
  struct binary_quadratic_form comp_f = {a3, b3, c3};
  if(!is_reduced(comp_f)) comp_f = reduce_quadratic_form(comp_f);
  if(comp_f.a < 0){
    comp_f.a = -comp_f.a;
    comp_f.b = -comp_f.b;
    comp_f.c = -comp_f.c;
  }
  return comp_f;
};



//Função que calcula a exponencial de uma forma quadrática reduzida
struct binary_quadratic_form quadratic_form_exponentiation_fast(struct binary_quadratic_form f, int64_t exponent){

  //Variáveis locais
  int64_t D=binary_quadratic_form_discriminant(f);
  struct binary_quadratic_form result=generate_unity_form(D);
  struct binary_quadratic_form q=f;


  //Procedimento
    //Loop sobre os bits do expoente
    while(exponent>0){

      //Checando a paridade do bit atual
      if(exponent&1) result = NUCOMP(result, q);

      //Atualizando variáveis para apróxima iteração
      exponent>>=1;
      q = NUDUPL(q);

    }


  //Resultado
  return result;

};

//**********************************************************************************************************************************************
//FIM DO HEADER
#endif
