function accept(p)
public v
do accept12   with p
return v

Proced accept12
param p
public   v
v=space(30)
define  form f1
f1.Text ='Input'
f1.mdi=.f.
f1.height=10
f1.width=70
defi text t1 of f1 at 1,2 prop Text 'Valoare', fontsize 12, fontbold .t.
defi entryfield e1 of  f1 at 2,15 prop width 20, fontsize 12, fontbold .t.
f1.e1.width=50
f1.e1.datalink='v'
f1.t1.text=p
f1.t1.width=30
defi pushbutton b1 of f1 at 4,15 prop text 'OK', fontsize 12, fontbold .t.

f1.b1.onclick ={;do pOK }
    f1.readmodal()
   return

procedure pOK
public v
v= f1.e1.value
f1.close()
return