/*
Constructorul clasei AscultatorCaracter va primi un caracter care va fi salvat ca un câmp și un obiect CititorIntrare.
Constructorul se va abona la evenimentul OnKeyPressed din CititorIntrare.
AscultatorCaracter va avea o metodă HandleKeyPressed (abonată la eveniment), care primește șirul de la eveniment și afișează un mesaj dacă șirul conține caracterul specificat în constructor.
*/

namespace Laborator_07;

class CharacterListener
{
    private char character;
    private InputReader inputReader;

    public CharacterListener(char character, InputReader inputReader)
    {
        this.character = character;
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
        if (e.Handled)
        {
            return;
        }

        if (e.Key.Contains(character))
        {
            Console.WriteLine($"Character {character} found in {e.Key}");
        }
    }
}
