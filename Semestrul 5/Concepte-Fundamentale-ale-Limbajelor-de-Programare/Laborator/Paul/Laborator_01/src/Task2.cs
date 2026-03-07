// 2. Scrieti un program care primeste coeficientii a, b si c si rezolva ecuatia ax² + bx + c = 0

class Task2{
    public static void Main(string[] args){

        if (args.Length != 3){
            Console.WriteLine("Numar invalid de argumente!");
        }

        double a = double.Parse(args[0]);
        double b = double.Parse(args[1]);
        double c = double.Parse(args[2]);

        Console.WriteLine("Ecuatia este: " + a + "x² + " + b + "x + " + c + " = 0");

        double delta = b * b - 4 * a * c;
        if(delta < 0){
            Console.WriteLine("Ecuatia nu are solutii reale");
            return;
        }

        double x1 = (b - Math.Sqrt(delta)) / (2 * a);
        double x2 = (b + Math.Sqrt(delta)) / (2 * a);

        Console.WriteLine("x1 = " + x1);
        Console.WriteLine("x2 = " + x2);
    }
}
