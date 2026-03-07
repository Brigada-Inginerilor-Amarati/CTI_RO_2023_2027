/*

Se da urmatorul fisier text cars.csv

Porniti de la urmatorul fragment de cod pentru a citi contintul fisierului csv.

Completati codul cu clasa Car.

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

class Program
{
    static List<Car> getCarsFromCSV(string filePath)
    {
        var lines = File.ReadAllLines(filePath);
        return lines
            .Skip(1)
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
                    FuelType = columns[6],
                };
            })
            .ToList();
    }

    static void Main(string[] args)
    {
        string filePath = "data/cars.csv";
        var cars = getCarsFromCSV(filePath);

        Test1_GetCarsAfter2018(cars);
        Test2_GetElectricCars(cars);
        Test3_GetHighestPricedCar(cars);
        Test4_GetAveragePriceUnder50000Mileage(cars);
        Test5_GroupByFuelType(cars);
        Test6_GetModelsAndYearsUnder20000(cars);
        Test7_GetToyotaAndHondaCars(cars);
        Test8_SortByYearDescending(cars);
        Test9_GetIDsWithMileageOver80000(cars);
        Test10_GetTotalPriceBefore2015(cars);
    }

    static void Test1_GetCarsAfter2018(List<Car> cars)
    {
        Console.WriteLine("=== Test 1: Cars After 2018 ===");

        var result1 = Car.GetCarsAfter2018_Procedural(cars);
        var result2 = Car.GetCarsAfter2018_Declarative(cars);

        Console.WriteLine("Procedural:");
        result1.ForEach(car => Console.WriteLine(car));
        Console.WriteLine("\nDeclarative:");
        result2.ForEach(car => Console.WriteLine(car));
        Console.WriteLine();
    }

    static void Test2_GetElectricCars(List<Car> cars)
    {
        Console.WriteLine("=== Test 2: Electric Cars ===");
        var result1 = Car.GetElectricCars_Procedural(cars);
        var result2 = Car.GetElectricCars_Declarative(cars);

        Console.WriteLine("Procedural:");
        result1.ForEach(car => Console.WriteLine(car));
        Console.WriteLine("\nDeclarative:");
        result2.ForEach(car => Console.WriteLine(car));
        Console.WriteLine();
    }

    static void Test3_GetHighestPricedCar(List<Car> cars)
    {
        Console.WriteLine("=== Test 3: Highest Priced Car ===");
        var result1 = Car.GetHighestPricedCar_Procedural(cars);
        var result2 = Car.GetHighestPricedCar_Declarative(cars);

        Console.WriteLine("Procedural:");
        Console.WriteLine(result1);
        Console.WriteLine("\nDeclarative:");
        Console.WriteLine(result2);
        Console.WriteLine();
    }

    static void Test4_GetAveragePriceUnder50000Mileage(List<Car> cars)
    {
        Console.WriteLine("=== Test 4: Average Price (Mileage < 50,000) ===");
        var result1 = Car.GetAveragePriceUnder50000Mileage_Procedural(cars);
        var result2 = Car.GetAveragePriceUnder50000Mileage_Declarative(cars);

        Console.WriteLine("Procedural:");
        Console.WriteLine($"Average Price: {result1:C}");
        Console.WriteLine("\nDeclarative:");
        Console.WriteLine($"Average Price: {result2:C}");
        Console.WriteLine();
    }

    static void Test5_GroupByFuelType(List<Car> cars)
    {
        Console.WriteLine("=== Test 5: Group By Fuel Type ===");
        var result1 = Car.GroupByFuelType_Procedural(cars);
        var result2 = Car.GroupByFuelType_Declarative(cars);

        Console.WriteLine("Procedural:");
        foreach (var group in result1)
        {
            Console.WriteLine($"{group.Key}: {group.Value} cars");
        }
        Console.WriteLine("\nDeclarative:");
        foreach (var group in result2)
        {
            Console.WriteLine($"{group.Key}: {group.Value} cars");
        }
        Console.WriteLine();
    }

    static void Test6_GetModelsAndYearsUnder20000(List<Car> cars)
    {
        Console.WriteLine("=== Test 6: Models and Years Under $20,000 ===");
        var result1 = Car.GetModelsAndYearsUnder20000_Procedural(cars);
        var result2 = Car.GetModelsAndYearsUnder20000_Declarative(cars);

        Console.WriteLine("Procedural:");
        foreach (var item in result1)
        {
            Console.WriteLine($"{item.Model} ({item.Year})");
        }
        Console.WriteLine("\nDeclarative:");
        foreach (var item in result2)
        {
            Console.WriteLine($"{item.Model} ({item.Year})");
        }
        Console.WriteLine();
    }

    static void Test7_GetToyotaAndHondaCars(List<Car> cars)
    {
        Console.WriteLine("=== Test 7: Toyota and Honda Cars ===");
        var result1 = Car.GetToyotaAndHondaCars_Procedural(cars);
        var result2 = Car.GetToyotaAndHondaCars_Declarative(cars);

        Console.WriteLine("Procedural:");
        result1.ForEach(car => Console.WriteLine(car));
        Console.WriteLine("\nDeclarative:");
        result2.ForEach(car => Console.WriteLine(car));
        Console.WriteLine();
    }

    static void Test8_SortByYearDescending(List<Car> cars)
    {
        Console.WriteLine("=== Test 8: Sort By Year (Descending) ===");
        var result1 = Car.SortByYearDescending_Procedural(cars);
        var result2 = Car.SortByYearDescending_Declarative(cars);

        Console.WriteLine("Procedural:");
        result1.ForEach(car => Console.WriteLine(car));
        Console.WriteLine("\nDeclarative:");
        result2.ForEach(car => Console.WriteLine(car));
        Console.WriteLine();
    }

    static void Test9_GetIDsWithMileageOver80000(List<Car> cars)
    {
        Console.WriteLine("=== Test 9: IDs with Mileage > 80,000 ===");
        var result1 = Car.GetIDsWithMileageOver80000_Procedural(cars);
        var result2 = Car.GetIDsWithMileageOver80000_Declarative(cars);

        Console.WriteLine("Procedural:");
        result1.ForEach(id => Console.WriteLine($"ID: {id}"));
        Console.WriteLine("\nDeclarative:");
        result2.ForEach(id => Console.WriteLine($"ID: {id}"));
        Console.WriteLine();
    }

    static void Test10_GetTotalPriceBefore2015(List<Car> cars)
    {
        Console.WriteLine("=== Test 10: Total Price (Before 2015) ===");
        var result1 = Car.GetTotalPriceBefore2015_Procedural(cars);
        var result2 = Car.GetTotalPriceBefore2015_Declarative(cars);

        Console.WriteLine("Procedural:");
        Console.WriteLine($"Total Price: {result1:C}");
        Console.WriteLine("\nDeclarative:");
        Console.WriteLine($"Total Price: {result2:C}");
        Console.WriteLine();
    }
}
