{-
VAMOS ESCRVER UM PROGRAMA QUE CALCULA RAÍZES DE VÁRIAS ORDENS EM HASKELL, USANDO O ALGORITMO DE RAPOHSON NEWTON.
A IDEIA BÁSICA DESTE ALGORITMO É USAR UMA SEQUÊNCIA DE NÚMEROS X(0), X(1), ... TAL QUE
X(N+1)=X(N)+(F'(X(N))/F(X(N))), ONDE F(X) E F'(X) DENOTAM UMA FUNÇÃO E SUA DERIVADA. PARA UMA FUNÇÃO DO TIPO F(X)=X^(n)-A
O CÁLCULO NOS MOSTRA QUE X(N+1)=(1/n)[(n-1)X(N)+*(A/X(N)^(n-1))]. / 

-}

--FUNÇÕES
--Função que calcula o próximo termo da sequência de números

term::Double->Double->Double->Double
term n x y = (1/n)*((n-1)*x+(y/(x**(n-1)))) --n é a ordem da raíz , x é o termo da série e y é o valor do radicando

--Função que calcula recursivamente uma raíz do termo
root::Double->Double->Double->Double
root n x y
 | abs(x- (term n x y))<0.0000000000001 = x
 | otherwise = root n (term n x y) y


--FUNÇÃO PRINCIPAL
main::IO()
main = do 
 putStr("Digite um inteiro correspondendo a ordem da raíz a ser calculada:\n")
 x1<-getLine
 let n = read x1::Double
 putStr("Digite o valor do radicando:\n")
 x2<-getLine
 let y = read x2::Double
 putStr("Digite um palpite inicial para a raíz do número a ser calculado:\n")
 x3<-getLine
 let x = read x3::Double
 putStrLn("A  raíz de "++ show y ++ " de ordem "++show n++" é "++ show(root n x y))


