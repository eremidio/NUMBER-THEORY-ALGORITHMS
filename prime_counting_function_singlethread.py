#VAMOS CRIAR UM PROGRAMA QUE COMPUTA A FUNÇÃO π(x) DE CONTAGEM DE NÚMEROS PRIMOS USANDO UMA PENEIRA DE ERATÓSTENES SEGMENTADA

#--------------------------------------------------------------------------------------------------------------------------------------------------
#IMPORTANDO BIBLIOTECAS EM PYTHON
from  math import  sqrt


#--------------------------------------------------------------------------------------------------------------------------------------------------
#ETAPA 1: COMPUTANDO UMA LISTA DE PRIMOS ATÉ  n^(1/2)
def fast_prime_checking(n:int)-> bool:
    ''' Função que determina se um inteiro é primo ou não'''
    #Casos  triviais: primos menores  do que 100
    prime_seed:list=[2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97]
    if(n in prime_seed):
        return True

    if(n<2):
        return False

    #Variáveis locais
    divisor:int=0
    seed:list=[7,11,13,17,19,23,29,31]
    root:int=int(sqrt(n))
    
    #Caso geral: n>100
    if(n%2==0  or n%3==0 or n%5==0):
        return False

    
    for i in range(n):
        for j in range(8):
            divisor=30*i+seed[j]

            if(n%divisor==0):
                return False
            if(divisor>root):
                return True


def  generate_prime_list(n:int)->set:
    '''Função que computa uma lista de primos até a raíz quadrada de um inteiro'''
    #Variáveis locais
    root:int=int(sqrt(n))+1
    prime_set:set=set([])

    #Procedimentos
    for i in range(root):
        if(fast_prime_checking(i)):
            prime_set.add(i)

    #Resultado
    prime_set=sorted(prime_set)
    return prime_set


#--------------------------------------------------------------------------------------------------------------------------------------------------
#ETAPA 2: COMPUTANDO PRIMOS DE n^(1/2) A n USANDO UMA PENEIRA SEGMENTADA

def counting_primes_interval(prime_set:set,  number_set:set, min_number:int, max_number:int)->int:
    '''Função que realiza a contagem de primos em um intervalo de segmentação'''

    #Variáveis locais
    max_root:int=int(sqrt(max_number))
    minimum_multiplier:int=0
    tester:int=0

    #Procedimentos

    #Descartando não primos no dado intervalo em questão
    for prime in prime_set:
        if(prime<11):
            continue
        if(prime>max_root):
             break
            
        minimum_multiplier=(min_number//prime)-5

        for x in range(minimum_multiplier, max_number, 1):
            tester=x*prime
            if(tester>max_number):
                break
            else:
                number_set.discard(tester)
   
    #Computando o número de primos em um dado intervalo
    return len(number_set)



#--------------------------------------------------------------------------------------------------------------------------------------------------
#ETAPA 3: IMPLEMENTANDO A FUNÇÃO DE CONTAGEM DE PRIMOS ATÉ 10^13
def set_settings(minimum:set, maximum:set)->set:
    '''Função que define os elementos de um conjunto'''

    #Procedimentos
    #Checando os números de elementos
    number_set:set=set([])

    #Adicionando elementos no conjunto
    if(minimum%2==0):
      minimum+=1

    for n in range(minimum, (maximum+1), 2):
        if((n%30) in {1,7,11,13,17,19,23,29} and (n%7)>0):
            number_set.add(n)
        
    #Resultado
    return number_set

def prime_counting_function(limit:int,  sieve_size:int):
    ''''Função de contagem de números primos até um determinado valor'''
    #Casos triviais: limit<100
    if(limit<100):
        mini_counter:int=0
        for i in range(limit):
            if(fast_prime_checking(i)):
               mini_counter+=1

        return mini_counter
        

    #Casos gerais: limit>100
 
    #Váriaveis locais:
    root_prime_set:set=generate_prime_list(limit)
    prime_counter:int = len(root_prime_set)
    root:int =int(sqrt(limit))
    min_element:int=(root+1)
    max_element:int=min_element+sieve_size
    number_set:set=set([])
    parcel:int=0

  
    #Contagem de primos em intervalos segmentados
    while(True):
        number_set:set=set_settings(min_element, max_element)
        parcel=counting_primes_interval(root_prime_set, number_set, min_element, max_element)
        prime_counter+=parcel


        #Fim do Loop principal
        if(max_element==limit):
            break

        #Atualizando variáveis para a próxima iteração
        min_element=(max_element+1)
        max_element=min_element+sieve_size

        if(max_element>limit):
            max_element=limit


    #Resultado
    return prime_counter
        



#--------------------------------------------------------------------------------------------------------------------------------------------------
#PROGRAMA PRINCIPAL

#Recebendo input do usuário
number:int = int(input('Limite superior do intervalo de contagem de números primos: '))
sieve_size:int = int(input('Valor do intervalo de segmentação: '))

pi:int=prime_counting_function(number, sieve_size)

print(f"π({number}): {pi}")
