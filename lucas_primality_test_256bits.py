#VAMOS CRIAR UM PROGRAMA QUE IMPLMENTA UMA VERSÃO APRIMORADA DO TESTE DE PRIMALIDADE DE LUCAS

'''
USAMOS ROTINAS OTIMIZADAS DAS BIBLIOTECAS SymPy PARA FATORAÇÃO DE NÚMEROS INTEIROS E gmpy2 PARA ARITMÉTICA DE GRANDES NÚMEROS INTEIROS.
A PRESENTE IMPLEMENTAÇÃO FUNCIONA BEM PARA INTEIROS ATÉ 10^60, ACIMA DESSE LIMITE OTEMPO DE EXECUÇÃO AUMENTA, PORÉM NÚMEROS DA ORDEM DE
10^100 PODEM SER TESTADOS. O TESTE É DETERMINÍSTICO.

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/lucas_primality_test.h


'''

#IMPORTANDO BIBLIOTECAS USADAS NO ALGORITMO
from sympy import factorint
import gmpy2


#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#FUNÇÕES

#1
def extract_prime_factors(n:int)->list:
    '''Função que para um inteiro n aloca os fatores de (n-1) em uma lista'''

    #Variáveis locais
    factor_dict:dict=factorint((n-1)) #Invocando rotinas otimizadas para fatoração da biblioteca SymPy
    prime_factor_list:list=[]

    #Procedimentos
    #Alocando fatores primos em uma lista
    for keys, values in factor_dict.items():
        prime_factor_list.append(keys)

    #Resultado
    return prime_factor_list



def lucas_primality_test(n:int)->bool:
    '''Função que implementa o teste de primalidade Lucas'''
    #Casos triviais: n contém fatores primos inferiores a 100
    prime_seed=[2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97]

    for prime in prime_seed:
        if(n==prime):
            return True
        if((n%prime)==0):
            return False
    
    #Variáveis locais
    prime_factor_list=extract_prime_factors(n) #Alocando os fatores de (n-1) em uma lista 
    largest_prime_factor=prime_factor_list[(len(prime_factor_list)-1)]
    r:int=(n-1)//(2*largest_prime_factor)
    exponent_list:list=[]
    false_checks:int=0
    root:int=int(gmpy2.sqrt(n))


    #Procedimentos
    #Teste 1: testando se n-1 possui um fator primo da ordem n^(1/2)
    if( largest_prime_factor>=((r-1)//2) ):
        r<<=1

        for a in prime_seed:
            if(gmpy2.powmod(a, (n-1), n)!=1): #Teste de Fermat (detectando compostos)
                return False
            if(pow(a, r, n)!=1):
                return True
            


    #Teste 2: teste de Lucas usando primos inferiores a 100, caso (n-1) tenha apenas pequenos fatores primos
    #Computando uma lista de possíveis divisores  da ordem do grupo inteiros a menos de uma congruência módulo n     
    for prime in prime_factor_list:
        exponent_list.append(((n-1)//prime))

    #Realizando o teste com os expoentes calculados: a condição do teste de Fermat foi checada na etapa anterior
    for a in prime_seed:
        if(gmpy2.powmod(a, (n-1), n)!=1): #Teste de Fermat (detectando compostos)
            return False

        false_checks=0 #Ajuste de variáveis
        
        for exponent in exponent_list:
            if(gmpy2.powmod(a, exponent, n)==1):
                false_checks+=1

        #Testando se um certificado de primalidade foi encontrado:
        if(false_checks==0):
            return True


    #Caso o número em questão falhe nos testes acima ele é declarado composto:
    return False
    
