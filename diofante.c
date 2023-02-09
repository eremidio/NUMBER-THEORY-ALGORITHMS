//Vamos escrever um simples programa em C capaz de resolver equações diofantinas lineares do tipo

/*Cabeçalho*/
#include<stdio.h>
#include<stdlib.h>

//Funções úteis
//Explicação do algoritmo implementado
void header(){
printf("\033[34mVamos escrever um programa que resolve equações diofantinas lineares envolvendo duas variáveis.\nEquações diofantinas lineares tem a seguinte forma: ax+by=c, onde a, b, c são números inteiros e todos são diferentes de zero.\nO objetivo é encontrar valores inteiros de x e y que satifaçam a equação acima para um determinado conjunto de valores (a,b,c).\nNeste processo usaremos a aritmética modular.\nDado a equação do tipo ax+b=c, determina-se o maior de a e b, que denotamos por max(a,b), o menor entre eles é de notado por min(a,b).\nDado o maior coeficiente dos dois o proximo consiste em encontrar um  limitante superior k, tal que:\nk.max(a,b)<c, porém (k+1).max(a,b)>c.\nTomando um o conjunto i=k, k-1, k-2, ..., 1, efetuamos o cálculo c-i.max(a,b).\nAs soluções correspodem as situações em que c-i.max(a,b) ≡ 0 mod (min(a,b)).\nAssim obtemos as soluções como pares ordenados x=i, y=j, onde j=[c-i.max(a,b)]/min(a,b).\nO algoritmo aqui descrito pode ser facilmente generalizado, para uma equação mais geral do tipo: a(1)x(1)+ a(2)x(2) + ... + a(n)x(n)=constante usando-se arrays de coeficientes.\nPorém, o tempo e complexidade do algoritmo crescrem rapidamente, uma vez que estes coeficientes precisam ser ordenados em ordem crescente e o número de cálculos envolvendo congruências cresce rapidamente\n(A redução é feita um a um em ordem decrescente dos coeficientes da equação).\033[0m\n\n");
             };

//Função principal
int main(){
//Cabeçalho do programa
header();
//Variáveis
int a, b, c;
int* x_values=NULL;
int* y_values=NULL;
int counter, limitant, i, bigger, smaller, difference;

//Procedimentos
//Recebendo variáveis
printf("Digite o valor de a:\n");
scanf("%d", &a);
printf("Digite o valor de b:\n");
scanf("%d", &b);
printf("Digite o valor de c:\n");
scanf("%d", &c);

//Determinando o maior dos coeficientes
if(a>b){
bigger=a;
smaller=b;
       };

if(a<b){
bigger=b;
smaller=a;
       };

//Instanciando variáveis usadas no cálculo (i, j)
limitant=1;
counter=0;

//Calculando o valor do limitante
while((limitant*bigger)<c){
limitant++;
                          };//Aqui encontramos o valor de k+1, portanto devemos reduzir uma unidade
limitant--;

//Calculando os valores de x e y
for(i=limitant; i>0; i--){
difference=(c-i*bigger)%smaller;
if(difference==0){
counter++;
//Redefinindo o array de soluções e alocando os resultados encontrados
x_values=(int*)realloc(x_values, counter*sizeof(int));
y_values=(int*)realloc(y_values, counter*sizeof(int));
x_values[counter-1]= i;
y_values[counter-1]=(c-i*bigger)/smaller;

                                    };
                          };

//Exibindo os resultados encontrados
printf("Eis as soluções inteira para a %dx+%dy=%d:\n", bigger, smaller, c);
for(i=0;i<counter; i++)
printf("x=%d e y=%d\n", x_values[i], y_values[i]);
printf("Aqui 'x' de nota o valor da variável multiplicada pelo maior coeficiente, enquanto 'y' o valor da variável multiplicada pelo menor dos coeficientes da equação.\n");                    
//Limpando o cachê de memória e encerrando o programa
free(x_values);
free(y_values);
return 0;
          };
