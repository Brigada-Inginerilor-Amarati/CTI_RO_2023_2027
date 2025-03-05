set talk off
clear
x=val(accept('Dati x in grade:'))
x=dtor(x)
s=x
t=x
limita=15
eps=1e-12
k=3
do while abs(t)>eps
	t=(-t*x*x)/(k*(k-1))
s=s+t
k=k+2
enddo

?'sin(x):', sin(x)
?'Sinus calculat', s
?'numar de termeni:',ceil(k-3)/2
return
