/*
Constructorul clasei AscultatorComplex va primi un int numit strNo care specifică numărul de șiruri reținute și un obiect CititorIntrare.
Constructorul se va abona la evenimentul OnKeyPressed din CititorIntrare.
AscultatorComplex va avea o metodă HandleKeyPressed (abonată la eveniment), care primește șirul de la eveniment și îl adaugă într-o listă de șiruri.
Doar ultimele strNo șiruri vor fi păstrate în listă (cele mai vechi vor fi eliminate). Dacă metoda primește „afișează ultimul”, va afișa ultima intrare din listă și va returna. Dacă primește „afișează toate”, va afișa toate șirurile din listă și va returna.
*/

namespace Laborator_07;

class ComplexListener
{
    private int strNo;
    private InputReader inputReader;
    private List<string> strings;

    public ComplexListener(int strNo, InputReader inputReader)
    {
        this.strNo = strNo;
        this.strings = new List<string>(strNo);
        this.inputReader = inputReader;
        this.Subscribe();
    }

    public void Subscribe()
    {
        this.inputReader.OnKeyPressed += HandleKeyPressed;
    }

    public void Unsubscribe()
    {
        this.inputReader.OnKeyPressed -= HandleKeyPressed;
    }

    public void HandleKeyPressed(object? sender, KeyEventArgs e)
    {
        if (e.Key == "afiseaza ultimul")
        {
            Console.WriteLine(strings.Last());
            e.Handled = true;
            return;
        }

        if (e.Key == "afiseaza toate")
        {
            Console.WriteLine(string.Join(", ", strings));
            e.Handled = true;
            return;
        }

        if (strings.Count >= strNo)
            strings.RemoveAt(0);

        strings.Add(e.Key);
    }
}
