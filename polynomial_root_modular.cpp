//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO polynomial_root_modular.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o polynomial_root_modular polynomial_root_modular.cpp 


//Cabeçalho
#include"polynomial_root_modular.h"
using namespace std;


//Função principal
int main(){

  //Variáveis locais
  polynomial<int64_t> p1;
  int64_t prime, power;
  int64_t mod_root;


  //Procedimentos
    //Recebendo input do usuário
    cout<<"Primo: ";
    cin>>prime;
    cout<<"Expoente: ";
    cin>>power;

    p1.set();
    cout<<"p(x): "<<p1.algebraic()<<'\n';

    //Cálculo da raíz do polinômio
    mod_root=polynomial_root_modulo_prime(p1, prime);

    if(mod_root>0)
      cout<<"Solução de p(x)=0 (mod "<<prime<<"): "<<mod_root<<'\n';
    else
      cout<<"Não foi encontrada solução de p(x)=0 (mod "<<prime<<")\n";


    mod_root=polynomial_root_modulo_prime_power(p1, prime, power);

    if(mod_root>0)
      cout<<"Solução de p(x)=0 (mod "<<static_cast<int64_t>(bin_pow(prime, power))<<"): "<<mod_root<<'\n';
    else
      cout<<"Não foi encontrada solução de p(x)=0 (mod "<<static_cast<int64_t>(bin_pow(prime, power))<<")\n";



  //Finalizando a aplicação
  return 0;
          }
