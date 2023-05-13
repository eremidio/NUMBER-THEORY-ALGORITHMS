--VAMOS IMPLEMENTAR O ALGORITMO ORIGINAL DE EUCLIDES PARA CALCULAR O MMC DE DOIS NÚMEROS EM HASKELL

--FUNÇÃO
mmc::Integer->Integer->Integer
mmc x y
 | x==y {-Expresão logica a ser avaliada-} = x {-Resultado correspondendo a condição. Este éo caso trivial-}
 | x>y = mmc (x-y) y
 | x<y = mmc  x (y-x)
--FUNÇÃO PRINCIPAL
main::IO()
main=do
 putStrLn("Digite um número inteiro")
 num1_<-getLine
 let num1= read num1_::Integer
 putStrLn("Digite outro número inteiro")
 num2_<-getLine
 let num2= read num2_::Integer
 putStrLn("O MMC de "++show num1++" e "++show num2 ++" é "++ show (mmc num1 num2))
 
