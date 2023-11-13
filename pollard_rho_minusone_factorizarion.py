#VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO POLLARD ρ-1 PARA FATORAR NÚMEROS INTEIROS
'''
O ALGORITMO DE POLLARD-RHO (p-1) FAZ USO DO CHAMADO PEQUENO TEOREMA DE FERMAT QUE AFIRMA QUE:
"QUE PARA QUAISQUER NÚMEROS COPRIMOS a E p, ISTO É, TAL QUE mdc(a, p) = 1, TEMOS QUE a^(p-1)≡1 (mod p)".
COMO EXEMPLO SEJAM a=2, p=3, a^(p-1)=2^(3-1)=4≡1 (mod 3).
SIMILARMENTE PARA a=4, p=7 TEMOS QUE a^(p-1)=4^(7-1)=4096≡1 (mod 7). 

SEJA n UM NÚMERO COMPOSTO, QUALQUER FATOR f NÃO TRIVIAL DE n OBEDECE AS RELAÇÕES f < n E f<n^(1/2).
SEJAM p, q DOIS NÚMEROS NO INTERVALO [0, n-1]. p≡q (mod n), APENAS NOS CASOS EM QUE p E q SÃO IDÊNTICOS.
SEJAM p E q DOIS NÚMEROS PRIMOS E SUPONHA QUE n SEJA UM PRODUTO DESTES DOIS FATORES PRIMOS.
SEJA (p-1) UM FATOR PRIMO DE UM NÚMERO l DE MODO QUE l=k(p-1), ONDE k É UM INTEIRO QUALQUER.
PELO TEOREMA DE FERMAT TEMOS QUE: a^l≡(a^(p-1))^k (mod p)≡1.
USANDO ESTES RESULTADOS OBTEMOS QUE p DIVIDE a^l, E POR SUPOSIÇÃO p É UM FATOR PRIMO DE n.
ASSIM O mdc(a^l-1, n) INCLUIRÁ p COM CERTEZA. O PROBLEMA RESIDE ENTÃO EM ENCONTRAR UM VALOR DE l ADEQUADO.


PARA MAIORES INFORMAÇÕES: 
https://en.wikipedia.org/wiki/Pollard%27s_p_−_1_algorithm

'''

#IMPORTANDO BIBLIOTECAS USADAS
import math


#FUNÇÕES USADAS NO ALGORITMO
def euclides_algorithm(a:int, b:int)->int:
 '''Algoritmo de Euclides para o cálculo do mmc de dois inteiros'''
 remainder:int=1
 while(remainder>0):
  remainder=(a%b)
  a=b
  b=remainder

 #Resultado
 return a


def bin_pow(a:int, b:int)->int:
 '''Função que implementa a exponenciação binária''' 
 result:int=1

 while(b>0):#Loop principal
  if((b&1)):
   result*=a
  
  a*=a #Atualizando variável
  b>>=1 #Atualizando variável
  
 return result


def mod_bin_pow(a:int, b:int, m:int)->int:
 '''Exponenciação binária''' 
 result:int=1

 while(b>0):#Loop principal
  if((b&1)):
   result=((result%m)*(a%m))%m
  
  a=((a%m)*(a%m))%m #Atualizando variável
  b>>=1 #Atualizando variável
  
 return result

def is_prime(n:int)->bool:
 '''Função que determina se um inteiro é primo'''
 #Casos triviais
 if(n<2):
  return False
 if(n==2 or n==3):
  return True
 if((n%2)==0 or (n%3)==0):
  return False
 
 #Loop principal
 limit:int=int(math.sqrt(n))

 for i in range(5, (limit+10), 6):
  if((n%i)==0 or (n%(i+2))==0):
   return False

 return True

def fill_prime_buffer(B:int)->list:
 '''Função que preenche um buffer de números primos usados no algoritmo'''
 prime_list:list=[]#Lista de números primos

 for i in range(B+1):
  if(is_prime(i)==True):
   prime_list.append(i)

 return prime_list
 

def pollard_rho_minusone_factorization(n:int, smoothness:int)->int:
 '''Função que cálcula um fator primo dado uma base de primos'''
 #Caso trivial:
 if((n%2)==0):
  return 2, (n//2)

 #Etapa 1: prenchendo um buffer de fatores primos e ajsutando variáveis no algoritmo
 prime_list:list=fill_prime_buffer((smoothness+1))
 
 #Etapa2: Calculando o expoente M usado no algoritmo
 M:int=1
 for p in prime_list:
  s:int =int(math.log(n)/math.log(p))
  M*=bin_pow(p, s)

  #Etapa 3: Cálculo do fatore primos
  power:int= mod_bin_pow(2, M, n)-1
  factor:int= euclides_algorithm(power, n)
  if(factor>1):
   return factor

 return factor


#FUNÇÃO PRINCIPAL
#RECEBENDO INPUT DO USUÁRIO
n:int = int(input('Digite um inteiro a ser fatorado:'))
B:int = int(input('Digite um limite para a base de primos usados no algoritmo:'))

#EXECUTANDO O ALGORITMO
prime_factor:int=pollard_rho_minusone_factorization(n, B)
print("Fatores de {} encotrados:  {} e {}".format(n, prime_factor, (n//prime_factor)))

