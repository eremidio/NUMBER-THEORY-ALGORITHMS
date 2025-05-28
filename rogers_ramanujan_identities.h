//VAMOS CRIAR UM PROGRAMA QUE COMPUTA EXPANSÕES DAS IDENTIDADES ORIGINAIS DE ROGER-RAMANUJAN

/*

AS IDENTIDADES DE ROGER-RAMANUJAN SÃO UM CONJUNTO DE IDENTIDADES ENVOLVENDO SÉRIES-Q QUE POSSUEM UMA INTERPRETAÇÃO
COMBINATÓRIA EM TERMOS DE PARTIÇÕES QUE SATISFAZEM UM CONJUNTO DE RELAÇÕES DE CONGRUÊNCIA. 

DEFININDO AS FUNÇÕES G(q) E H(q) RESPECTIVAMENTE PELAS IDENTIDADES G(q)= Σ{q^n²}/(q; q)(n) e
H(q)= Σ{q^(n²+n)}/(q; q)(n), ONDE (q; q)(n) DENOTA OS SÍMBOLOS DE Q-POCHHAMMER AS IDENTIDADES DE ROGER-RAMANUJAN 
SÃO ESCRITAS COMO: G(q)=1/{(q; q^5)(∞)(q^4; q^5)(∞)} E H(q)=1/{(q^2; q^5)(∞)(q^3; q^5)(∞)}.

DO PONTO DE VISTA COMBINATÓRIO, AS DUAS FÓRMULAS PARA AS FUNÇÕES H(q) E G(q) IMPLICAM OS SEGUINTES TEOREMAS: O
NÚMERO DE PARTIÇÕES DE UM INTEIRO EM QUE CADA PARCELA DIFERE POR NO MÍNIMO 2 É IGUAL AO NÚMERO DE PARTIÇÕES CUJOS
TERMOS SÃO CONGRUENTES A 1,4 (mod 5). O NÚMERO DE PARTIÇÕES DE UM INTEIRO EM QUE CADA PARCELA DIFERE POR NO
MÍNIMO 2 E QUE NÃO CONTÉM 1'S É IGUAL AO NÚMERO DE PARTIÇÕES CUJOS TERMOS SÃO CONGRUENTES A 2,3 (mod 5).

EXISTEM VÁRIAS IDENTIDADES ENVOLVENDO SÉRIES-Q SIMILARES AS IDENTIDADES DE ROGER-RAMANUJAN QUE POSSUEM
INTERPRETAÇÕES COMBINATÓRIA EM TERMOS DE PARTIÇÕES QUE SATISFAZEM UM CONJUNTO DE RELAÇÕES DE CONGRUÊNCIA. UMA LISTA
COMPLETA DE TAIS IDENTIDADES ESTÁ DISPONÍVEL EM:
            https://londmathsoc.onlinelibrary.wiley.com/doi/epdf/10.1112/plms/s2-54.2.147


A FRAÇÃO CONTINUADA DE ROGERS-RAMANUJAN É DEFINIDA PELA RELAÇÃO
R(q)={q^(1/5)}____1____
                1  +____q____  
                       1 +____q²___     
                               1  + ___q³____   
                                       1+ ... 

TAL FUNÇÃO SATISFAZ UM CONJUNTO DE EQUAÇÕES MODULARES (O FATOR q^(1/5) É NECESSÁRIO POR ESTA RAZÃO) PARA VALORES
ESPECÍFICOS DE q, ALÉM DISSO PARA VALORES DO TIPO e^{-πn} COM n É POSSÍVEL MOSTRAR QUE R(q) É UM NÚMERO ALGÉBRICO
(TAIS VALORES PODEM SER EXPRESSOS EM TERMOS DA FUNÇÃO NOME q=e^{iπτ}, PARA τ COMPLEXO COM PARTE REAL NULA).
A FUNÇÃO R(q) APARECE EM CERTOS MODELOS DE FÍSICA ESTATÍSTICA, NA SOLUÇÃO FECHADA DE CERTOS TIPOS DE EQUAÇÃO
DE 5º GRAU, ENTRE OUTROS CONTEXTOS ESPECÍFICOS.


AS FUNÇÕES G(q) E H(q) ESTÃO RELACIONADAS A FUNÇÃO R(q) POR MEIO DA IDENTIDADE: R(q)={q^(1/5)}{H(q)/G(q)}.


PARA MAIORES INFORMAÇÕES: Number Theory in the Spirit of Ramanujan by Bruce C. Berndt
                          https://en.wikipedia.org/wiki/Rogers–Ramanujan_continued_fraction#Examples_of_R(q)
                          https://en.wikipedia.org/wiki/Rogers–Ramanujan_identities#Combinatorial_interpretation
                          https://mathworld.wolfram.com/Rogers-RamanujanContinuedFraction.html
                          https://mathworld.wolfram.com/Rogers-RamanujanIdentities.html
                          https://en.wikipedia.org/wiki/Hypergeometric_function


*/



//******************************************************************************************************************************
//CABEÇALHO
#ifndef ROGER_RAMANUJAN_IDENTITIES_H
#define ROGER_RAMANUJAN_IDENTITIES_H
#include"generalized_q_pochhammer_symbol.h"


