namespace Laborator_03;

class Program
{
    static Coords Midpoint(Coords a, Coords b)
    {
        return new Coords((a.X + b.X) / 2, (a.Y + b.Y) / 2);
    }

    static void Main()
    {
        Task1.Main(new string[] { "2", "3" });

        Coords a = new Coords(1, 2);
        Coords b = new Coords(3, 4);
        Coords midpoint = Midpoint(a, b);
        Console.WriteLine($"Midpoint: ({midpoint.X}, {midpoint.Y})");

        Account account = new Account("Blabla", 1000);
        Console.WriteLine($"Account: {account.Name}, Balance: {account.Balance}");

        double balance = 0;
        bool result = account.Withdraw(500, out balance);
        Console.WriteLine($"Withdrawal result: {result}");
        result = account.Withdraw(1000, out balance);
        Console.WriteLine($"Withdrawal result: {result}");
    }
}
