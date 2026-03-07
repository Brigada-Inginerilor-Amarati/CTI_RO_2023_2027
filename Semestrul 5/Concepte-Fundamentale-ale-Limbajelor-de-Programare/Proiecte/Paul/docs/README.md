# RAPORTARE CNATDCU

## Universitatile din Romania primesc pe baza unui indicator de cercetare o finantare suplimentara de la bugetul de stat

Acest indicator se calculeaza pe baza raportarilor individuale a fiecarui cadru didactic.

Raportarile se fac sub forma unui fisier Excel xlsx in care sunt trecute publicatiile pe baza unor campuri:
titlu, cod DOI, cod WOS etc.

Se va mai prevede un camp pentru autorul fisierului pentru a putea sti cine a facut raportarea.

Sa se scrie o aplicatie care modeleaza o colectie de publicatii si are urmatoarele functionalitati:

- primeste la intrare o lista de fisiere xlsx, cate un fisier de la fiecare cercetator, si le incarca in lista de publicatii din memorie;

- in cazul in care se incearca introducerea de publicatii cu codurile ISBN sau WOS identice cu publicatii existente atunci introducerea acelei publicatii in lista nu se va mai face (nu se permit duplicate);

- afiseaza o statistica calculand sume pe coloanele cu valori numerice (de ex cate sunt ISI Rosu, cate sunt ISI Galben etc.)

- genereaza un fisier text centralizat cu toate campurile de publicatii in format CSV.

Pentru a citi fișiere Excel (.xlsx) într-o aplicație de consolă C#, poți folosi librăria ClosedXML, care simplifică interacțiunea cu fișierele Excel fără a necesita instalarea Microsoft Excel pe calculator.

1. Instalează ClosedXML
   În Visual Studio, deschide Package Manager Console și rulează comanda:

Install-Package ClosedXML

Alternativ, poți adăuga pachetul din NuGet Package Manager căutând ClosedXML.

2. Exemple de cod

După instalare, poți folosi codul de mai jos pentru a citi date dintr-un fișier .xlsx.

```csharp
using System;
using ClosedXML.Excel;

class Program
{
static void Main(string[] args)
{
// Specifică calea către fișierul Excel
string filePath = @"C:\calea\catre\fisier.xlsx";

        // Deschide fișierul Excel
        using (var workbook = new XLWorkbook(filePath))
        {
            // Selectează foaia de lucru (sheet-ul) dorită
            var worksheet = workbook.Worksheet(1); // sau numele foii: workbook.Worksheet("Sheet1")

            // Iterează prin rândurile și coloanele foii de lucru
            foreach (var row in worksheet.RowsUsed())
            {
                foreach (var cell in row.CellsUsed())
                {
                    Console.Write(cell.GetValue<string>() + "\t");
                }
                Console.WriteLine();
            }
        }
    }

}
```

Deschiderea fișierului: new XLWorkbook(filePath) deschide fișierul .xlsx specificat.

Selectarea Foii de Lucru: workbook.Worksheet(1) alege prima foaie de lucru din fișier. Poți folosi și numele foii, de exemplu: workbook.Worksheet("Sheet1").

Iterarea prin celule: Folosim RowsUsed() pentru a itera doar prin rândurile folosite, iar CellsUsed() pentru a obține doar celulele cu date.

Observații
ClosedXML gestionează automat închiderea fișierului și eliberarea resurselor după utilizare datorită using statement-ului.

Referință pentru valori:

```csharp
cell.GetValue<string>() // extrage valoarea din celulă și o converteste la tipul specificat (aici string).
```

Acest cod ar trebui să afișeze datele din fișierul Excel în consolă, fiecare celulă fiind separată de un tab pentru lizibilitate.