//******************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
polynomial<T> compute_partial_denominator(int64_t, int64_t, int64_t);

template<typename T>
polynomial<T> compute_rogers_ramanujan_g_function(int64_t);

template<typename T>
polynomial<T> compute_rogers_ramanujan_h_function(int64_t);


//******************************************************************************************************************************
//FUNÇÕES
//Função que computa uma expansão paricial do denominador para a funções de Rogers-Ramanujan
template<typename T>
polynomial<T> compute_partial_denominator(int64_t n, int64_t m, int64_t k){

  //Variáveis locais
  polynomial<T> roger_ramanujan_temp=compute_q_pochhammer_symbol_infinite<T>(n, m, k, 1, 1);
  polynomial<T> roger_ramanujan_partial;
  univariate_monomial<T> poly_term;
  
  //Procedimentos
    //Ajuste do resultado
    for(auto it=roger_ramanujan_temp.monomials.begin(); it!=roger_ramanujan_temp.monomials.end(); ++it){
      if((it->first)>0){
        poly_term.coefficient=(it->second.coefficient)*(-1);
        poly_term.power=(it->second.power);
        roger_ramanujan_partial.monomials.insert({poly_term.power, poly_term});
      } 
      
    }

  //Resultado
  return roger_ramanujan_partial;


};


//Função que computa a função G(q)
template<typename T>
polynomial<T> compute_rogers_ramanujan_g_function(int64_t k){


  //Variáveis locais
  polynomial<T> q_15_den=compute_partial_denominator<T>(1,5, k);
  polynomial<T> q_45_den=compute_partial_denominator<T>(4,5, k);
  polynomial<T> g_function, g45, g15, mul1=q_15_den, mul4=q_45_den;
  univariate_monomial<T> g_term;

  
  //Procedimentos
    //Adicionando o primeiro termo a série
    g_term.coefficient=1; g_term.power=0;
    g15.monomials.insert({g_term.power, g_term});
    g45.monomials.insert({g_term.power, g_term});
    g15=g15+q_15_den;
    g45=g45+q_45_den;
        

    //Loop principal: adicionando os demais termos da série
    for(int64_t i=0; i<k; i++){

      q_15_den=q_15_den*mul1;
      q_45_den=q_45_den*mul4;

      //Removendo os termos de expoentes elevados
      if(q_15_den.degree()>(k<<1)){
        for(auto it=q_15_den.monomials.begin(); it!=q_15_den.monomials.end();){
          if((it->first)>k)
            it = q_15_den.monomials.erase(it);
          else break;
        }

      };

      //Removendo os termos de expoentes elevados
      if(q_45_den.degree()>(k<<1)){
        for(auto it=q_45_den.monomials.begin(); it!=q_45_den.monomials.end();){
          if((it->first)>k)
            it = q_45_den.monomials.erase(it);
          else break;
        }

      };

      //Adicionando os termos
      g15=g15+q_15_den;
      g45=g45+q_45_den;



    };//Fim do loop principal


    //Cálculo final do resultado
    g_function=g15*g45;
    for(auto it=g_function.monomials.begin(); it!=g_function.monomials.end();){
      if((it->first)>k)
        it = g_function.monomials.erase(it);
      else break;
    }


  //Resultado
  return g_function;


};



//Função que computa a função H(q)
template<typename T>
polynomial<T> compute_rogers_ramanujan_h_function(int64_t k){


  //Variáveis locais
  polynomial<T> q_25_den=compute_partial_denominator<T>(2,5, k);
  polynomial<T> q_35_den=compute_partial_denominator<T>(3,5, k);
  polynomial<T> h_function, h25, h35, mul2=q_25_den, mul3=q_35_den;
  univariate_monomial<T> h_term;

  
  //Procedimentos
    //Adicionando o primeiro termo a série
    h_term.coefficient=1; h_term.power=0;
    h25.monomials.insert({h_term.power, h_term});
    h35.monomials.insert({h_term.power, h_term});
    h25=h25+q_25_den;
    h35=h35+q_35_den;
        

    //Loop principal: adicionando os demais termos da série
    for(int64_t i=0; i<k; i++){

      q_25_den=q_25_den*mul2;
      q_35_den=q_35_den*mul3;

      //Removendo os termos de expoentes elevados
      if(q_25_den.degree()>(k<<1)){
        for(auto it=q_25_den.monomials.begin(); it!=q_25_den.monomials.end();){
          if((it->first)>k)
            it = q_25_den.monomials.erase(it);
          else break;
        }

      };

      //Removendo os termos de expoentes elevados
      if(q_35_den.degree()>(k<<1)){
        for(auto it=q_35_den.monomials.begin(); it!=q_35_den.monomials.end();){
          if((it->first)>k)
            it = q_35_den.monomials.erase(it);
          else break;
        }

      };

      //Adicionando os termos
      h25=h25+q_25_den;
      h35=h35+q_35_den;
        


    };//Fim do loop principal


    //Cálculo final do resultado
    h_function=h25*h35;
    for(auto it=h_function.monomials.begin(); it!=h_function.monomials.end();){
      if((it->first)>k)
        it = h_function.monomials.erase(it);
      else break;
    }


  //Resultado
  return h_function;


};


//******************************************************************************************************************************
//FIM DO HEADER
#endif
