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

using System;


interface IGarageItem{
    string ToString();
}

abstract class Car : IGarageItem{
    public string Model { get; protected set; }
    public string Brand { get; protected set; }
    public double EngineCapacity { get; protected set; }
    public int YearOfManufacture { get; protected set; }

    public Car(string model, string brand, double engineCapacity, int year){
        Model = model;
        Brand = brand;
        EngineCapacity = engineCapacity;
        YearOfManufacture = year;
    }

    public abstract void Run();
    public override string ToString(){
        return $"Model: {Model}, Brand: {Brand}, Engine Capacity: {EngineCapacity}, Year: {YearOfManufacture}";
    }
}

class RaceCar : Car{
    public double Acceleration0100Time { get; protected set; }

    public RaceCar(string model, string brand, double engineCapacity, int year, double acceleration) : base(model, brand, engineCapacity, year){
        Acceleration0100Time = acceleration;
    }

    public override void Run(){
        Console.WriteLine("Hello, I am RaceCar");
    }

    public override string ToString(){
        return base.ToString() + ", Acceleration 0-100: " + Acceleration0100Time + "s";
    }
}

class GarbageTruck : Car{
    public double Load { get; protected set; }

    public GarbageTruck(string model, string brand, double engineCapacity, int year, double load) : base(model, brand, engineCapacity, year){
        Load = load;
    }

    public override void Run(){
        Console.WriteLine("Hello, I am GarbageTruck");
    }

    public override string ToString(){
        return base.ToString() + ", Load: " + Load + "kg";
    }
}

class Garage : IGarageItem{
    public List<IGarageItem> Items { get; private set; }

    public Garage(){
        Items = new List<IGarageItem>();
    }

    public void Add(IGarageItem item){
        Items.Add(item);
    }

    public override string ToString(){
        string result = "Garage Contents:\n";
        foreach (var item in Items){
            result += item.ToString() + "\n";
        }
        return result;
    }
}

class Program{
    public static void Main(string[] args){
        RaceCar raceCar = new RaceCar("911 GT3", "Porsche", 4.0, 2022, 3.4);
        GarbageTruck garbageTruck = new GarbageTruck("E-Class", "Mercedes-Benz", 6.7, 2021, 5000);

        Garage garage = new Garage();
        garage.Add(raceCar);
        garage.Add(garbageTruck);

        Garage subGarage = new Garage();
        subGarage.Add(new RaceCar("F40", "Ferrari", 2.9, 1987, 4.1));
        garage.Add(subGarage);

        Console.WriteLine(garage);
    }
}