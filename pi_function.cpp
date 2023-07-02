//VAMOS IMPLEMENTAR UM PROGRAMA QUE CALCULA A FUNÇÃO π(x) QUE CALCULA O NÚMERO DE PRIMOS ATÉ UM DADO LIMITE DE 10⁶
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o pi_function pi_function.cpp
//O PRESENTE CÓDIGO PRODUZ PEQUENOS ERROS PERCENTUAIS DEVIDO AO POSSÍVEL MAL AJUSTE DE PARÂMETROS

/*

A FUNÇÃO π(x) É UMA DAS FUNÇÕES MAIS IMPORTANTES EM MATEMÁTICA E CONTABILIZA O NÚMERO DE PRIMOS DADO UM CERTO LIMITE.

O CHAMADO TEOREMA DE NÚMEROS ṔRIMOS ESTABELECE QUE PARA VALORES GRANDES DE x π(x)=x/ln(x) OU π(x)=li(x).
ln(x) DENOTA O LOGARITMO NATURAL.
li(x) DENOTA A CHAMADA INTEGRAL LOGARÍTMICA, A INTEGRAL DEFINIDA DE 1/ln(x) DE 0 ATÉ x.

A FUNÇÃO π(x) É EXTREMAMENTE IMPORTANTE PARA ESTUDAR A DENSIDADE DE NÚMEROS PRIMOS NO CONJUNTODOS INTEIROS POSITIVOS,
ESTANDO CONECTADO DIRETAMENTE A CHAMADA HIPÓTESE DE RIEMANN QUE ESTABELECE K]LIMITES PRECISOS PARA A FUNÇÃO π(x).

DIVERSOS ALGORITMOS COMO A PENEIRA DE ERATÓSTENES PODEM SER USADOS PARA CONTABILIZAR A FUNÇÃO π(x).
NESTE PROGRAMA IMPLEMENTAMOS UM MÉTODO MISTO USANDO A PENEIRA DE ERATÓSTENES E O ALGORITMO DE MEISSEL-LEHMER.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Prime-counting_function

*/



//**************************************************************************************************************************** 
//Cabeçalho
#include<iostream>
#include<vector>
#include<stdint.h>
#include<assert.h>
#include<cmath>
using namespace std;

//Constantes globais
const long long unsigned SIEVE_MAX=10000;
const long long unsigned PRIME_MAX=540;

//****************************************************************************************************************************
//FUNÇÃO AUXILIAR QUE CHECA SE UM NÚMERO É PRIMO
//Usamos tentantiva por divisão com uma otimização do tipo 6k+1
bool is_prime(unsigned long n){
//Variáveis
unsigned long i;

//Procedimentos

if (n == 2 || n == 3)
return true;

if (n <= 1 || n % 2 == 0 || n % 3 == 0)
return false;

for(i = 5; i * i <= n; i += 6){
if (n % i == 0 || n % (i + 2) == 0)
return false;
                             };
return true;
                         };
 
//Função de contagem de primos para números pequenos usando a peneira de Eratóstenes
//Função de contagem para pequenos números primos
unsigned long sieve_counting(unsigned long n){

//Variáveis locais
bool number_list[SIEVE_MAX];
unsigned long ground, counter;
unsigned long i, prime;

//Ajustando um array de booleanos
for (i=0; i<n; ++i)
number_list[i]=true;

//AJUSTE DE VARIÁVEIS
ground=floor(sqrt(n));


//APLICANDO A PENEIRA DE ERATÓSTENES A LISTA DE VALORES BOOLEANOS
for (prime=2; prime<=ground; prime++){
for(i=prime*prime; i<n; i+=prime)
number_list[i]=false;
                                     };
//Contagem de números primos
counter=0;
for(i=2; i<n; ++i){
if(number_list[i]==true){
counter++;
                        };
                  };

//Resultado
return counter;                     
                                 };
//****************************************************************************************************************************
//CLASSE

struct pi{
public:
//Variáveis usadas no cálculo
unsigned long n;//Input do usuário
vector<unsigned long> prime_vector;//Buffer de vetor
unsigned long sqrt_n, cbrt_n, result, upper, lower;

//Métodos da classe
void get_input();//Função que recebe input do usuário
void pi_function(); //Função principal 
void fill_prime_buffer();//Função que estoca os número primos até n^(1/2)em um vetor
unsigned long phi(unsigned long, unsigned long);//Função Φ(m, n)
         };

//****************************************************************************************************************************
//MÉTODOS DA CLASSE
//Função que recebe input do usuário
void pi::get_input(){
cout<<"Digite um um limitante para a contagem de primos:";
cin>>n;

//Preenchendo o buffer de números primos e ajustando variáveis
if(n>SIEVE_MAX){
sqrt_n=sqrt(n);
cbrt_n=cbrt(n);
upper = sieve_counting(sqrt_n);
lower = sieve_counting(cbrt_n);
fill_prime_buffer();
               };

                    };

//Função principalda classe
void pi::pi_function(){
if(n<=SIEVE_MAX)
result=sieve_counting(n);
else{
result=phi(n,lower)+(0.5*(upper+lower-2)*(upper-lower+1));
for(unsigned long i=lower; i<upper; ++i)
result-=sieve_counting(n/prime_vector[i]);

    };
                      };

//Função que preenche o buffer de números primos
void pi::fill_prime_buffer(){
//Variáveis locais
unsigned long i=2;
//Procedimento
while(i<(n/1e2)){
if(is_prime(i)==true)
prime_vector.push_back(i);
i++;
              };
//TESTE USE UM // APÓS O MESMO
//cout<<"TESTE 2\n";
//cout<<prime_vector.size()<<"\n";
                            };
//Função Φ(m, n)
unsigned long pi::phi(unsigned long a, unsigned long b){
//Checagem se o buffer de primos possui elementos suficientes
//TESTE USE UM // APÓS O MESMO
//cout<<"TESTE 1\n";
//cout<<prime_vector.size()<<"\n";
//cout<<b<<"\n";

assert(b<=prime_vector.size() && b<PRIME_MAX);
//Procedimento
if(b==0)
return floor(a);
else if(b > 0)
return phi(a, b-1) - phi(a/prime_vector[b-1], b-1);

return 0;
                                        };

//****************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//Inicializando um objeto da classe
pi pi_counter;
//Procedimentos
//Recebendo input do usuário
pi_counter.get_input();

//Contabilizando o resultado de π(x) 
pi_counter.pi_function();
cout<<"π("<<pi_counter.n<<")="<<pi_counter.result<<".\n";

//Finalizando a aplicação
return 0;
          }
