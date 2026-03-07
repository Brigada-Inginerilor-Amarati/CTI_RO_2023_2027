/*

Se da urmatorul fisier text cars.csv

ID,Make,Model,Year,Price,Mileage,FuelType
1,Toyota,Corolla,2015,12000,75000,Petrol
2,Honda,Civic,2018,18000,50000,Petrol
3,Ford,Focus,2012,8500,95000,Diesel
4,Tesla,Model 3,2020,35000,10000,Electric
5,BMW,3 Series,2016,24000,60000,Diesel
6,Chevrolet,Malibu,2017,15000,70000,Petrol
7,Nissan,Leaf,2019,17000,30000,Electric
8,Audi,A4,2014,20000,80000,Diesel
9,Kia,Soul,2013,9000,85000,Petrol
10,Volkswagen,Golf,2018,19000,40000,Diesel
11,Hyundai,Elantra,2016,14000,65000,Petrol
12,Ford,Fusion,2015,13000,72000,Hybrid
13,Subaru,Impreza,2017,16000,55000,Petrol
14,Mercedes-Benz,C-Class,2019,32000,20000,Diesel
15,Toyota,Prius,2020,27000,15000,Hybrid
16,Chevrolet,Bolt,2021,31000,8000,Electric
17,Volkswagen,Passat,2016,18000,61000,Diesel
18,Honda,Accord,2018,22000,47000,Petrol
19,Nissan,Altima,2014,12500,81000,Petrol
20,Tesla,Model S,2021,85000,5000,Electric

Porniti de la urmatorul fragment de cod pentru a citi contintul fisierului csv.

Completati codul cu clasa Car.

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

class Program
{
    static void Main(string[] args)
    {
        string filePath = "cars.csv";
        var lines = File.ReadAllLines(filePath);
        var cars = lines.Skip(1)
                        .Select(line =>
                        {
                            var columns = line.Split(',');
                            return new Car
                            {
                                ID = int.Parse(columns[0]),
                                Make = columns[1],
                                Model = columns[2],
                                Year = int.Parse(columns[3]),
                                Price = decimal.Parse(columns[4]),
                                Mileage = int.Parse(columns[5]),
                                FuelType = columns[6]
                            };
                        })
                        .ToList();

        var recentCars = cars.Where(car => car.Year > 2018);

        foreach (var car in recentCars)
        {
            Console.WriteLine($"{car.Make} {car.Model} ({car.Year}) - {car.Price:C}");
        }
    }
}

Scrieti cod LINQ procedural si declarativ pentru rezolvarea sarcinilor urmatoare:

1. Selectează toate automobilele fabricate după anul 2018.
2. Afișează toate automobilele care au tipul combustibilului "Electric".
3. Găsește mașina cu cel mai mare preț.
4. Calculează prețul mediu al tuturor mașinilor care au un kilometraj sub 50,000.
5. Grupați mașinile după tipul combustibilului și afișați câte mașini sunt în fiecare grupă.
6. Selectează modelele și anii de fabricație ale mașinilor care costă mai puțin de 20,000 USD.
7. Afișează mașinile fabricate de "Toyota" și "Honda".
8. Sortează toate mașinile în ordine descrescătoare după anul fabricației.
9. Selectează doar ID-urile mașinilor care au un kilometraj mai mare de 80,000.
10. Găsește suma totală a prețurilor tuturor mașinilor fabricate înainte de 2015.

*/

namespace Laborator_10;

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

class Car{
    public int ID { get; set; }
    public string Make { get; set; }
    public string Model { get; set; }
    public int Year { get; set; }
    public decimal Price { get; set; }
    public int Mileage { get; set; }
    public string FuelType { get; set; }

    public Car(){
    }

    public override string ToString(){
        return $"ID: {ID}, Make: {Make}, Model: {Model}, Year: {Year}, Price: {Price:C}, Mileage: {Mileage}, FuelType: {FuelType}";
    }

    public static List<Car> GetCarsAfter2018Declarative(List<Car> cars){
        return cars.Where(car => car.Year > 2018).ToList();
    }

    public static List<Car> GetElectricCarsDeclarative(List<Car> cars){
        return cars.Where(car => car.FuelType == "Electric").ToList();
    }

    public static Car GetHighestPricedCarDeclarative(List<Car> cars){
        return cars.OrderByDescending(car => car.Price).First();
    }

