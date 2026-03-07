using System;

public abstract class Motorcycle
{
    public string Model { get; set; }
    public string Brand { get; set; }
    public int Nominal_speed { get; set; }

    public Motorcycle(string model, string brand, int nominal_speed)
    {
        Model = model;
        Brand = brand;
        Nominal_speed = nominal_speed;
    }

    public abstract void Run();

    public override string ToString()
    {
        return $"Model: {Model}, Brand: {Brand}, Nominal Speed: {Nominal_speed}.";
    }
}

public class CrossMotorcycle : Motorcycle
{
    public int Nr_shock_absorbers { get; set; }

    public CrossMotorcycle(string model, string brand, int nominal_speed, int nr_shock_absorbers) : base(model, brand, nominal_speed)
    {
        Nr_shock_absorbers = nr_shock_absorbers;
    }

    public override void Run()
    {
        Console.WriteLine("Hello, I am Crossmotorcycle!");
    }

    public override string ToString()
    {
        return $"Model: {Model}, Brand: {Brand}, Nominal Speed: {Nominal_speed} kmh, Nr_shock_absorbers: {Nr_shock_absorbers}.";
    }
}

public class SpeedMotorcycle : Motorcycle
{
    public int Top_speed { get; set; }

    public SpeedMotorcycle(string model, string brand, int nominal_speed, int top_speed) : base(model, brand, nominal_speed)
    {
        Top_speed = top_speed;
    }

    public override void Run()
    {
        Console.WriteLine("Hello, I am SpeedMotorcycle!");
    }

    public override string ToString()
    {
        return $"Model: {Model}, Brand: {Brand}, Nominal speed: {Nominal_speed}, Top speed: {Top_speed}";
    }
}

public class Garage
{
    private List<Motorcycle> motorcycles;

    public Garage()
    {
        motorcycles = new List<Motorcycle>();
    }

    public void AddMotorcycle(Motorcycle motorcycle)
    {
        motorcycles.Add(motorcycle);
        Console.WriteLine($"Motocicleta {motorcycle.Model} de la {motorcycle.Brand} a fost adaugata in garaj.");
    }

    public void ShowMotorcycles()
    {
        Console.WriteLine("Motociclete in garaj:");
        foreach (var moto in motorcycles)
        {
            Console.WriteLine(moto.ToString());
        }
    }
}

public class Program
{
    public static void Main(string[] args)
    {
        
    }
}