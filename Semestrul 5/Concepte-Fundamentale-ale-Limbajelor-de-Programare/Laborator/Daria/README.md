# Ghid Utilizare Proiecte .NET Console

Acesta este un ghid rapid pentru crearea și rularea proiectelor C# din linia de comandă.

## 1. Creare Proiect Nou
Pentru a crea un proiect nou de tip consolă, folosește comanda:

```bash
dotnet new console -o NumeProiect
```
> *Exemplu: `dotnet new console -o Laborator_10`*

## 2. Navigare în Folderul Proiectului
După ce ai creat proiectul, trebuie să intri în directorul acestuia:

```bash
cd NumeProiect
```

## 3. Rulare Proiect
Pentru a rula codul sursă:

```bash
dotnet run
```

## Alte Comenzi Utile

### Compilare (Build)
Dacă vrei doar să verifici dacă există erori, fără să rulezi programul:
```bash
dotnet build
```

### Restaurare Pachete
Dacă ai descărcat proiectul și lipsesc dependențele:
```bash
dotnet restore
```
