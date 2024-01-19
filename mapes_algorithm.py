#VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE MAPES  PARA COMPUTAR A FUNÇÃO π(x) DE CONTAGEM DE NÚMEROS PRIMOS


'''
O ALGORITMO DE MAPES É UM EFICIENTE ALGORITMO QUE CONTABILIZA A FUNÇÃO π(x) PARA A CONTAGEM DE PRIMOS. 
DADO UM DETERMINADO INTERVALO {1, 2,..., x}, CONTENDO PRIMOS {p(1), ..., p(a)} O PRINCÍPIO DE INCLUSÃO-EXCLUSÃO AFIRMA QUE:
π(x)=|_x_|-|_x/p(i)_|+|_x/p(i)p(j)_|-|_x/p(i)p(j)p(k)_|+.... (AQUI |_x_| DENOTA O INTEIRO MENOR MAIS PRÓXIMO DE x)

DIVERSOS ALGORITMO PARA COMPUTAR EFICIENTEMENTE A FUNÇÃO π(x) CONSISTEM EM REDEFINIÇÃO DO SOMATÓRIO EM PARCELAS QUE SÃO FACILMENTE COMPUTÁVEIS.
É POSSÍVEL MOSTRAR QUE O SOMATÓRIO ACIMA PODE SER REESCRITO COMO π(x)-π(√x)-1=φ(x, π(√x)) ONDE φ(m, n) É UMA FUNÇÃO QUE CONTABILIZA O NÚMERO DE INTEIROS <n NÃO DIVISÍVEL
POR UM PRIMO p<n.

O ALGORTITMO DE MAPES COMPUTA A FUNÇÃO φ USANDO UMA PEQUENA LISTA DE NÚMEROS PRIMOS PRÉ-COMPUTADA E UMA SÉRIE DE FUNÇÕES T(k, x, a) QUE USA A EXPANSÃO DE π(√x) EM
DIGITOS BINÁRIOS.

PARA MAIORES INFORMAÇÕES: https://mathworld.wolfram.com/MapesMethod.html
                          https://mathworld.wolfram.com/LegendresFormula.html
                          https://en.wikipedia.org/wiki/Prime-counting_function

'''

#********************************************************************************************************************************************************************
#1: IMPORTANDO BIBLIOTECAS USADAS NO ALGORITMO
import math

#********************************************************************************************************************************************************************
#2:FUNÇÕES
#Função que implementa a exponenciação binária
def bin_pow(a:int, b:int)->int:
 '''Exponenciação binária''' 
 result:int=1

 while(b>0):#Loop principal
  if((b&1)):
   result*=a
  
  a*=a #Atualizando variável
  b>>=1 #Atualizando variável
  
 return result

#Teste de primalidade para pequenos números primos
def fast_prime_checking(n:int)->bool:
 '''Teste de primalidade por divisão e erro com otimização 30k+1'''
 #Números menores que 2
 if(n<2):
  return False

 #Primos menores do que 30
 if(n==2 or n==3 or n==5 or n==7 or n==11 or n==13 or n==17 or n==19 or n==23  or n==29):
  return True

 #Teste para fatores 2, 3, 5
 if((n%2)==0 or (n%3)==0 or (n%5)==0):
  return False

 #Variáveis locais
 divisors:list=[1,7,11,13,17,19,23,29]
 root:int=int(math.sqrt(n))

 #Loop principal
 #1ª iteração
 for i in range(1,8,1):
  if((n%divisors[i])==0):
   return False

 #Demais iterações
 while(divisors[0]<root):
  #Atualizando a lista de possíveis divisores
  new_divisors:list=[x+30 for x in divisors]
  divisors=new_divisors

  for i in range(8):
   if((n%divisors[i])==0):
    return False

 #Resultado caso o número seja primo
 return True

#Função que preenche um buffer de números primos
def fill_prime_buffer(n:int)->list:
 '''Função que preenche um buffer de números primos'''
 #Variáveis locais
 prime_buffer:list=[]
 prime_candidate:int=2

 #Preenchendo um buffer de primos
 while(len(prime_buffer)<(n+10)): 
  if(fast_prime_checking(prime_candidate)==True):
   prime_buffer.append(prime_candidate)

  #Atualizando candidatos
  prime_candidate+=1

 #Resultado
 return prime_buffer



#Função que computa a função π(x) para x<1000000 usando testes de primalidade
def small_counting(x:float)->int:
 '''Função que determina π(x) usando testes de primalidade'''
 #Variáveis locais
 n:int=int(x)+1
 counter:int=0

 #Contagem de primos
 for i in range((n+1)):
  if(fast_prime_checking(i)==True):
   counter+=1

 #Resultado 
 return counter


#Função que computa a função intermediária T(k, x, a)
def T_k(k:int, x:float, a:int, prime_list:list):
 '''Função que computa valores intermediários usados no algoritmo de Mapes'''
 #Variáveis locais
 bit_list:list=[] #Array de bits
 parity:int=0 #Paridade
 tk:int=int(x)

 #Calculando a expansão de k em (a-1) bits
 while(len(bit_list)<a):
  if((k&1)):
   parity+=1
   bit_list.append(1)
  else:
   bit_list.append(0)
  
  k>>=1#Atualizando variável

 #Calculando o valor absoluto de T(k, x, a)
 for i in bit_list:
  if(i==1):
   tk//=prime_list[i]

 #Resultado
 if((parity%2)==0):
  return tk
 else:
  return (-1)*tk



#Função que computa φ(m, n)
def phi_mn(x:float, a:int, prime_list:list)->int:
 '''Função que o número de inteiros até um certo limite não divisíveis por um certo conjunto de primos'''
 #Variáveis locais
 phi:int=0

 #Loop principal
 for k in range(0, bin_pow(2, a), 1):
  phi=phi+T_k(k, x, a, prime_list)

 #Resultado
 return phi


#Função que computa o número de primos até um dado limite
def prime_counting_function(x:float)->int:
 '''Função de contagem de números primos'''
 #Caso base: pequenos números
 if(x<=100):
  return small_counting(x)

 #Caso geral:
 #Variáveis locais
 root:int=int(math.sqrt(x))

 #Computando π(√x)
 prime_root_counting:int=prime_counting_function(root)
 
 #Preenchendo um buffer de primos
 prime_seed=fill_prime_buffer((prime_root_counting+2))

 #Computando φ(x, π(√x))
 phi_function:int=phi_mn(x, prime_root_counting, prime_seed)

 #Computando π(x)
 return (phi_function+prime_root_counting-1)


#********************************************************************************************************************************************************************
#3:FUNÇÁO PRINCIPAL

#Recebendo input do usuário
x:float=float(input('Digite um limitante superior para a contagem de primos: '))

#Computando a função π(x)
print("π({})={}".format(x, prime_counting_function(x)))


