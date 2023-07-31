#PROGRAMA PARA GERAR AS SEQUÊNCIAS DE FAREY
#EXEMPLO ADAPTADO DA INTERNET

def farey_sequence(n: int, descending: bool = False) -> None:
    """Print the n'th Farey sequence. Allow for either ascending or descending."""
    (a, b, c, d) = (0, 1, 1, n)
    if descending:
        (a, c) = (1, n - 1)
    print("{0}/{1}".format(a, b))
    while (c <= n and not descending) or (a > 0 and descending):
        k = (n + b) // d
        (a, b, c, d) = (c, d, k * c - a, k * d - b)
        #print(a, b, c, d, k)
        print("{0}/{1}".format(a, b))


#TESTANDO A FUNÇÃO
n1:int= int(input('Digite um inteiro: '))
asc_desc:int=int(input('Digite 1 para gerar a sequência de Farey em ordem crescente.\nDigite 0 para gerar a sequência de Farey em ordem decrescente.: '))

if(asc_desc==1):
 farey_sequence(n1, False)
if(asc_desc==0):
 farey_sequence(n1, True)
