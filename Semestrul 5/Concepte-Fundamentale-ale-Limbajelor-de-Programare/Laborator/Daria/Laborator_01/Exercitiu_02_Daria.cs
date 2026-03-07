// 2. Scrieti un program care primeste coeficientii a, b si c si rezolva ecuatia ax² + bx + c = 0.
using System;

class Exercitiu_02_Daria{
    static void Main(String[] args){
        Console.WriteLine("Introduceti coeficientii a, b si c pentru ecuatia ax^2 + bx + c = 0: ");

        int a = 0;
        int b = 0;
        int c = 0;

       try{
            a = int.Parse(Console.ReadLine());  
        }
        catch(Exception e){
            Console.WriteLine("Eroare: " + e.Message);
        }

        try{
            b = int.Parse(Console.ReadLine());
        }
        catch(Exception e){
            Console.WriteLine("Eroare: " + e.Message);
        }

        try{
            c = int.Parse(Console.ReadLine());
        }
        catch(Exception e){
            Console.WriteLine("Eroare: " + e.Message);
        }

        int delta = (b * b) - (4 * a * c);

        if(delta < 0){
            Console.WriteLine("Ecuatia nu are solutii reale");
        }
        else if(delta == 0){
            double x = -b / (2 * a);
            Console.WriteLine("Ecuatia are o singura solutie reala: x = " + x);
        }
        else{
            double x1 = (-b + Math.Sqrt(delta)) / (2 * a);
            double x2 = (-b - Math.Sqrt(delta)) / (2 * a);
            Console.WriteLine("Ecuatia are doua solutii reale: x1 = " + x1 + " si x2 = " + x2);
        }
    }
}