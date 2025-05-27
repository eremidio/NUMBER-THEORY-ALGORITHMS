//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO roger_ramanujan_identities.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o rogers_ramanujan_identities rogers_ramanujan_identities.cpp -O3



//Cabeçalho
#include"rogers_ramanujan_identities.h"
using namespace std;


//Função principal
int main(){

  //Variáveis locais
  int64_t n;


  //Procedimentos
    //Recebendo input do usuário
    cout<<"[Inteiro]  n:";
    cin>> n;

    //Computando a função G(q)
    polynomial<int64_t> G_function=compute_rogers_ramanujan_g_function<int64_t>(n);
    cout<<"\nG(q)= ...+";
    for(auto it=G_function.monomials.begin(); it!=G_function.monomials.end(); ++it){
      cout<<"("<<it->second.coefficient<<")q^";
      cout<<it->second.power;
      if(it->second.power>0) cout<<"+";
    }
    cout<<"\n\n";


    //Computando a função H(q)
    polynomial<int64_t> H_function=compute_rogers_ramanujan_h_function<int64_t>(n);
    cout<<"\nH(q)=  ...+";
    for(auto it=H_function.monomials.begin(); it!=H_function.monomials.end(); ++it){
      cout<<"("<<it->second.coefficient<<")q^";
      cout<<it->second.power;
      if(it->second.power>0) cout<<"+";
    }
    cout<<"\n\n";



  //Finalizando a aplicação
  return 0;

}

