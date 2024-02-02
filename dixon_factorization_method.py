#VAMOS CRIAR UM PROGRAMA EM PYTHON QUE IMPLEMENTA O ALGORITMO DE DIXON PARA FATORAR NÚMEROS INTEIROS
'''
O ALGORITMO DE DIXON É UM EFICIENTE ALGORITMO USADO PARA FATORAR NÚMEROS INTEIROS. ESTE ALGORITMO É O PROTÓTIPO DOS ALGORITMOS DE FATORAÇÃO QUE USAM UMA PEQUENA BASE DE 
NÚMEROS PRIMOS E BUSCA POR NÚMEROS SUAVES (COMPLETAMENTE FATORADO EM RELAÇÃO A ESSA BASE DE PRIMOS).

A IDEIA É PRODUZIR UMA RELAÇÃO DE CONGRUÊNCIA DO TIPO x²=y² (mod N), ONDE N=pq É O NÚMERO A SER FATORADO, POSSÍVEIS FATORES PRIMOS DA FORMA p=mmc(x+y, N) E q=(|x-y|, N).
ENCONTRAR NÚMEROS x, y CUJOS QUADRADOS SATISFAÇAM ESTA RELAÇÃO É EXTREMAMENTE IMPROVÁVEL OU NO CASO MAIS SIMPLES x=n² E y=(n+1)² LEVA A FATORAÇÕES TRIVIAIS. A IDEIA
É ENTÃO BUSCAR NÚMEROS z(i), i=1, 2, ...; COMPLETAMENTE FATORADOS EM RELAÇÃO A UMA BASE DE PRIMOS PRÉ-COMPUTADA E OBTER y² POR MEIO DA MULTIPLICAÇÃO DE z(i)'s.

NO ALGORITMO DE DIXON x É SELECIONADO ALEATORIAMENTE E É CHECADO SE z=x² (mod N) SE EXPANDE EM UMA PEQUENA BASE DE PRIMOS.

AO CONTRÁRIO DE OUTROS ALGORITMOS QUE USAM UMA IDÉIA SIMILAR DE SELEÇÃO DE NÚMEROS SUAVES COMO A PENEIRA QUADRÁTICA E A PENEIRA EM CORPOS ALGÉBRICOS NÚMERICOS, O
ALGORITMO DE DIXON NÃO SE BASEIA EM CONJECTURAS AINDA NÃO COMPROVADAS EM RELAÇÃO A DISTRIBUIÇÃO DE NÚMEROS SUAVES EM UM DADO INTERVALO, DE MODO QUE SEU TEMPO DE 
EXECUÇÃO É RIGOROSAMENTE DETERMINADO O(2(2^(1/2)) (exp(ln(N)ln(ln(N))))^(1/2) ) OU L(1/2, (2^(1/2)).

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Dixon%27s_factorization_method
ARTIGO ORIGINAL: https://www.ams.org/journals/mcom/1981-36-153/S0025-5718-1981-0595059-1/S0025-5718-1981-0595059-1.pdf

''' 


#**********************************************************************************************************************************************************************
#
#0: IMPORTANDO BIBLIOTECAS
import numpy as np
import numba 
from random import randint


#**********************************************************************************************************************************************************************
#
#1: FUNÇÕES AUXILIARES
def euclides_algorithm(a:int, b:int)->int:
 '''Algoritmo de Euclides'''
 remainder:int=1
 while(remainder>0):
  remainder=(a%b)
  a=b
  b=remainder

 #Resultado
 return a

def bin_pow(a:int, b:int)->int:
 '''Exponenciação binária''' 
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


