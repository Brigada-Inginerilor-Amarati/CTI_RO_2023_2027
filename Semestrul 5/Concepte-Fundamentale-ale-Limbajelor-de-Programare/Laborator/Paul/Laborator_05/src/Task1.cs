/*
Teme

1. Implementați o metodă statică RemoveAt, care primește un array, lungimea array-ului și un index. Metoda elimină elementul de la indexul dat din array.

public static void RemoveAt(int[] array, ref int length, int n)
*/

class Task1
{
    public static void RemoveAt(int[] array, ref int length, int index)
    {
        for (int i = index; i < length - 1; i++)
        {
            array[i] = array[i + 1];
        }
        length--;
    }

    public static void PrintArray(int[] array, int length)
    {
        for (int i = 0; i < length; i++)
            Console.Write(array[i] + " ");

        Console.WriteLine();
    }

    public static void Main()
    {
        int[] array = { 1, 2, 3, 4, 5 };
        int length = array.Length;

        Console.WriteLine("Before: ");
        PrintArray(array, length);

        RemoveAt(array, ref length, 2);

        Console.WriteLine("After: ");
        PrintArray(array, length);
    }
}
