/*
O clasă abstractă Car, care conține:

i) Proprietăți: model, brand, engine_capacity, year_of_manufacture (public get, protected set).

ii) Un constructor pentru inițializarea proprietăților.

iii) O metodă abstractă void Run(). iv) O metodă ToString() care returnează un șir concatenat cu valorile membrilor.

O clasă RaceCar, care moștenește Car și conține:

i) Proprietate: acceleration_0_100_time (public get, protected set).

ii) Un constructor pentru inițializarea membrilor.

iii) O metodă Run() care afișează "Hello, I am RaceCar".

iv) O metodă ToString() care returnează un șir concatenat cu valorile membrilor.

O clasă GarbageTruck, care moștenește Car și conține:

i) Proprietate: load (public get, protected set).

ii) Un constructor pentru inițializarea membrilor.

iii) O metodă Run() care afișează "Hello, I am GarbageTruck".

iv) O metodă ToString() care returnează un șir concatenat cu valorile membrilor.

O clasă Garage, care conține o singură lista în care se vor putea adăuga atat mașini cat și garaje (instante din clasa Garage însăși)!
*/

interface Storable { }

abstract class Car(string model, string brand, double engineCapacity, int yearOfManufacture)
    : Storable
{
    public string Model { get; protected set; } = model;
    public string Brand { get; protected set; } = brand;
    public double EngineCapacity { get; protected set; } = engineCapacity;
    public int YearOfManufacture { get; protected set; } = yearOfManufacture;

    public abstract void Run();

    public override string ToString()
    {
        return $"Model: {Model}, Brand: {Brand}, Engine Capacity: {EngineCapacity}, Year of Manufacture: {YearOfManufacture}";
    }
}

class RaceCar(
    string model,
    string brand,
    double engineCapacity,
    int yearOfManufacture,
    double zeroToHundredTime
) : Car(model, brand, engineCapacity, yearOfManufacture)
{
    public double ZeroToHundredTime { get; protected set; } = zeroToHundredTime;

    public override void Run()
    {
        Console.WriteLine("RaceCar");
    }

    public override string ToString()
    {
        return $"Model: {Model}, Brand: {Brand}, Engine Capacity: {EngineCapacity}, Year of Manufacture: {YearOfManufacture}, Zero to Hundred Time: {ZeroToHundredTime}";
    }
}

class GarbageTruck(
    string model,
    string brand,
    double engineCapacity,
    int yearOfManufacture,
    double load
) : Car(model, brand, engineCapacity, yearOfManufacture)
{
    public double Load { get; protected set; } = load;

    public override void Run()
    {
        Console.WriteLine("GarbageTruck");
    }

    public override string ToString()
    {
        return $"Model: {Model}, Brand: {Brand}, Engine Capacity: {EngineCapacity}, Year of Manufacture: {YearOfManufacture}, Load: {Load}";
    }
}

class Garage : Storable
{
    private readonly List<Storable> storables = new List<Storable>();

    public void Add(Storable storable)
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
    public static void Main()
    {
        var car1 = new RaceCar("Model1", "Brand1", 1.5, 2020, 10.5);
        var car2 = new RaceCar("Model2", "Brand2", 2.0, 2021, 12.5);
        var car3 = new GarbageTruck("Model3", "Brand3", 3.0, 2022, 100);
        var garage1 = new Garage();
        garage1.Add(car1);
        garage1.Add(car2);

        var garage2 = new Garage();
        garage2.Add(car3);
        garage2.Add(garage1);

        Console.WriteLine(garage2);
    }
}
