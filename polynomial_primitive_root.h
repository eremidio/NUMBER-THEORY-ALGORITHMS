//VAMOS CRIAR UM PROGRAMA QUE COMPUTA RAÍZES PRIMITIVAS EM CORPOS FINITOS DO SEGUNDO TIPO PARA INTEIROS DE 64 BITS

/*

EM CORPOS FINITOS DO SEGUNDO TIPO F(p)[x]/f(x), COM f(x) COM COEFICIENTES EM GF(p) E IRREDUTÍVEL,
p PRIMO E k INTEIRO NÃO NEGATIVO, UM POLINÔMIO É DITO SER UMA RAÍZ PRIMITIVA SE E SOMENTE SE
ELE TIVER ORDEM MULTIPLICATIVA (p^k)-1, ONDE k É O GRAU DE f(x). TAL OBSERVAÇÃO É ÚTIL EM
COMPUTAR RAÍZES PRIMITIVAS EM CORPOS FINITOS.

PARA MAIORES INFORMAÇÕES: Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance
                          https://math.stackexchange.com/questions/1258567/find-primitive-root-for-polynomial-field
                          https://math.stackexchange.com/questions/36583/primitive-root-of-a-finite-field
              

*/ 


//*********************************************************************************************************
//CABEÇALHO
#ifndef POLYNOMIAL_PRIMITIVE_ROOT_H
#define POLYNOMIAL_PRIMITIVE_ROOT_H
#include"polynomial_exponentiation_finite_field.h"
#include"polynomial_irreducibility.h"
#include"polynomial_gcd.h"
#include"polynomial_cast.h"
#include"factorization_map.h"
#include"mod_bin_exponentiation128.h"

//*********************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool is_primitive_root(polynomial<int64_t>&, polynomial<int64_t>&, int64_t);


//*********************************************************************************************************
//FUNÇÕES
//Função que checa se um polinômio é uma raíz primitiva em um corpo finito do segundo tipo
bool is_primitive_root(polynomial<int64_t>& p1, polynomial<int64_t>& field_generator, int64_t field_characteristic){

  //Restrição
  if(irredutibility_criterion<int64_t>(field_generator, field_characteristic)==false){
    std::cout<<"f(x): "<<field_generator.algebraic()<<" não é irredutível em GF("<<field_characteristic<<")\n";
    return false;
  };

  
  //Variáveis locais
  polynomial<__int128_t> u=polynomial_cast<int64_t, __int128_t>(p1), v=polynomial_cast<int64_t, __int128_t>(field_generator);
  polynomial<__int128_t> tester;
  uint64_t prime_factor_array[30];
  int multiplicities[30];
  int64_t group_order=bin_pow(field_characteristic, field_generator.degree);
  int64_t exponent;


  //Procedimentos
    //Inicializando os arrays de fatores primos
    for(int i=0; i<30; ++i){
      prime_factor_array[i]=1;
      multiplicities[i]=0;
    };

    factorization_map((uint64_t)(group_order-1), prime_factor_array, multiplicities);


    //Cálculo da ordem multiplica do elemento a ser testado
      //1ª etapa
      tester=polynomial_powmod_finite_field<__int128_t, int64_t>(u, v, (group_order-1), field_characteristic);
      for(auto& c:tester.polynomial_coefficients){
        if(c<0) c+=field_characteristic;
      }
      tester.adjust_degree();      
      
      if(is_unity_polynomial<__int128_t>(tester)==false) return false;
     

      //2ª etapa
      for(int j=0; j<30; ++j){
    
       if(prime_factor_array[j]<=1) break;//Fim do loop

       exponent=(group_order-1)/prime_factor_array[j]; if(exponent==1) continue;
       tester=polynomial_powmod_finite_field<__int128_t, int64_t>(u, v, exponent, field_characteristic);
       for(auto& c:tester.polynomial_coefficients){
        if(c<0) c+=field_characteristic;
       };
       tester.adjust_degree();


       if(is_unity_polynomial<__int128_t>(tester)==true) return false;
  
       }


  //Resultado
  return true;


};

//*********************************************************************************************************
//FIM DO HEADER
#endif
