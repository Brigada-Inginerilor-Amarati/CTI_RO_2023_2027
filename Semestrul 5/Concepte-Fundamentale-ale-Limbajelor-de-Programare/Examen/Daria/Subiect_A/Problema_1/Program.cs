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

using System;
using System.Collections.Generic;
using System.Text;

// Interfata comuna pentru a permite stocarea in lista Garajului
public interface IGarageItem 
{
    string ToString();
}

public abstract class Motorcycle : IGarageItem
{
    public string Brand { get; protected set; }
    public string Model { get; protected set; }
    public double NominalSpeed { get; protected set; }

    public Motorcycle(string brand, string model, double nominalSpeed)
    {
        Brand = brand;
        Model = model;
        NominalSpeed = nominalSpeed;
    }

    public abstract void Run();

    public override string ToString()
    {
        return $"Brand: {Brand}, Model: {Model}, Nominal Speed: {NominalSpeed}";
    }
}

public class CrossMotorcycle : Motorcycle
{
    public int NrShockAbsorbers { get; protected set; }

    public CrossMotorcycle(string brand, string model, double nominalSpeed, int nrShockAbsorbers) 
        : base(brand, model, nominalSpeed)
    {
        NrShockAbsorbers = nrShockAbsorbers;
    }

    public override void Run()
    {
        Console.WriteLine("Hello, I am CrossMotorcycle");
    }

    public override string ToString()
    {
        return $"{base.ToString()}, Shock Absorbers: {NrShockAbsorbers}";
    }
}

public class SpeedMotorcycle : Motorcycle
{
    public double TopSpeed { get; protected set; }

    public SpeedMotorcycle(string brand, string model, double nominalSpeed, double topSpeed) 
        : base(brand, model, nominalSpeed)
    {
        TopSpeed = topSpeed;
    }

    public override void Run()
    {
        Console.WriteLine("Hello, I am SpeedMotorcycle");
    }

    public override string ToString()
    {
        return $"{base.ToString()}, Top Speed: {TopSpeed}";
    }
}

public class Garage : IGarageItem
{
    // Lista poate contine orice implementeaza IGarageItem (Motorcycle sau Garage)
    public List<IGarageItem> Items { get; private set; }

    public Garage()
    {
        Items = new List<IGarageItem>();
    }

    public void Add(IGarageItem item)
    {
        Items.Add(item);
    }
    
    public override string ToString()
    {
        StringBuilder sb = new StringBuilder();
        sb.AppendLine("Garage contains:");
        foreach(var item in Items)
        {
            // Indentam continutul pentru claritate daca este un garaj imbricat
            string content = item.ToString().Replace("\n", "\n  ");
            sb.AppendLine($" - {content}");
        }
        return sb.ToString();
    }
}

public class Program
{
    public static void Main(string[] args)
    {
        Garage garage = new Garage();
        garage.Add(new CrossMotorcycle("Yamaha", "YZF-R1", 250, 4));
        garage.Add(new SpeedMotorcycle("KTM", "RC 250", 250, 250));
        Console.WriteLine(garage.ToString());

        Garage garage2 = new Garage();
        garage2.Add(garage);
        Console.WriteLine(garage2.ToString());
    }
}
