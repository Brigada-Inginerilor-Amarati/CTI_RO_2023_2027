/*
CititorIntrare va avea un EventHandler<string> numit OnKeyPressed și o metodă ReadKeys() care citește de la consolă folosind metoda Console.ReadLine() până când este citit un șir gol.
După citirea fiecărui șir, evenimentul OnKeyPressed va fi invocat.
*/

namespace Laborator_07;

public class KeyEventArgs : EventArgs
{
    public string Key { get; }
    public bool Handled { get; set; }

    public KeyEventArgs(string key)
    {
        Key = key;
        Handled = false;
    }
}

class InputReader
{
    public event EventHandler<KeyEventArgs> OnKeyPressed;

    public void ReadKeys()
    {
        string input = Console.ReadLine();

        while (input != "")
        {
            OnKeyPressed?.Invoke(this, new KeyEventArgs(input));
            input = Console.ReadLine();
        }
    }
}
