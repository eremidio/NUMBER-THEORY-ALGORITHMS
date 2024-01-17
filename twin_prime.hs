--VAMOS CRIAR UM PROGRAMA EM HASKELL QUE TESTA SE UM DADO PARA DE NÚMEROS PRIMOS É GÊMEO 
{-
PRIMOS GÊMEOS SÃO PARES DE NÚMEROS PRIMOS DIFERINDO POR DUAS UNIDADES, ISTO É, DADO UM INTEIRO p PRIMO (p+2) TAMBÉM É PRIMO. NÚMEROS PRIMOS QUE NÃO OBEDECEM A ESTA
RELAÇÃO SÃO DENOMINADOS PRIMOS ISOLADOS.

CONJECTURAS EXITEM ACERCA DA INFINITUDE DE PRIMOS GÊMEOS E DA DISTRIBUIÇÃO DE PRIMOS GÊMEOS NO CONJUNTO DOS NÚMEROS NATURAIS (EM ANALOGIA COM A DISTRIBUIÇÃO DE PRIMOS
DE UMA FORMA).

A SEGUINTE RELAÇÃO DE CONGRUÊNCIA FORNECE UM SIMPLES TESTE PARA DETERMINAR SE UM PAR (p, p+2) SÃO PRIMOS GÊMEOS: 4[(p-1)!+1] = (-p) (mod p(p+2)).

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Twin_prime#Large_twin_primes

-}

--FUNÇÕES
--Função que calcula o fatorial do antecessor de um número a menos de uma relação de congruência
modular_factorial::Integer->Integer->Integer
modular_factorial n k
    |n==1 = 1
    |otherwise = mod (n*(modular_factorial (n-1) k)) k

--Função intermédiaria que calcula o valor da expressão 4[(p-1)!+1] (mod p(p+2)) para possíveis primos gêmeos p, p+2
twin_prime_congruent::Integer->Integer
twin_prime_congruent n = mod (4*( (modular_factorial (n-1) (n*(n+2))) +1 )) (n*(n+2))

--Função que determina se um pares de inteiros ímpares são primos gêmeos
twin_prime_check::Integer->Bool
twin_prime_check n
    |twin_prime_congruent n==(n*(n+1)) = True
    |otherwise = False


--FUNÇÃO PRINCIPAL
main::IO()
main = do
 --Recebendo input do usuário
 putStrLn("Digite um possível candidato 'p' a um par de números primos gêmeos (p, p+2): ")
 p1<-getLine
 let p = read p1::Integer

 --Testando se um par de primos gêmeos foi encontrado
 let check = twin_prime_check p
 
 if (check==True)
  then putStrLn("("++(show p) ++ ","++ show (p+2) ++") formam um par de primos gêmeos.")
  else putStrLn("("++(show p) ++ ","++ show (p+2) ++") não formam um par de primos gêmeos.")

