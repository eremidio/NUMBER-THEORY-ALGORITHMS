//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO polynomial_primitive_root.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o polynomial_primitive_root polynomial_primitive_root.cpp


//Cabeçalho
#include"polynomial_primitive_root.h"
using namespace std;


//Função principal
int main(){

  //Variáeis locais
  polynomial<int64_t> field_generator, p;
  int64_t prime;


  //Procedimentos
    //Recebendo input do usuário
    cout<<"[Característica do corpo finito] p: ";
    cin>>prime;

    cout<<"[Gerador do corpo finito] f(x): ";
    field_generator.set();

    cout<<"[Polinômio a ser testado] p(x): ";
    p.set();
    

    //Testando se p(x) é uma raíz primitiva em GF(p)[X]/f(x)
    if(is_primitive_root(p, field_generator, prime)==true)
      cout<<"p(x): "<<p.algebraic()<<" é uma raíz primitiva em GF("<<prime<<")/("<<field_generator.algebraic()<<").\n";
    else
      cout<<"p(x): "<<p.algebraic()<<" não é uma raíz primitiva em GF("<<prime<<")/("<<field_generator.algebraic()<<").\n";


  //Finalizando a aplicação
  return 0;

}