    public static decimal GetAveragePriceUnder50000MileageDeclarative(List<Car> cars){
        return cars.Where(car => car.Mileage < 50000).Average(car => car.Price);
    }

    public static Dictionary<string, int> GroupByFuelTypeDeclarative(List<Car> cars){
        return cars.GroupBy(car => car.FuelType).ToDictionary(group => group.Key, group => group.Count());
    }

    public static List<(string Model, int Year)> GetModelsAndYearsUnder20000Declarative(List<Car> cars){
        return cars.Where(car => car.Price < 20000).Select(car => (car.Model, car.Year)).ToList();
    }

    public static List<Car> GetToyotaAndHondaCarsDeclarative(List<Car> cars){
        return cars.Where(car => car.Make == "Toyota" || car.Make == "Honda").ToList();
    }

    public static List<Car> SortByYearDescendingDeclarative(List<Car> cars){
        return cars.OrderByDescending(car => car.Year).ToList();
    }

    public static List<int> GetIDsWithMileageOver80000Declarative(List<Car> cars){
        return cars.Where(car => car.Mileage > 80000).Select(car => car.ID).ToList();
    }

    public static decimal GetTotalPriceBefore2015Declarative(List<Car> cars){
        return cars.Where(car => car.Year < 2015).Sum(car => car.Price);
    } 
}

static class CarQueriesProcedural {
    public static List<Car> GetCarsAfter2018Procedural(List<Car> cars) {
        List<Car> result = new List<Car>();
        foreach (var car in cars) {
            if (car.Year > 2018) {
                result.Add(car);
            }
        }
        return result;
    }

    public static List<Car> GetElectricCarsProcedural(List<Car> cars) {
        List<Car> result = new List<Car>();
        foreach (var car in cars) {
            if (car.FuelType == "Electric") {
                result.Add(car);
            }
        }
        return result;
    }

    public static Car GetHighestPricedCarProcedural(List<Car> cars) {
        if (cars.Count == 0) return null;
        Car highest = cars[0];
        foreach (var car in cars) {
            if (car.Price > highest.Price) {
                highest = car;
            }
        }
        return highest;
    }

    public static decimal GetAveragePriceUnder50000MileageProcedural(List<Car> cars) {
        decimal totalPrice = 0;
        int count = 0;
        foreach (var car in cars) {
            if (car.Mileage < 50000) {
                totalPrice += car.Price;
                count++;
            }
        }
        return count == 0 ? 0 : totalPrice / count;
    }

    public static Dictionary<string, int> GroupByFuelTypeProcedural(List<Car> cars) {
        Dictionary<string, int> groups = new Dictionary<string, int>();
        foreach (var car in cars) {
            if (groups.ContainsKey(car.FuelType)) {
                groups[car.FuelType]++;
            } else {
                groups[car.FuelType] = 1;
            }
        }
        return groups;
    }

    public static List<(string Model, int Year)> GetModelsAndYearsUnder20000Procedural(List<Car> cars) {
        List<(string Model, int Year)> result = new List<(string Model, int Year)>();
        foreach (var car in cars) {
            if (car.Price < 20000) {
                result.Add((car.Model, car.Year));
            }
        }
        return result;
    }

    public static List<Car> GetToyotaAndHondaCarsProcedural(List<Car> cars) {
        List<Car> result = new List<Car>();
        foreach (var car in cars) {
            if (car.Make == "Toyota" || car.Make == "Honda") {
                result.Add(car);
            }
        }
        return result;
    }

    public static List<Car> SortByYearDescendingProcedural(List<Car> cars) {
        List<Car> result = new List<Car>(cars);
        result.Sort((c1, c2) => c2.Year.CompareTo(c1.Year));
        return result;
    }

    public static List<int> GetIDsWithMileageOver80000Procedural(List<Car> cars) {
        List<int> result = new List<int>();
        foreach (var car in cars) {
            if (car.Mileage > 80000) {
                result.Add(car.ID);
            }
        }
        return result;
    }

    public static decimal GetTotalPriceBefore2015Procedural(List<Car> cars) {
        decimal total = 0;
        foreach (var car in cars) {
            if (car.Year < 2015) {
                total += car.Price;
            }
        }
        return total;
    }
}


