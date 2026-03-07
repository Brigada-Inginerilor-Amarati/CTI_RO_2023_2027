namespace Test_1_R1;

class Program
{
    const double KELVIN_CONVERSION = 273.15;

    /*
    1. Implementati o metoda ConvertTemperature care primeste ca parametru temperatura in Kelvin si
    returneaza true daca temperatura este mai mare decat 0K. In plus, metoda returneaza temperatura in
    grade Celsius prin intermediul unui alt parametru. (2p)
    C = K – 273.15
    
    */
    static bool ConvertTemperature(in double Kelvin, out double Celsius)
    {
        if (Kelvin < 0)
        {
            Celsius = 0;
            return false;
        }

        Celsius = Kelvin - KELVIN_CONVERSION;
        return true;
    }

    static void Test1()
    {
        var kelvin = 300.0;
        var celsius = 0.0;
        if (ConvertTemperature(in kelvin, out celsius))
            Console.WriteLine($"Temperatura este: {kelvin}K = {celsius}°C");
        else
            Console.WriteLine("Temperatura este sub 0K");
    }

    /*
    2. Implementati o metoda All care primeste ca parametru o lista de float si o conditie (o
    funcție care primește un float și returnează un bool) si returneaza true daca toate elementele listei respecta conditia. In caz contrar, metoda returneaza false. (2p)
    */
    static bool All(List<double> list, Predicate<double> pred)
    {
        foreach (var item in list)
            if (!pred(item))
                return false;

        return true;
    }

    static void Test2()
    {
        var random = new Random();
        var results = new List<double>();
        for (int i = 0; i < 10; i++)
            results.Add(random.NextDouble() * 2 - 1);

        Predicate<double> pred = (x) => x > 0;

        Console.WriteLine("Lista: " + string.Join(" ", results));
        Console.WriteLine("Toate elementele listei sunt pozitive: " + All(results, pred));
    }

    /*
    Adaugati cel putin un obiect din fiecare clasa (WashingMachine si Refrigerator) intr-o lista de tip
    Appliance, apoi apelati metodele implementate pentru fiecare obiect astfel incat sa se poata observa
    modul de functionare al acestora. Pentru afisarea starii obiectelor se va folosi metoda ToString. (1p)
    */
    static void Test3()
    {
        var appliances = new List<Appliance>();
        appliances.Add(new WashingMachine("WashingMachine", 1000, 0));
        appliances.Add(new Refrigerator("Refrigerator", 1000, 0, 100));

        foreach (var appliance in appliances)
        {
            Console.WriteLine("--------------------------------");
            Console.WriteLine(appliance.ToString());
            appliance.Activate();
            Console.WriteLine("--------------------------------");
            Console.WriteLine("Activated");
            Console.WriteLine(appliance.ToString());
            appliance.Deactivate();
            Console.WriteLine("--------------------------------");
            Console.WriteLine("Deactivated");
            Console.WriteLine(appliance.ToString());
        }
    }

    static void Main(string[] args)
    {
        Test1();
        Test2();
        Test3();
    }
}
