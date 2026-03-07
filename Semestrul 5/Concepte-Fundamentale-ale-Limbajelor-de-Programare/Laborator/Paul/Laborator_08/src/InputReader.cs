/*
CititorIntrare va avea un EventHandler<string> numit OnKeyPressed și o metodă ReadKeys() care citește de la consolă folosind metoda Console.ReadLine() până când este citit un șir gol.
După citirea fiecărui șir, evenimentul OnKeyPressed va fi invocat.
*/

namespace Laborator_08;

class InputReader
{
    public event EventHandler<string> OnKeyPressed;

    public void ReadKeys()
    {
        string input = Console.ReadLine();

        while (input != "")
        {
            OnKeyPressed?.Invoke(this, input);
            input = Console.ReadLine();
        }
    }
}