def legendre_symbol(a:int, p:int)->int:
 '''Função que calcula o símbolo de Legendre usando o critério de Euler. Função útil se usada no algoritmo principal'''
 return mod_bin_pow(a,((p-1)//2), p)

@numba.jit(nopython=True)
def fast_prime_checking(n:int)->bool:
 '''Função que determina se um número é primo por meio de tentativa por divisão com otimização 30k+1'''
 #Caso trivial primos menores que 30
 if(n<2):
  return False
 if(n==2 or n==3 or n==5 or n==7 or n==11 or n==13 or n==17 or n==19 or n==23 or n==29):
  return True
 
 #Teste para números divisíveis por 2, 3, 5
 if((n%2)==0 or (n%3)==0 or (n%5)==0):
  return False
 
#Variáveis locais
 divisors:list=[1, 7, 11, 13, 17, 19, 23, 29]
 root:int=int(np.sqrt(n))

 #Procedimentos 
 #1ª iteração:
 for i in range(1,8,1):
  if((n%divisors[i])==0):
   return False
 
 #Demais iterações
 while(divisors[0]<root):
  #Recalculando possíveis divisores
  new_divisors:list=[x+30 for x in divisors]
  divisors=new_divisors

  #Teste por divisão:
  for j in range(8):
   if((n%divisors[j])==0):
    return False

 #Resultado
 return True



'''TESTE USE UM # APÓS O MESMO'''
#print(fast_prime_checking(4001))
#print(fast_prime_checking(10009))
#print(fast_prime_checking(10000000000000009))



#**********************************************************************************************************************************************************************
#
#2: CLASSE DO ALGORITMO

class dixon_factorization:
 '''Classe que implementa o algoritmo de Dixon'''
 #-------------------------------------------------------------------------------
 #MEMBROS DA CLASSE
 prime_buffer:list=[] #Base de primos usadas no algoritmo
 prime_bound:int=0 #Tamanho da base de primos usadas no algoritmo
 prime_size:int=0 #Número de elementos na base de números primos
 number:int=0 #Número a ser fatorado
 number_root:int=0 #Raíz quadradda do número a ser fatorado

 smooth_number_list:list=[] #Lista de números suaves
 z_list:list=[] #Lista de quadrados perfeitos usados na busca por relações constitutivas
 parity_matrix=np.empty((1, 1)) #Matriz de paridade dos expoentes das decomposições de z² (mod N) em relação a base de primos

 transpose_parity_matrix=np.empty((1, 1)) #Transposta da matriz de paridade
 reduced_matrix=np.empty((1, 1)) #Matriz reduzida usada na busca de relações constitutivas
 congruence_vector=np.empty((1, 1)) #Vetor de booleanos usados na busca de relações de Legendre do tipo x²= y²(mod N)

 factor:int=0 #Fator primo encontrado no algoritmo
 remainder:int=0 #Fator coprimo

 #--------------------------------------------------------------------------------
 #MÉTODOS DO ALGORITMO

 #1 
 def run(self):
  '''Função principal do algoritmo'''
  #Etapa 1: recebendo input do usuário e selecionando a base primos:
  self.setup()
  self.fill_prime_buffer()

  #Etapa 2: Processo de peneira de números suaves em relação a base de primos
  self.setup_sieving()
  self.sieving_algorithm()

  #Etapa 3: Busca por inteiros satisfazendo a relação constitutiva
  self.build_reduced_matrix()
  self.congruence_find_algorithm()
  
  #Etapa 4: Exibindo o resultado da execução do algoritmo
  self.print_result()


 #2
 def setup(self):
  '''Função que recebe input do usuário'''
  self.number = int(input("Digite um número que será fatorado: "))
  self.prime_bound = int(input("Digite um limitante superior para a base de números primos usados no algoritmo: "))
  self.number_root=int(np.sqrt(self.number))


 #3
 def fill_prime_buffer(self):
  '''Função que preenche um buffer de números primos'''
  #Definindo uma base primos usadas no processo de peneira de números suaves
  self.prime_buffer:list=[x for x in range((self.prime_bound+1)) if fast_prime_checking(x)==True]
  self.prime_size=len(self.prime_buffer)
  
  '''TESTE USE UM # APÓS O MESMO'''
  #print(self.prime_buffer)
  #print(self.prime_size)


 #4
 def setup_sieving(self):
  '''Função que ajusta matrizes usadas no algoritmo'''
  self.parity_matrix=np.resize(self.parity_matrix, ((self.prime_size+1), self.prime_size))
  self.congruence_vector=np.resize(self.congruence_vector, ((self.prime_size+1), 1))


 #5 
 def sieving_algorithm(self):
  '''Função que seleciona quadrados perfeitos suaves em relação a base de primos pré-computada'''
  #Variáveis locais
  row:int=0 #Index das linhas da matriz de paridade
  column:int=0 #Index das linhas da matriz de paridade
  random_int:int=0 #Número aleatório z tal que z²(mod N) é suave em relação a base de primos pré-computada
  z:int=0 #Variável intermediária  
  tester:int=0 #Variável intermediária  
  parity_list:list=[]#Lista de expoente da expansão em fatores primos de um possível candidato suave em relação a base de primos pré-computada
  prime_power:int=0 #Expoente da expansão de  em fatores primos de um possível candidato suave em relação a base de primos pré-computada

  #Procedimentos
  #Loop principal
  while(row<(self.prime_size+1)):
   random_int=randint(self.number_root, self.number) #Seleção de um número suave
   z=(random_int*random_int) #Ajuste de variáveis
   tester=z%(self.number) #Ajuste de variáveis
   column=0 #Ajuste de variáveis
   parity_list=[] #Ajuste de variáveis

   for x in self.prime_buffer:
    prime_power=0 #Ajuste de variáveis

    while((tester%x)==0): #Teste de divisibilidade
     tester//=x
     prime_power+=1

    parity_list.append((prime_power%2))


   #Checando se um número suave foi encontrado e preenchimento da matriz de paridade
   if(tester==1):
    self.z_list.append(z)
    self.smooth_number_list.append((z%self.number))


    '''TESTE USE UM # APÓS O MESMO'''
    #print(z)
    #print((z%self.number))
    

    for i in range(self.prime_size):
     self.parity_matrix[row, i] = parity_list[i]

    #Ajustando variavel para a próxima linha da matriz de paridade
    row+=1
  
  '''TESTE USE UM # APÓS O MESMO'''
  #print(self.parity_matrix)
  #print(self.z_list)
  #print(self.smooth_number_list)
  

 #6 
 def build_reduced_matrix(self):
  '''Função que calcula a matriz reduzida do sistema usada na busca por relações constitutivas'''
  self.transpose_parity_matrix=np.transpose(self.parity_matrix)
  self.reduced_matrix=np.dot(self.parity_matrix, self.transpose_parity_matrix)

  '''TESTE USE UM # APÓS O MESMO'''
  #print(self.transpose_parity_matrix)
  #print(self.reduced_matrix)
  


 #7
 def generate_checking_vector(self, n:int):
  '''Função que gera um vetor binário usado na busca por relações constitutivas'''
  #Variáveis locais
  k:int =0 #Posição do k-ésimo bit no vetor binário

  #Procedimentos
  #Loop principal
  while(k<(self.prime_size+1)):
   #Definindo o k-ésimo bit
   if(n&1):
    self.congruence_vector[k, 0]=1
   else: 
    self.congruence_vector[k, 0]=0

   #Atualizando variáveis 
   k+=1
   n>>=1
    

 #8 
 def factor_testing_algorithm(self)->bool:
  '''Função que determina se um fator não trivial do número a ser fatorado foi encontrado'''
  #Variáveis locais
  checking_vector=None #Vetor de booleanos usados na busca de relações de Legendre do tipo x²= y²(mod N)

  #Procedimentos
  checking_vector=np.dot(self.reduced_matrix, self.congruence_vector)
  
  #Checando a paridade do vetor coluna gerado
  for i in range((self.prime_size+1)):
   if((checking_vector[i, 0]%2)==1):
    return False

  #Resultado
  return True


 #9
 def factors_calculation(self)->bool:
  '''Função que tenta calcular um possível fator primo do número a ser fatorado'''
  #Variáveis locais
  x_squared:int=1
  y_squared:int=1
  x:int=1
  y:int=1

  #Procedimento
  #Computando x e y
  for i in range((self.prime_size+1)):
   if(self.congruence_vector[i, 0]==1):
    x_squared*=self.smooth_number_list[i]
    y_squared*=self.z_list[i]

  x=int(np.sqrt(x_squared))
  y=int(np.sqrt(y_squared))

  #Checando se fatores não triviais foram encontrados
  self.factor=euclides_algorithm((x+y), self.number)
  if(self.factor>1 and self.factor<self.number):
   self.remainder=self.number//self.factor
   return True

  self.factor=euclides_algorithm(abs(x-y), self.number)
  if(self.factor>1 and self.factor<self.number):
   self.remainder=self.number//self.factor
   return True

  #Caso fatores não tenham sido encontrados
  return False

 #10
 def congruence_find_algorithm(self):
  '''Algoritmo de busca por relações de Legendre do tipo x²= y²(mod N)'''
  #Variáveis locais
  upper:int=bin_pow(2, (self.prime_size+1))
  test1:bool=None
  test2:bool=None

  #Procedimentos
  #Loop principal
  for i in range(upper):
   self.generate_checking_vector(i) #Gerando um vetor de booleanos
   test1=self.factor_testing_algorithm() #Busca por relações de Legendre do tipo x²= y²(mod N)

   if(test1==True):
    test2=self.factors_calculation() #Cálculo de fatores não triviais
    if(test2==True):
     return

 #11
 def print_result(self):
  '''Função que exibe um relatório de execução do algoritmo'''
  print("Número a ser fatorado: ", self.number)
  print("Fator encontrado: ", self.factor)
  print("Cofator relativamente primo: ", self.remainder)
  print("Limitante para a base de primos usados no algoritmo: ", self.prime_bound)



























  
