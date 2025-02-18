//VAMOS CRIAR UM PROGRAMA QUE CRIA ROTINAS PARA SE TRABALHAR COM A REPRESENTAÇÃO EM SÉRIES-Q DA FUNÇÃO DE EULER Φ(q)


/*

A FUNÇÃO DE EULER Φ(q) É DEFINIDA FORMALMENTE PELA SÉRIE-Q Φ(q)=Π(1-q^n), COM n=1,2,...
A SÉRIE-Q CONVERGE PARA |q|<1.

O CHAMADO TEOREMA DOS NÚMEROS PENTAGONAIS AFIRMA QUE O PRODUTÓRIO ACIMA OBEDECE A RELAÇÃO
Φ(q)=Π(1-q^n)=Σ{(-1)^k}{q^[(3k²-k)/2]}, COM k =..., -2,-1,0,1,2,... ONDE g(n)=(3n²-n)/2,
COM n=1,-1, 2,-2,...; SÃO OS CHAMADOS NÚMEROS PENTAGONAIS GENERALIZADOS.

A FUNÇÃO DE EULER É DE GRANDE INTERESSE EM PROBLEMAS DE ANÁLISE COMBINATÓRIA E TEORIA DOS
NÚMEROS. VÁRIAS IDENTIDADES IMPORTANTES RELACIONAM A EXPANSÃO DOS COEFICIENTES DE Φ(q) E
FUNÇÕES ARITMÉTICAS COMO A FUNÇÃO PARTIÇÃO p(n) E A FUNÇÃO DE SOMAS DE DIVISORES σ(n) EM
PARTICULAR:

p(n) = Σ {-sgn(gk)}p(n-gk), ONDE sgn(gk)=1 SE gk>0 E sgn(gk)= (-1) SE gk<0 E A SOMA É FEITA
PARA TODOS OS VALORES DE k TAIS QUE n-gk>0.

ln(Φ(q))= Σ (1/n) {q^n/(1-(q^n))} = -Σ{σ(n)/n} q^n, n=1,2,3,....

PARA q=e^{2πiτ}, Φ(q)=e^{-πiτ/12}η(τ), ONDE η(τ) É A FUNÇÃO ETA DE DEDEKIND.



PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Euler_function
                          https://en.wikipedia.org/wiki/Pentagonal_number_theorem


*/


//******************************************************************************************
//CABEÇALHO
#ifndef EULER_FUNCTION_QSERIES_H
#define EULER_FUNCTION_QSERIES_H
#include"sparse_polynomials.h"



//******************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
polynomial<T> compute_euler_function_qseries(int64_t);

template<typename T, typename U>
std::vector<U> compute_generalized_pentagonal_numbers(polynomial<T>&);

template<typename T, typename U>
std::vector<U> compute_integer_partition_function(std::vector<T>&, int64_t);


//******************************************************************************************
//FUNÇÕES
//Função que computa uma aproximação da expansão formal em série q da função de Euler Φ(q)
template<typename T>
polynomial<T> compute_euler_function_qseries(int64_t n){

  //Variáveis locais
  polynomial<T> euler_qseries;
  univariate_monomial<T> q_term;


  //Procedimentos
    //Adicionando o 1º termo (1-q)
    q_term.coefficient=1;  q_term.power=0;
    euler_qseries.monomials.insert({q_term.power, q_term});
    q_term.coefficient=(-1);  q_term.power=1;
    euler_qseries.monomials.insert({q_term.power, q_term});

    //Adicionando os demais termos
    for(int64_t i=2; i<=n;  ++i){

      polynomial<T> q_partial;

      q_term.coefficient=1;  q_term.power=0;
      q_partial.monomials.insert({q_term.power, q_term});
      q_term.coefficient=(-1);  q_term.power=i;
      q_partial.monomials.insert({q_term.power, q_term});

      euler_qseries=q_partial*euler_qseries;

      //Removendo os termos de expoentes elevados
      if(euler_qseries.degree()>(n<<1)){
        for(auto it=euler_qseries.monomials.begin(); it!=euler_qseries.monomials.end();){
          if((it->first)>n)
            it = euler_qseries.monomials.erase(it);
          else break;
        }

      };

    };

    //Removendo os termos de expoentes elevados
    for(auto it=euler_qseries.monomials.begin(); it!=euler_qseries.monomials.end();){
      if((it->first)>n) it = euler_qseries.monomials.erase(it);
      else break;
    }



  //Resultado
  return euler_qseries;

};


//Calculando os números pentagonais generalizados usando a expansão formal da série q da função de Euler
template<typename T, typename U>
std::vector<U> compute_generalized_pentagonal_numbers(polynomial<T>& euler_qseries){

  //Variáveis locais
  std::vector<U> gk_vector;
  
  //Procedimentos
    //Loop sobre os coeficientes da série formal da função de Euler
    for(auto it=euler_qseries.monomials.begin(); it!=euler_qseries.monomials.end(); ++it){
      U gk=it->second.power;
      signed sign=(it->second.coefficient>0)?1:(-1);
      gk_vector.push_back(gk*sign);
    }

    
  //Resultado
  return gk_vector;

};


//Função que computa a função de partição p(n) usando os números pentagonais generalizados
template<typename T, typename U>
std::vector<U> compute_integer_partition_function(std::vector<T>& gk_vector,  int64_t n){

  //Variáveis locais
  std::vector<U> pn_vector;


  //Procedimentos
    //Adicionando os primeiros termo da lista
    pn_vector.push_back(1); //p(0)=1
    pn_vector.push_back(1); //p(1)=1


    //Loop principal
    for(int64_t i=2;  i<n; ++i){
    
      U pn=0;
      for(int64_t j=(gk_vector.size()-2); j>=0; --j){
        
        T abs_gk=gk_vector[j]; 
        if(abs_gk<0) abs_gk=abs_gk*(-1);

        T index=(i-abs_gk);
        signed minus_sgn=(gk_vector[j]<0)?1:(-1);

        if(index<0) break;
        else pn=pn+ (pn_vector[index]*minus_sgn);          

      };
    
      pn_vector.push_back(pn);

    };//Fim do loop principal


  //Resultado
  return pn_vector;

};


//******************************************************************************************
//FIM DO HEADER
#endif
