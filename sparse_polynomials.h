//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA CLASSE DE POLINÔMIOS ESPARSOS

/*
POLINÔMIOS ESPARSOS SÃO POLINÔMIOS QUE CONTÉM MUITOS MONÔMIOS COM COEFICIENTES
NULOS. NESSE CASO EM PARTICULAR É MAIS COVENIENTE ESTOCAR APENAS AS POETÊNCIAS
E OS COEFICIENTES DOS TERMOS NÃO NULOS. OS MONÔMIOS SERÃO ALOCADOS EM ORDEM
DESCRESENTE DE ACORDO COM SEUS EXPOENTES

*/

//*******************************************************************************
//CABEÇALHO
#ifndef SPARSE_POLYNOMIAL_H
#define SPARSE_POLYNOMIAL_H
#include"univariate_monomial_class.h"
#include<map>
#include<functional>


//*******************************************************************************
//CLASSE DE POLINÔMIOS ESPARSOS
template<typename T>
class polynomial{
  public:

  //Membros da classe
  std::map<int64_t, univariate_monomial<T>, std::greater<int64_t>> monomials;

  //Construtores e destruidores
  polynomial(){ };
  virtual ~polynomial(){ };

  //Métodos da classe
    //Funções básicas
    void setup();
    void remove_null_terms();
    int64_t degree();
    std::string algebraic();

    //Operações aritméticas
    polynomial<T> operator=(const polynomial<T>&);
    polynomial<T> operator+(polynomial<T>&);
    polynomial<T> operator-(polynomial<T>&);
    polynomial<T> operator*(polynomial<T>&);
    polynomial<T> operator/(polynomial<T>&);


};


//*******************************************************************************
//MÉTODOS DA CLASSE
  //Funções básicas

//Função que define manualmente os monômios de uma classe de polinômios
/*
NOTA: os monômios podem ser definidos diretamente usando a classe de monômios
e inseridos no container principal da classe.
*/
template<typename T>
void polynomial<T>::setup(){

  //Variáveis locais
  univariate_monomial<T> element;
  int64_t k, n;

  //Procedimentos
    //Recebendo input do usuário
    std::cout<<"Número de monômios do polinômio: ";
    std::cin>> n;

    //Definindo os termos do polinômio
    for(int64_t i=0; i<n; ++i){
      element.set();
      monomials.insert({element.power, element});
    }
  
    //Removendo termos de coeficients nulos
    remove_null_terms();
};


//Função que remove termos com coeficientes nulos
template<typename T>
void polynomial<T>::remove_null_terms(){

  //Procedimentos: loop sobre os termos
  for(auto it=monomials.begin(); it!=monomials.end();){
    if(it->second.coefficient == 0)
      it = monomials.erase(it);
    else  ++it;
  }

};


//Função que retorna o grau de um polinômio
template<typename T>
int64_t polynomial<T>::degree(){

  //Caso base 
  if(monomials.size()==0) return 0;

  //Variáveis locais
  auto it=monomials.begin();

  //Resultado
  return it->second.power;

};


//Função que escreve um polinômio como uma string 
template<typename T>
std::string polynomial<T>::algebraic(){

  //Variáveis locais
  std::string polynomial_string="";
  auto it=monomials.begin();

  //Procedimentos
    //Caso base:
    if(monomials.size()==0){
      polynomial_string=" ";
      return polynomial_string;
    }

    //1º elemento
    polynomial_string+=it->second.algebraic();
    ++it;

    //Demais elementos
    for(; it!=monomials.end(); ++it){
      if(it->second.coefficient==0) continue;
      if(it->second.coefficient>0) polynomial_string+="+";
      polynomial_string+=it->second.algebraic();
    }

  //Resultado
  return polynomial_string;

};

  //Funções que implementam aritmética de polinômios

//Cópia (copy constructor)
template <typename T>
polynomial<T> polynomial<T>::operator=(const polynomial<T>& p2) {
  // Condição que checa a não igualdade dos polinômios
  if (this != &p2) {

    // Ajuste do array de monômios
    this->monomials = p2.monomials;

  };

  // Resultado
  return *this;
};

