// See https://aka.ms/new-console-template for more information
/*
Problema A
1. Creează următoarea ierarhie de clase:

O clasă abstractă Motorcycle, care conține:
i) Proprietăți: brand, model, nominal_speed (public get, protected set).
ii) Un constructor pentru inițializarea proprietăților.
iii) O metodă abstractă void Run().
iv) O metodă ToString() care returnează un șir concatenat cu valorile membrilor.

O clasă CrossMotorcycle, care moștenește Motorcycle și conține:
i) Proprietate: nr_shock_absorbers (public get, protected set).
ii) Un constructor pentru inițializarea membrilor.
iii) O metodă Run() care afișează "Hello, I am CrossMotorcycle".
iv) O metodă ToString() care returnează un șir concatenat cu valorile membrilor.

O clasă SpeedMotorcycle, care moștenește Motorcycle și conține:
i) Proprietate: top_speed (public get, protected set).
ii) Un constructor pentru inițializarea membrilor.
iii) O metodă Run() care afișează "Hello, I am SpeedMotorcycle".
iv) O metodă ToString() care returnează un șir concatenat cu valorile membrilor.

O clasă Garage, care conține o singură lista în care se vor putea adăuga atat motociclete cat și garaje (instante din clasa Garage însăși)!
*/

abstract class Motorcycle(string Brand, string Model, int NominalSpeed) : IStorable
{
    public string Brand { get; protected set; } = Brand;
    public string Model { get; protected set; } = Model;
    public int NominalSpeed { get; protected set; } = NominalSpeed;

    public abstract void Run();

    public override string ToString()
    {
        return $"Brand: {Brand}, Model: {Model}, Nominal Speed: {NominalSpeed}";
    }
}

class CrossMotorcycle(string Brand, string Model, int NominalSpeed, int NumShockAbsorbers)
    : Motorcycle(Brand, Model, NominalSpeed)
{
    public int NumShockAbsorbers { get; protected set; } = NumShockAbsorbers;

    public override void Run()
    {
        Console.WriteLine("Hello, I am CrossMotorcycle");
    }

    public override string ToString()
    {
        return $"Brand: {Brand}, Model: {Model}, Nominal Speed: {NominalSpeed}, Num Shock Absorbers: {NumShockAbsorbers}";
    }
}

class SpeedMotorcycle(string Brand, string Model, int NominalSpeed, int TopSpeed)
    : Motorcycle(Brand, Model, NominalSpeed)
{
    public int TopSpeed { get; protected set; } = TopSpeed;

    public override void Run()
    {
        Console.WriteLine("Hello, I am SpeedMotorcycle");
    }

    public override string ToString()
    {
        return $"Brand: {Brand}, Model: {Model}, Nominal Speed: {NominalSpeed}, Top Speed: {TopSpeed}";
    }
}

interface IStorable { }

class Garage : IStorable
{
    private readonly List<IStorable> storables = new List<IStorable>();

    public void Add(IStorable storable)
    {
        storables.Add(storable);
    }

    public override string ToString()
    {
        var buffer = "";
        foreach (var item in storables)
        {
            buffer += item.ToString() + "\n";
        }
        return $"Garage with {storables.Count} items:\n{buffer}";
    }
}

class MainClass
{
    static void Main(string[] args)
    {
        var garage1 = new Garage();
        garage1.Add(new CrossMotorcycle("Yamaha", "YZF-R6", 180, 4));
        garage1.Add(new SpeedMotorcycle("Kawasaki", "Ninja ZX-10R", 200, 250));

        var garage2 = new Garage();
        garage2.Add(new CrossMotorcycle("Honda", "CBR650R", 180, 4));
        garage2.Add(new SpeedMotorcycle("Ducati", "Panigale V4", 200, 250));
        garage2.Add(garage1);

        Console.WriteLine(garage2);
    }
}
