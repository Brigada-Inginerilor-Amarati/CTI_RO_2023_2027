using System; 

public class Exercise4  
{  
    public static void Main()  
    {       
        int a, b, c, delta = 0;
        double x1, x2;
        
        
        Console.Write("\n\n");
        Console.Write("a:\n");
        a = Convert.ToInt32(Console.ReadLine());
        Console.Write("\n\n");
        
        Console.Write("\n\n");
        Console.Write("b:\n");
        b = Convert.ToInt32(Console.ReadLine());
        Console.Write("\n\n");
        
        Console.Write("\n\n");
        Console.Write("c:\n");
        c = Convert.ToInt32(Console.ReadLine());
        Console.Write("\n\n");
        
        delta = (a*a) - (4 * a * c);
        
        x1 = ((-b) - Math.Sqrt(delta)) / (2 * a);
         x2 = ((-b) + Math.Sqrt(delta)) / (2 * a);
        
        Console.Write(delta);
          Console.Write("\n\n");
        Console.Write(x1);
         Console.Write("\n\n");
        Console.Write(x2);

    
        
        

    
    }
}
