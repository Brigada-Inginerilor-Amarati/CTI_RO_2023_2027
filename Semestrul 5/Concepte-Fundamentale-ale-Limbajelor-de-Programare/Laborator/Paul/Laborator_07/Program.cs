/*
Creați un proiect cu 3 clase: CititorIntrare, AscultatorCaracter, AscultatorComplex.

    CititorIntrare va avea un EventHandler<string> numit OnKeyPressed și o metodă ReadKeys() care citește de la consolă folosind metoda Console.ReadLine() până când este citit un șir gol. După citirea fiecărui șir, evenimentul OnKeyPressed va fi invocat.
    Constructorul clasei AscultatorCaracter va primi un caracter care va fi salvat ca un câmp și un obiect CititorIntrare. Constructorul se va abona la evenimentul OnKeyPressed din CititorIntrare. AscultatorCaracter va avea o metodă HandleKeyPressed (abonată la eveniment), care primește șirul de la eveniment și afișează un mesaj dacă șirul conține caracterul specificat în constructor.
    Constructorul clasei AscultatorComplex va primi un int numit strNo care specifică numărul de șiruri reținute și un obiect CititorIntrare. Constructorul se va abona la evenimentul OnKeyPressed din CititorIntrare. AscultatorComplex va avea o metodă HandleKeyPressed (abonată la eveniment), care primește șirul de la eveniment și îl adaugă într-o listă de șiruri. Doar ultimele strNo șiruri vor fi păstrate în listă (cele mai vechi vor fi eliminate). Dacă metoda primește „afișează ultimul”, va afișa ultima intrare din listă și va returna. Dacă primește „afișează toate”, va afișa toate șirurile din listă și va returna.

În metoda main, veți crea un CititorIntrare și apoi doi AscultatoriCaracter și un AscultatorComplex. După aceea, cititorul va fi folosit pentru a citi șiruri ca intrare.
*/

namespace Laborator_07;

class Program
{
    static void Main(string[] args)
    {
        InputReader inputReader = new InputReader();
        ComplexListener complexListener = new ComplexListener(4, inputReader);
        CharacterListener characterListener1 = new CharacterListener('a', inputReader);
        CharacterListener characterListener2 = new CharacterListener('b', inputReader);

        inputReader.ReadKeys();
    }
}
