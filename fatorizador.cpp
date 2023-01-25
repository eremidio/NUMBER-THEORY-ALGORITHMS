//VAMOS ESCREVER UM NÚMERO QUE EXIBE NA TELA A DECOMPOSIÇÃO DE UM NÚMERO EM SEUS FATOORES PRIMOS

/*CABEÇALHO*/
#include<iostream>
#include<cstdlib>
using namespace std;

int main(){
//DEFINIÇÃO DE VARIÁVEIS
long long int * variavel=(long long int *)malloc(sizeof(long long int));
long long int * numero=(long long int *)malloc(sizeof(long long int));
long long int i;
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
