//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO dirichlet_character.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o dirichlet_character dirichlet_character.c -lm -O2


//Cabeçalho
#include"dirichlet_character.h"


//Função principal
int main(){

  //Teste 1: tabela de caractéres de Dirichlet módulo um primo
  tabulate_dirichlet_character_modulo_prime_power(7,1);
  
  //Teste 2: tabela de caractéres de Dirichlet módulo potência de um primo  
  tabulate_dirichlet_character_modulo_prime_power(3,2);
  tabulate_dirichlet_character_modulo_prime_power(2,4);

  //Finalizando a aplicação
  return 0;

}
