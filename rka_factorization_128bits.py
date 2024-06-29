#VAMOS IMPLEMENTAR UMA VERSÃO DO ALGORITMO RKA PARA FATORAR NÚMEROS INTEIROS USANDO BIBLIOTECAS PARA PRECISÃO MÚLTIPLA

'''
PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/rka_factorization_algorithm.h
'''

#IMPORTANDO BIBLIOTECAS USADAS NO ALGORITMO
from math import log, floor, isqrt
import gmpy2



#--------------------------------------------------------------------------------------------------------------------
#FUNÇÕES
def rka_factorization_algorithm(n):
    '''Função que implementa o algoritmo de RKA para fatorar números inteiros'''
    
    # Pré-Computando parâmetros usados no algoritmo
    e = floor(log(n, 2))
    k = ((n + 1) // 2) - (isqrt(n) + 1)
    c = gmpy2.powmod(4, k, n)
    
    if c == 1:
        x = k
    else:
        A = [gmpy2.powmod(4, z, n) for z in range((e * e) + 1)]
        for z in range(1, (e * e)):
            if c == A[z]:
                x = k - z
                break
        else:
            h = pow(pow(4, (e * e)), (-1), n)
            m = 1
            while (1):
                c = (c * h) % n
                for z in range(1, (e * e)):
                    if (c == A[z]):
                        x = k - (m * e * e) - z
                        break
                else:
                    m += 1
                    continue
                break
    
    # Computando fatores primos
    while (not x & 1 and gmpy2.powmod(4, x, n)) == 1:
        x >>= 1
    if (gmpy2.powmod(4, x, n) != 1):
        x <<= 1
    
    a = 2
    root = isqrt(n)
    while (a < root):
        factor = gmpy2.gcd(gmpy2.powmod(a, x, n) - 1, n)
        if (1 < factor < n):
            break
        factor = gmpy2.gcd(gmpy2.powmod(a, x, n) + 1, n)
        if (1 < factor < n):
            break
        a += 1
    
    cofactor = n // factor
    print(f"Fatores de {n}: {factor} e {cofactor}") 


#--------------------------------------------------------------------------------------------------------------------
#FUNÇÃO PRINCIPAL 

#Recebendo input do usuário
n:int=int(input('Digite um inteiro a ser fatorado: '))

#Fatorando o número inteiro em questão usando o algoritmo RKA
rka_factorization_algorithm(n)


