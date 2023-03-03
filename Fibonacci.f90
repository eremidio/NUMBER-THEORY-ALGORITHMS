!UM PROGRAMA SIMPLES PARA SE CALCULAR A SEQUÊNCIA DE FIBONACCI DADO UM LIMITANTE SUPERIOR ESCRITO EM FORTRAN
program Fibonacci
integer::limit, i
character (len=1)::r
integer, dimension(1000000)::f


write(*,*) "Qual o valor do limite?"
read(*,*)limit

f(1)=1
f(2)=1
write(*,*) f(1)
write(*,*) f(2)

do i=2, 999999
f(i+1)=f(i)+f(i-1)

 if (f(i+1)<limit) then
write(*,*) f(i+1)
 elseif ((f(i+1)>=limit)) then 
exit
 endif
enddo

end program Fibonacci
