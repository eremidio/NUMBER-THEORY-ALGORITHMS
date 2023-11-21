#VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE STRASSEN PARA FATORAR NÚMEROS INTEIROS
'''
O ALGORITMO DE STRASSEN (POLLARD) É O ALGORITMO MAIS RÁPIDO PARA FATORAR NÚMEROS INTEIROS CUJA COMPLEXIDADE E TEMPO DE EXECUÇÃO SÃO RIGOROSAMENTE DETERMINADOS EM NOTAÇÃO
BIG-O SUA COMPLEXIDADE É O(n^(1/4)log(n)).

O ALGORITMO É EXTREMAMENTE SIMPLES E BASEIA-SE NA OBSERVAÇÃO DE QUE UM NUMERO COMPOSTO TEM PELO MENOS UM FATOR PRIMO INFERIOR A n^(1/2) SENDO d=n^(1/4), ENTÃO 
mmc(d²! mod n, n)>1. 

NESTE CASO d²! mod n =b(0)b(1)...b(d-1), ONDE DEFINE-SE PARA i INTEIRO b(i)=(i.d+1)(i.d+2)...(i.d+d) mod n

PARA MAIORES INFORMAÇÕES: https://web.maths.unsw.edu.au/~davidharvey/talks/factoring.pdf
'''


#IMPORTANDO BIBLIOTECAS
from math import sqrt, gcd

#FUNÇÕES USADAS NO ALGORITMO

def quartic_root(n:int)->int:
 '''Função que extrai a raíz quarta de um número'''
 return int(sqrt(sqrt(n)))


def generate_divisor(multiplier:int, bound:int, number:int)->int:
 '''Função que calcula um divisor que possivel compartilha algum fator primo com o número a ser fatorado'''
 result:int=1
 for i in range((multiplier*bound), ((multiplier*bound)+bound+1)):
  result=(result*i)%number
 
 return result


def strassen_pollard_factorization(n:int)->int:
 '''Função que implementa o algoritmo de Strassen-Pollard'''
 #Cálculo da raíz quártica do número a ser fatorado
 d:int=quartic_root(n)

 factor:int=1 #Variável local

 #Busca por fatores primos
 for i in range(d+2, 0, (-1)):
  tester:int=generate_divisor(i, d, n)
  factor=gcd(tester, number)
  if(factor>1):
   return factor;

 #Caso o algoritmo falhe
 if(factor<2):
  print("%d é primo."%n)
  return(-1)


#****************************************************************************************************************************************************************
#PROGRAMA PRINCIPAL

#Recebendo input do usuário
number:int=int(input('Digite um inteiro:'))

#Executando o algoritmo
factor:int=strassen_pollard_factorization(number)

if(factor>1):
 print('Fatores de {} : {} e {}'.format(number, factor, (number//factor))) 
