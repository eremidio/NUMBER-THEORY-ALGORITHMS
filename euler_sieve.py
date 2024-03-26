#VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA A PENEIRA DE EULER PARA COMPUTAR NÚMEROS PRIMOS
#Nota: usaremos a estrutura de dados set em python como principal container durante a execução do algoritmo

'''

A PENEIRA DE EULER É UM DOS MAIS EFICIENTES ALGORITMOS PARA COMPUTAR UMA LISTA DE NÚMEROS PRIMOS ATÉ UM DETERMINADO VALOR.

A IDEIA DO ALGORITMO É COMO SE SEGUE:
1. COMEÇAMOS COMO UMA LISTA INICIADA EM EM 2 ATÉ O LIMITE DESEJADO.
2. O PRIMEIRO ELEMENTO DA LISTA É ADICIONADO A LISTA DE PRIMOS.
3. UMA NOVA LISTA QUE CONSISTE NO PRODUTO DA LISTA ORIGINAL VEZES O PRIMO COMPUTADO É GERADO. OS TERMOS OBTIDOS DA LISTA ORIGINAL.
(NESTA ETAPA PODEMOS USAR UM CONJUNTO MENOR QUE COBRE NO MÁXIMO O VALO)
4. AS ETAPAS 2 E 3 SÃO REPETIDOS ATÉ QUE O PRIMO ASSINALADO NA ETAPA 2 SEJA SUPERIOR A RAÍZ QUADRADA DO LIMITE EM QUESTÃO.
5. SE NO FINAL RESTAR ELEMENTOS NO CONJUNTO ORIGINAL ELES SÃO INCORPORADOS AO CONJUNTO DE NÚMEROS PRIMOS.

REFERÊNCIAS: https://programmingpraxis.com/2011/02/25/sieve-of-euler/
             Prime Numbers: The Holy Grail Of Mathematics: A brief introduction to prime numbers by Thamer Naouech

'''

#IMPORTANDO BIBLIOTECAS USADAS NO ALGORITMO
from math import sqrt

#FUNÇÕES USADAS NO ALGORITMO

def generate_set(minimum:int, maximum:int)->set:
 ''''Função que gera um conjunto de valores em um dado intervalo'''

 #Variáveis locais
 number_set:set=set([])

 #Procedimentos
 for i in range(minimum, (maximum+1), 1):
  number_set.add(i)
        
 #Resultados
 return number_set

def generate_reduction_set(prime:int, max_int:int)-> set:
 '''Função que gera um conjunto de números compostos a serem eliminados da lista de números primos'''
 
 #Variáveis locais
 reduction_set:set=set([])
 upper:int=max_int//prime

 #Procedimentos
 for i in range(1, (upper+1)):
  reduction_set.add(i*prime)
       
 #Resultado
 return reduction_set



def euler_sieve(limit:int)->set:
 '''Função que implementa a peneira de Euler para computar uma lista de números'''

 #Variáveis locais
 number_set:set=generate_set(2, limit)
 max_root:int=int(sqrt(limit))
 prime_set:set=set([])
 current_prime:int=0
 upper_bound:int=0
 reduction_set:set=None
 final_prime_set:set=None

 #Procedimentos
 while(1):
  #Atualizando variáveis 
  current_prime=min(number_set)
  upper_bound=max(number_set)

  #Fim do loop
  if(current_prime>max_root):
   break

  #Atualizando os conjuntos usados no algoritmo
  prime_set.add(current_prime)
  number_set.discard(current_prime)
  reduction_set=generate_reduction_set(current_prime, upper_bound)

  number_set-=reduction_set

 #Computando a lista final de primos
 final_prime_set=prime_set.union(number_set)
 final_prime_set=sorted(final_prime_set)
 return final_prime_set



#----------------------------------------------------------------------------------------------------------------------------------------------------------------------
#PROGRAMA PRINCIPAL

#Recebendo input do usuário
n:int=int(input('Digite um limitante superior para sua sequência de números primos: '))

#Computando a lista de números primos até o valor especificado
prime_set:set=euler_sieve(n)
print('\nLista de números primos até ', n, ': ', list(prime_set))


