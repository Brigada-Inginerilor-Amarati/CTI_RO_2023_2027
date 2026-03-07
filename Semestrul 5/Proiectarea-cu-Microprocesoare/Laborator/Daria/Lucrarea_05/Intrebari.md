# Cod laborator

- Specs laptop

![[Pasted image 20251121214634.png]]

- Ce returneaza programul

- ![[Pasted image 20251121214743.png]]

Screenshot dupa actualizarea codului :

# Intrebari

```C++
//1. // Folosind documentația Intel, explicați de ce se aplică următoarele operații pe biți,  
// constând în deplasarea spre dreapta cu 4, 8, 12, 16, respectiv 20 de poziții, a 
//variabilelor din porțiunea de cod de mai jos:  

vendorID[12] = '\0';  

cout << "Vendor ID: " << vendorID << "\n\n"; 
 
modelNum >>= 4;  
FamilyCODE >>= 8;  
procTYPE >>= 12;  
ExtMODE >>= 16;  
extFam >>= 20;  

cout << "Model Number: " << modelNum << "\n";  
cout << "Family Code: " << FamilyCODE << "\n";  
cout << "Extended Mode: " << ExtMODE << "\n";  
cout << "Processor Type: " << procTYPE << "\n";  
cout << "Extended Family: " << extFam << "\n";
```
Operatiile de shiftare la dreapta sunt utilizate pentru a izola diferite informatii despre registrul EAX
- Nr modelului >> 4
- codul aferent familiei procesorului >> 8
- modul extins >> 16
- tipul procesorului >> 12
- familia extinsa a procesorului >> 20


```
  
2. Explicați care este rolul instrucțiunilor: pushfd si pop eax
```
PUSHFD - salveaza continutul registrului EFLAGS (32 de biti) in stiva
POP EAX - copiaza valoarea din varful stivei in registrul EAX

Cele 2 instructiuni sunt utilizate pentru a verifica daca procesorul suporta instructiunea CPUID prin modificarea bitului de ID Flag (bitul 21 din EFLAGS)

```
3. Folosind documentația Intel furnizată, scrieți care este registrul procesorului care va  conține informațiile Extended Family și Extended Model în urma apelării instrucțiunii  CPUID și care sunt pozițiile binare revendicate de fiecare dintre acestea.
```
EAX este registrul procesorului care va contine informatiile Extended Family (bitii 20 - 27) si Extended Model (bitii 16 - 19). Este necesara apelarea CPUID cu EAX = 1

```
4. Folosind documentația Intel furnizată, scrieți care este registrul procesorului care va  contine informatiile APIC ID si Count în urma apelării instrucțiunii CPUID și care sunt pozițiile binare revendicate de fiecare dintre acestea.  
```
Registrul procesorului care va contine informatiile APIC ID (bitii 24 - 31) si Count (bitii 0 - 7 / 16 - 23 ??) este EAX. Este necesara apelarea CPUID cu EAX = 0Bh 

```
5. Folosind documentația Intel furnizată, scrieți care ar trebui să fie continutul binar al registrului EAX in urma apelului instrucțiunii CPUID pentru procesoarele Intel 486 SX.  
```
Procesorul mentionat nu suporta instructiunea CPUID. Conform documentatiei Intel, in urma apelarii CPUID, registrul EAX ar trebui sa contina valoarea 0

```
6. Folosind documentația Intel furnizată, scrieți care ar trebui să fie continutul binar al registrului EAX in urma apelului instrucțiunii CPUID pentru procesoarele Intel Pentium Pro, precum și pentru procesoarele Intel Core i7.  
```
Registrul EAX va contine valoarea 00000600h in urma apelului instructiunii CPUID pentru procesoarele Intel Premium Pro.
Pentru procesoarele Intel Core i7, registrul EAX va contine valoarea 000106A0h

```
7. Explicați la ce este folosită variabila unsigned long int brandID din codul exemplu.  
Care biți, din care registru, vor fi salvați în această variabilă?
```
Unsigned long int brandID este utilizata pentru a salva informatii despre brand-ul procesorului.
In aceasta variabila vor fi setati bitii 0-7 din registrul EBX/ Este necesara apelarea CPUID cu EAX = 1