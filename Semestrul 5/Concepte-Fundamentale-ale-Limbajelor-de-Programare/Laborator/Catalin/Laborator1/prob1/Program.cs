using System; 

public class randasa12
{  
    public static void Main()  
    {       
        int i, n, sum = 0;
        int x;
    

    
      
        Console.Write("Read n numbers and calculate sum:\n"); 
        Console.Write("\n\n"); 
        Console.Write("Input n numbers : \n");
        n = Convert.ToInt32(Console.ReadLine()); 
	
       
        for (i = 1; i <= n; i++) 
        {
            Console.Write("Number-{0} :", i);  

            x = Convert.ToInt32(Console.ReadLine()); 
            sum += x;
        }

        

        Console.Write(sum); 
    }
}

