namespace Test_1_R2;

class Program
{
    /*
    1. Implementati o metoda CalculateScore care primeste 2 valori basePoints si multiplier si
    returneaza true daca basePoints * multiplier este mai mare decat 0. In plus, metoda returneaza
    basePoints * multiplier prin intermediul unui alt parametru. (2p)
    */
    static bool CalculateScore(in double basePoints, in double multiplier, out double result)
    {
        result = basePoints * multiplier;
        return result > 0;
    }

    static void Test1()
    {
        var basePoints = 10.0;
        var multiplier = 10.0;
        var result = 0.0;
        if (CalculateScore(in basePoints, in multiplier, out result))
            Console.WriteLine($"Multiplied points: {basePoints} * {multiplier} = {result}");
        else
            Console.WriteLine("Points are negative!");
    }

    /*
    2. Implementati o metoda Any care primeste ca parametru o lista de double si o conditie (o
    funcție care primește un double și returnează un bool) si returneaza true daca exista cel putin un
    element in lista care respecta conditia. In caz contrar, metoda returneaza false. (2p)
    */
    static bool Any(List<double> list, Predicate<double> pred)
    {
        foreach (var item in list)
            if (pred(item))
                return true;

        return false;
    }

    static void Test2()
    {
        var random = new Random();
        var results = new List<double>();
        for (int i = 0; i < 10; i++)
            results.Add(random.NextDouble() * 2 - 1);

        Predicate<double> pred = (x) => x < 0;

        Console.WriteLine("Lista: " + string.Join(" ", results));
        Console.WriteLine(
            "Cel putin unul din elementele listei este negative: " + Any(results, pred)
        );
    }

    /*
    3. Creati urmatoare ierarhie de clase:
    Adaugati cel putin un obiect din fiecare clasa ( HardDisk si CloudStorage) intr-o lista de tip
    Storage, apoi apelati metodele implementate pentru fiecare obiect astfel incat sa se poata observa
    modul de functionare al acestora. Pentru afisarea starii obiectelor se va folosi metoda ToString. (1p)
    */
    static void Test3()
    {
        var storage = new List<Storage>();
        storage.Add(new HardDisk("HardDisk", 1000, 0));
        storage.Add(new CloudStorage("CloudStorage", 1000, 0, 100));

        foreach (var item in storage)
        {
            Console.WriteLine("--------------------------------");
            Console.WriteLine(item.ToString());
            item.Load(100);
            Console.WriteLine("--------------------------------");
            Console.WriteLine("Loaded");
            Console.WriteLine(item.ToString());
            item.Unload(100);
            Console.WriteLine("--------------------------------");
            Console.WriteLine("Unloaded");
            Console.WriteLine(item.ToString());
        }
    }

    static void Main(string[] args)
    {
        Test1();
        Test2();
        Test3();
    }
}
