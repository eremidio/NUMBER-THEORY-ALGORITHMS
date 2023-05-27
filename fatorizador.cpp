//VAMOS ESCREVER UM NÚMERO QUE EXIBE NA TELA A DECOMPOSIÇÃO DE UM NÚMERO EM SEUS FATOORES PRIMOS

/*CABEÇALHO*/
#include<iostream>
#include<cstdlib>
using namespace std;

int main(){
//DEFINIÇÃO DE VARIÁVEIS
uint64_t * variavel=(uint64_t *)malloc(sizeof(uint64_t));
uint64_t * numero=(uint64_t *)malloc(sizeof(uint64_t));
uint64_t i;
//PROCEDIMENTOS EXECUTÁVEIS
cout<<"Digite o número um número inteiro para ser decomposto em seus fatores primos: ";
cin>> *numero;
//DECOMPOSIÇÃO DE UM NÚMERO EM FATORES PRIMOS
cout<<"Eis a sua lista de fatores primos do número "<<*numero<<":\n";
*variavel=*numero;
do{
for(i=2; i<*numero; i++){
if(((*variavel)%i)==0){
cout<<i<<", ";
(*variavel) = (*variavel)/i;
break;
                    };
if((*variavel%i)!=0)
continue;
                   };
  }while(*variavel!=1);
cout<<"\n";
//LIMPANDO O CACHÊ DE MEMÓRIA E NECERRANDO O PROGRAMA
numero=NULL;
variavel=NULL;
free(numero);
free(variavel);

return 0;
}
