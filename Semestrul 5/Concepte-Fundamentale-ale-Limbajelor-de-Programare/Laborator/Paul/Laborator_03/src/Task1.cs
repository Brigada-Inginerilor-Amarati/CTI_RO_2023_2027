// 1. Implementați o metodă statică, care primește doi întregi ca parametri ref și îi interschimbă.
namespace Laborator_03;

public class Task1
{
    public static void Swap(ref int a, ref int b)
    {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }

    public static void Main(string[] args)
    {
        var a = int.Parse(args[0]);
        var b = int.Parse(args[1]);

        Console.WriteLine($"Before: {a}, {b}");
        Swap(ref a, ref b);
        Console.WriteLine($"After: {a}, {b}");
    }
}
