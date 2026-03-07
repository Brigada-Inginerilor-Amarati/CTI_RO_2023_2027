namespace CFLPLab1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello, World!");

            // string s = Console.ReadLine();

            // Console.WriteLine(s);

            int n = 0;
            
            /*
            try
            {
                n = int.Parse(s);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            */
            /*
            if (int.TryParse(s, out n))
            {
                Console.WriteLine(n);
            }
            else
            {
                Console.WriteLine("ghinion");
            }
            */

            Animal a = new Animal("caine");
            Console.WriteLine(a);
        }
    }
}
