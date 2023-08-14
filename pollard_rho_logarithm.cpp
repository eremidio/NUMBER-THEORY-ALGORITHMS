//VAMOS IMPLEMENTAR O ALGORITMO DE POLLARD RHO PARA CÁLCULO DE LOGARITMO DISCRETOS
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o pollard_rho_logarithm pollard_rho_logarithm.cpp 


/*
O ALGORITMO DE POLLARD RHO PARA O CALCULO DE LOGARITMOS DISCRETOS BASEIA-SE NA SEGUINTE OBSERVAÇÃO:
SEJA G DE ORDEM |G| UM GRUPO FINITO E CÍCLICO, SEJAM α, β, DOIS ELEMENTOS DE G, TAL QUE: α^γ = β.
SE EXISTIREM a, b , A, B TAL QUE (α^a)(β^b)=(α^A)(β^B), ENTÃO (B-b)γ=(a-A) (mod |G|).
(|G| DENOTA O NÚMERO DE ELEMENTOS NESTE GRUPO).


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm_for_logarithms
                          https://programmingpraxis.com/2016/05/27/pollards-rho-algorithm-for-discrete-logarithms/
                          https://www.codingninjas.com/studio/library/the-pollard-rho-but-for-discrete-logarithm-algorithms
*/

//Cabeçalho
extern "C"{
int printf(const char* format, ...);
          };


//Definindo constantes usadas no cálculo
const int n = 102, N = n + 1;  /* N DEVE SER DEFINIDO COMO A ORDEM DO GRUPO CÍCLICO EM QUESTÃO.*/
const int alpha = 6;            /*O PARÂMETRO alpha DEVE SER UMA RAÍZ PRIMITIVA DE N A ORDEM DO GRUPO EM QUESTÃO.*/
const int beta = 53;             /* O PARÂMETRO beta DEVE SER DEFINIDO COMO O MENOR EXPOENTE TAL QUE alpha^beta>N. */


//Função que atualiza as variáveis no algoritmo de Pollard rho
void new_xab(int& x, int& a, int& b){
  switch (x % 3) {
  case 0: x = x * x     % N;  a =  a*2  % n;  b =  b*2  % n;  break;
  case 1: x = x * alpha % N;  a = (a+1) % n;                  break;
  case 2: x = x * beta  % N;                  b = (b+1) % n;  break;
                 };
                                    };

//Função principal que implementa o algoritmo de Pollard rho para o cálculo de logaritmos discretos
int main(void){
//Variáveis locais
int x = 1, a = 0, b = 0;
int X = x, A = a, B = b;
//Procedimentos
//Loop principal
printf("     i      x      a      b      X      A      B\n----------------------------------------------------------------\n");
for (int i = 1; i < n; ++i){
new_xab(x, a, b);
new_xab(X, A, B);
new_xab(X, A, B);
printf("%6d %6d %6d %6d %6d %6d %6d\n", i, x, a, b, X, A, B);

if (x == X)
break;
                           };
return 0;
              }
