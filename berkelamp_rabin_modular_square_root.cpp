//VAMOS CRIAR UM PROGRAMA PARA TESTARAS ROTINAS CRIADAS NO ARQUIVO berkelamp_rabin_modular_square_root.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o berkelamp_rabin_modular_square_root berkelamp_rabin_modular_square_root.cpp


//Cabeçalho
#include"berkelamp_rabin_modular_square_root.h"
using namespace std;

//Função principal
int main(){

  //Variáveis locais
  int64_t a, p, root;


  //Procedimentos
    //Recebendo input do usuário
    cout<<"[Inteiro] a: ";
    cin>> a;
    cout<<"[Inteiro primo] p: ";
    cin>> p;

    //Calculando solução de x² = a (mod p)
    root=berkelamp_rabin_modular_square_root(a, p);

    if(root>0)
      cout<<"√"<<a<<" (mod "<<p<<") = "<<root<<'\n';
    else
      cout<<"Não foram encontradas raízes quadradas de "<< a<<" móudulo "<<p<<'\n';

  //Finalizando a aplicação
  return 0;      

}