//Adição
template<typename T>
polynomial<T> polynomial<T>::operator+(polynomial<T>& p1){

  //Caso base
  if(p1.monomials.size()==0){
    polynomial<T> result=*this;
    return result;
  }

  if(this->monomials.size()==0){
    polynomial<T> result=p1;
    return result;
  }

  //Variáveis locais
  polynomial<T> result=p1;


  //Procedimentos
    //Iterando sobre os monômios do primeiro termo
    for(auto it=monomials.begin(); it!=monomials.end(); ++it){

      //Definindo um termo
      univariate_monomial<T> element=it->second;
      int64_t key=element.power;

      //Busca por monômios com o mesmo grau
      auto found=result.monomials.find(key);

      //Caso haja um termo com o mesmo grau os coeficientes são adicionados
      if(found != result.monomials.end())
        found->second.coefficient=found->second.coefficient+element.coefficient;
      else result.monomials.insert({key, element});
 
    }

    //Ajuste do resultado final
    result.remove_null_terms();

  //Resultados
  return result;


};


//Subtração
template<typename T>
polynomial<T> polynomial<T>::operator-(polynomial<T>& p1){


  //Caso base
  if(p1.monomials.size()==0){
    polynomial<T> result=*this;
    return result;
  }

  //Variáveis locais
  polynomial<T> result=*this;


  //Procedimentos
    //Iterando sobre os monômios do segundo termo
    for(auto it=p1.monomials.begin(); it!=p1.monomials.end(); ++it){

      //Definindo um termo
      univariate_monomial<T> element=it->second;
      int64_t key=element.power;

      //Busca por monômios com o mesmo grau
      auto found=result.monomials.find(key);

      //Caso haja um termo com o mesmo grau os coeficientes são adicionados
      if(found != result.monomials.end())
        found->second.coefficient=found->second.coefficient-element.coefficient;
      else{
        element.coefficient=element.coefficient*(-1);//Invertendo o sinal do coefficiente
        result.monomials.insert({key, element});
          }
 
    }

    //Ajuste do resultado final
    result.remove_null_terms();

  //Resultados
  return result;


};

//Multiplicação
template<typename T>
polynomial<T> polynomial<T>::operator*(polynomial<T>& p1){

  //Caso base
  if(this->monomials.size()==0 || p1.monomials.size()==0){
    polynomial<T> result;
    return result;
  }

  //Variáveis locais
  polynomial<T> result;
  T new_coefficient;
  int64_t new_power;
  

  //Procedimentos
    //Iterando sobre todos os produtos possíveis de monômios de ambos dos polinômios
    for(auto it1=this->monomials.begin(); it1!=this->monomials.end(); ++it1){
      for(auto it2=p1.monomials.begin(); it2!=p1.monomials.end(); ++it2){

        //Calculando os coeficientes e potências dos novos termos
        new_coefficient=it1->second.coefficient*it2->second.coefficient;
        new_power=it1->second.power+it2->second.power;

        //Checando se há algum termo no produto com o mesmo expoente
        auto found=result.monomials.find(new_power);

        if(found != result.monomials.end())
          found->second.coefficient+=new_coefficient;
        else{
          univariate_monomial<T> product_monomial(new_coefficient, new_power);
          result.monomials.insert({new_power, product_monomial});
        }        
     


      }

    }

    //Ajuste do resultado final
    result.remove_null_terms();

  //Resultados
  return result;

};


