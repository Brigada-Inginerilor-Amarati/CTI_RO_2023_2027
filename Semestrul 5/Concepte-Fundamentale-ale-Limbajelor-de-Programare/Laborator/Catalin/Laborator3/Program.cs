

class Program
{

    public class Account
    {
        public string Name { get;}
        public double Balance { get;}
        
        public Account(string name, double balance)
        {
            Name = name;
            Balance = balance;
        }


        public bool Withdraw(double amount, out double remainingBalance)
        {
            if (amount > Balance)
            {
                remainingBalance = Balance;
                return false;
            }
            else
            {
                remainingBalance = Balance - amount;
                return true;
            }
        }
        
    }
    
    static void swap(ref int a, ref int b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
    
    public struct Coords
    {
        public float X { get; set; }
        public float Y { get; set; }

        public Coords(float x, float y)
        {
            X = x;
            Y = y;
        }

        public override string ToString()
        {
            return $"({X}, {Y})";
        }
    }

    static Coords Middle(Coords a, Coords b)
    {
        // middle of coordinates
        return new Coords((a.X + b.X)/2, (a.Y + b.Y)/2);
    }

    static void Main()
    {
        int a = 0;
        int b = 5;
        Console.WriteLine($"a = {a}, b = {b}");
        swap(ref a, ref b);
        Console.WriteLine($"a = {a}, b = {b}");


        Coords x = new Coords(5, 3);
        Coords y = new Coords(3, 5);

        Coords mij = Middle(x, y);
        Console.WriteLine(mij.ToString());

        Account myAccount = new Account("Daniel", 500);

        double balance;
        
        myAccount.Withdraw(600, out balance);
        
        Console.WriteLine($"Balance = {balance}");




    }
}
