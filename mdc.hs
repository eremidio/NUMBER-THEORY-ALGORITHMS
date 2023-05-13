--VAMOS IMPLEMENTAR O ALGORITMO ORIGINAL DE EUCLIDES PARA CALCULAR O MDC DE DOIS NÚMEROS EM HASKELL

--FUNÇÃO
mdc::Integer->Integer->Integer
mdc x y
 | x==y {-Expresão logica a ser avaliada-} = x {-Resultado correspondendo a condição. Este é o caso trivial-}
 | x>y = mdc (x-y) y
 | x<y = mdc  x (y-x)
--FUNÇÃO PRINCIPAL
main::IO()
main=do
 putStrLn("Digite um número inteiro")
 num1_<-getLine
 let num1= read num1_::Integer
 putStrLn("Digite outro número inteiro")
 num2_<-getLine
 let num2= read num2_::Integer
 putStrLn("O MDC de "++show num1++" e "++show num2 ++" é "++ show (mdc num1 num2))
 