// Divisão de polinômios
template<typename T>
polynomial<T> polynomial<T>::operator/(polynomial<T>& p1){

  //Restrição
  assert(this->degree() >= p1.degree() && p1.monomials.size() > 0);

  // Caso base: o dividendo é um polinômio nulo
  if (this->monomials.size() == 0) {
    polynomial<T> result;
    return result;
  }

  //Variáveis locais
  polynomial<T> dividend_polynomial = *this;
  polynomial<T> result;


  //Procedimentos
    // Loop sobre os monômios do dividendo
    while (dividend_polynomial.degree() >= p1.degree()) {

        //Cálculos dos termos de maior coefficientes
        auto lead_term_dividend = dividend_polynomial.monomials.begin();
        auto lead_term_divisor = p1.monomials.begin();

        //Cálculo do termo (monômio do quociente)
        T coeff_ratio = lead_term_dividend->second.coefficient / lead_term_divisor->second.coefficient;
        int64_t power_ratio = lead_term_dividend->second.power - lead_term_divisor->second.power;

        univariate_monomial<T> quotient_monomial(coeff_ratio, power_ratio);
        result.monomials.insert({power_ratio, quotient_monomial});

        //Atualizando o dividendo
        polynomial<T> multiplier;
        multiplier.monomials[power_ratio] = quotient_monomial;
        polynomial<T> reducer = multiplier * p1;
        dividend_polynomial = dividend_polynomial - reducer;

        // Remove termos com coeficientes nulos
        dividend_polynomial.remove_null_terms();
    }

    // Ajuste do resultado final
    result.remove_null_terms();

  //Resultado
  return result;

}

//*******************************************************************************
//DECLARAÇÃO DE FUNÇÕES AUXLIARES
template<typename T>
polynomial<T> remainder(polynomial<T>&, polynomial<T>&);

template<typename T, typename U>
polynomial<T> polynomial_mod(polynomial<T>&, U);

template<typename T, typename U>
U polynomial_evaluation(polynomial<T>&, U);

template<typename T, typename U>
U modular_polynomial_evaluation(polynomial<T>&, U, U);


//*******************************************************************************
//FUNÇÕES AUXLIARES
//Função que calcula o resto da divisão de dois polinômios
template<typename T>
polynomial<T> remainder(polynomial<T>& p1, polynomial<T>& p2){

  //Restrição:
  assert(p2.monomials.size()>0 && p1.monomials.size()>0);
  assert(p1.degree()>= p2.degree());

  //Variáveis locais
  polynomial<T> quotient=p1/p2;
  polynomial<T> reducer=quotient*p2;
  polynomial<T> result=p1-reducer;

  //Procedimentos
    //Ajuste do resultado final
    result.remove_null_terms();

  //Resultado
  return result;

};


//Função que reduz os coeficientes de um polinômio a menos de uma relação de congruência
template<typename T, typename U>
polynomial<T> polynomial_mod(polynomial<T>& p1, U modulus){

  //Restrição
  static_assert(std::is_integral<T>::value, "Expoentes devem ser inteiros");
  static_assert(std::is_integral<U>::value, "Coeficientes devem ser inteiros");

  //Variáveis locais
  polynomial<T> result;


  //Procedimentos
    //Loop sobre os monômios do polinômio
    for(auto it=p1.monomials.begin(); it!=p1.monomials.end(); ++it){
  
      int64_t key=it->first;
      univariate_monomial<T> temp=it->second;

      univariate_monomial<T> new_monomial=univariate_monomial_mod<T, U>(temp, modulus);
      result.monomials[key]=new_monomial;
      
    }
   

    //Ajuste do resultado final
    result.remove_null_terms();

  //Resultado
  return result;
  
};


//Função que calcula o valor de um polinômio
template<typename T, typename U>
U polynomial_evaluation(polynomial<T>& p1, U arg){

  //Variáveis locais
  U result=0;

  //Procedimentos
    //Loop sobre os monômios do polinômio
    for(auto it=p1.monomials.begin(); it!=p1.monomials.end(); ++it)
      result=result+univariate_monomial_valuation<T,U>(it->second, arg);


  //Resultado
  return result;
  
};

//Função que calcula o valor de um polinômio a menos de uma relação de congruência
template<typename T, typename U>
U modular_polynomial_evaluation(polynomial<T>& p1, U arg, U modulus){
  //Restrição
  static_assert(std::is_integral<U>::value, "Coeficientes devem ser inteiros");

  //Variáveis locais
  U result=0;

  //Procedimentos
    //Loop sobre os monômios do polinômio
    for(auto it=p1.monomials.begin(); it!=p1.monomials.end(); ++it){
      result=result+modular_univariate_monomial_valuation<T,U>(it->second, arg, modulus);
      result%=modulus;
    }

  //Resultado
  return (result%modulus);
  
};
 

//*******************************************************************************
//FIM DO HEADER
#endif