class Program
{
    static void Main(string[] args)
    {
        string filePath = "data/cars.csv";
        if (!File.Exists(filePath))
        {
            Console.WriteLine($"File not found: {filePath}");
            return;
        }

        var lines = File.ReadAllLines(filePath);
        var cars = new List<Car>();
        
        bool isFirstRow = true;
        foreach(var line in lines)
        {
            if (isFirstRow) {
                isFirstRow = false;
                continue;
            }
            
            var columns = line.Split(',');
            cars.Add(new Car
            {
                ID = int.Parse(columns[0]),
                Make = columns[1],
                Model = columns[2],
                Year = int.Parse(columns[3]),
                Price = decimal.Parse(columns[4]),
                Mileage = int.Parse(columns[5]),
                FuelType = columns[6]
            });
        }


        Console.WriteLine("=== TESTING OPERATIONS (Declarative vs Procedural) ===\n");

        // Test 1: Cars manufactured after 2018
        Console.WriteLine("1. Cars manufactured after 2018 (Declarative):");
        var carsAfter2018 = Car.GetCarsAfter2018Declarative(cars);
        foreach (var car in carsAfter2018)
        {
            Console.WriteLine($"   {car.Make} {car.Model} ({car.Year})");
        }
        Console.WriteLine($"   Total: {carsAfter2018.Count} cars\n");

        Console.WriteLine("1. Cars manufactured after 2018 (Procedural):");
        var carsAfter2018_P = CarQueriesProcedural.GetCarsAfter2018Procedural(cars);
        foreach (var car in carsAfter2018_P)
        {
            Console.WriteLine($"   {car.Make} {car.Model} ({car.Year})");
        }
        Console.WriteLine($"   Total: {carsAfter2018_P.Count} cars\n");


        // Test 2: Cars with Electric fuel
        Console.WriteLine("2. Cars with Electric fuel (Declarative):");
        var electricCars = Car.GetElectricCarsDeclarative(cars);
        foreach (var car in electricCars)
        {
            Console.WriteLine($"   {car.Make} {car.Model} - {car.Price:C}");
        }
        Console.WriteLine($"   Total: {electricCars.Count} cars\n");

        Console.WriteLine("2. Cars with Electric fuel (Procedural):");
        var electricCars_P = CarQueriesProcedural.GetElectricCarsProcedural(cars);
        foreach (var car in electricCars_P)
        {
            Console.WriteLine($"   {car.Make} {car.Model} - {car.Price:C}");
        }
        Console.WriteLine($"   Total: {electricCars_P.Count} cars\n");


        // Test 3: Car with the highest price
        Console.WriteLine("3. Car with the highest price (Declarative):");
        var highestPricedCar = Car.GetHighestPricedCarDeclarative(cars);
        Console.WriteLine($"   {highestPricedCar.Make} {highestPricedCar.Model} ({highestPricedCar.Year}) - {highestPricedCar.Price:C}\n");

        Console.WriteLine("3. Car with the highest price (Procedural):");
        var highestPricedCar_P = CarQueriesProcedural.GetHighestPricedCarProcedural(cars);
        Console.WriteLine($"   {highestPricedCar_P.Make} {highestPricedCar_P.Model} ({highestPricedCar_P.Year}) - {highestPricedCar_P.Price:C}\n");


        // Test 4: Average price of cars with mileage under 50,000
        Console.WriteLine("4. Average price of cars with mileage under 50,000 (Declarative):");
        var avgPrice = Car.GetAveragePriceUnder50000MileageDeclarative(cars);
        Console.WriteLine($"   {avgPrice:C}\n");

        Console.WriteLine("4. Average price of cars with mileage under 50,000 (Procedural):");
        var avgPrice_P = CarQueriesProcedural.GetAveragePriceUnder50000MileageProcedural(cars);
        Console.WriteLine($"   {avgPrice_P:C}\n");


        // Test 5: Grouping cars by fuel type
        Console.WriteLine("5. Grouping cars by fuel type (Declarative):");
        var fuelGroups = Car.GroupByFuelTypeDeclarative(cars);
        foreach (var group in fuelGroups)
        {
            Console.WriteLine($"   {group.Key}: {group.Value} cars");
        }
        Console.WriteLine();

        Console.WriteLine("5. Grouping cars by fuel type (Procedural):");
        var fuelGroups_P = CarQueriesProcedural.GroupByFuelTypeProcedural(cars);
        foreach (var group in fuelGroups_P)
        {
            Console.WriteLine($"   {group.Key}: {group.Value} cars");
        }
        Console.WriteLine();


        // Test 6: Models and years for cars under 20,000 USD
        Console.WriteLine("6. Models and years for cars under 20,000 USD (Declarative):");
        var modelsUnder20000 = Car.GetModelsAndYearsUnder20000Declarative(cars);
        foreach (var (model, year) in modelsUnder20000)
        {
            Console.WriteLine($"   {model} ({year})");
        }
        Console.WriteLine($"   Total: {modelsUnder20000.Count} cars\n");

        Console.WriteLine("6. Models and years for cars under 20,000 USD (Procedural):");
        var modelsUnder20000_P = CarQueriesProcedural.GetModelsAndYearsUnder20000Procedural(cars);
        foreach (var (model, year) in modelsUnder20000_P)
        {
            Console.WriteLine($"   {model} ({year})");
        }
        Console.WriteLine($"   Total: {modelsUnder20000_P.Count} cars\n");


        // Test 7: Cars manufactured by Toyota and Honda
        Console.WriteLine("7. Cars manufactured by Toyota and Honda (Declarative):");
        var toyotaHondaCars = Car.GetToyotaAndHondaCarsDeclarative(cars);
        foreach (var car in toyotaHondaCars)
        {
            Console.WriteLine($"   {car.Make} {car.Model} ({car.Year}) - {car.Price:C}");
        }
        Console.WriteLine($"   Total: {toyotaHondaCars.Count} cars\n");

        Console.WriteLine("7. Cars manufactured by Toyota and Honda (Procedural):");
        var toyotaHondaCars_P = CarQueriesProcedural.GetToyotaAndHondaCarsProcedural(cars);
        foreach (var car in toyotaHondaCars_P)
        {
            Console.WriteLine($"   {car.Make} {car.Model} ({car.Year}) - {car.Price:C}");
        }
        Console.WriteLine($"   Total: {toyotaHondaCars_P.Count} cars\n");


        // Test 8: Cars sorted descending by manufacturing year
        Console.WriteLine("8. Cars sorted descending by manufacturing year (Declarative):");
        var sortedByYear = Car.SortByYearDescendingDeclarative(cars);
        foreach (var car in sortedByYear)
        {
            Console.WriteLine($"   {car.Make} {car.Model} ({car.Year})");
        }
        Console.WriteLine();

        Console.WriteLine("8. Cars sorted descending by manufacturing year (Procedural):");
        var sortedByYear_P = CarQueriesProcedural.SortByYearDescendingProcedural(cars);
        foreach (var car in sortedByYear_P)
        {
            Console.WriteLine($"   {car.Make} {car.Model} ({car.Year})");
        }
        Console.WriteLine();


        // Test 9: IDs of cars with mileage > 80,000
        Console.WriteLine("9. IDs of cars with mileage > 80,000 (Declarative):");
        var idsOver80000 = Car.GetIDsWithMileageOver80000Declarative(cars);
        Console.WriteLine($"   {string.Join(", ", idsOver80000)}");
        Console.WriteLine($"   Total: {idsOver80000.Count} cars\n");

        Console.WriteLine("9. IDs of cars with mileage > 80,000 (Procedural):");
        var idsOver80000_P = CarQueriesProcedural.GetIDsWithMileageOver80000Procedural(cars);
        Console.WriteLine($"   {string.Join(", ", idsOver80000_P)}");
        Console.WriteLine($"   Total: {idsOver80000_P.Count} cars\n");


        // Test 10: Total sum of prices for cars manufactured before 2015
        Console.WriteLine("10. Total sum of prices for cars manufactured before 2015 (Declarative):");
        var totalPriceBefore2015 = Car.GetTotalPriceBefore2015Declarative(cars);
        Console.WriteLine($"    {totalPriceBefore2015:C}\n");

        Console.WriteLine("10. Total sum of prices for cars manufactured before 2015 (Procedural):");
        var totalPriceBefore2015_P = CarQueriesProcedural.GetTotalPriceBefore2015Procedural(cars);
        Console.WriteLine($"    {totalPriceBefore2015_P:C}\n");
    }
}