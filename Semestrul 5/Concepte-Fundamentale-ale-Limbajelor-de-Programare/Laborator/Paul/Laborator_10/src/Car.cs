/*
 ID = int.Parse(columns[0]),
                    Make = columns[1],
                    Model = columns[2],
                    Year = int.Parse(columns[3]),
                    Price = decimal.Parse(columns[4]),
                    Mileage = int.Parse(columns[5]),
                    FuelType = columns[6],

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

class Car
{
    public int ID { get; init; }
    public string Make { get; init; }
    public string Model { get; init; }
    public int Year { get; init; }
    public decimal Price { get; init; }
    public int Mileage { get; init; }
    public string FuelType { get; init; }

    public override string ToString()
    {
        return $"ID: {ID}, Make: {Make}, Model: {Model}, Year: {Year}, Price: {Price:C}, Mileage: {Mileage}, FuelType: {FuelType}";
    }

    public static List<Car> GetCarsAfter2018_Procedural(List<Car> cars)
    {
        return cars.Where(c => c.Year > 2018).ToList();
    }

    public static List<Car> GetCarsAfter2018_Declarative(List<Car> cars)
    {
        var result = from car in cars where car.Year > 2018 select car;
        return result.ToList();
    }

    public static List<Car> GetElectricCars_Procedural(List<Car> cars)
    {
        return cars.Where(c => c.FuelType == "Electric").ToList();
    }

    public static List<Car> GetElectricCars_Declarative(List<Car> cars)
    {
        var result = from car in cars where car.FuelType == "Electric" select car;
        return result.ToList();
    }

    public static Car GetHighestPricedCar_Procedural(List<Car> cars)
    {
        return cars.OrderByDescending(car => car.Price).First();
    }

    public static Car GetHighestPricedCar_Declarative(List<Car> cars)
    {
        var result = from car in cars where car.Price == cars.Max(c => c.Price) select car;
        return result.ToList().First();
    }

    public static decimal GetAveragePriceUnder50000Mileage_Procedural(List<Car> cars)
    {
        return cars.Where(car => car.Mileage < 50000).Average(car => car.Price);
    }

    public static decimal GetAveragePriceUnder50000Mileage_Declarative(List<Car> cars)
    {
        var result = from car in cars where car.Mileage < 50000 select car;
        return result.ToList().Average(car => car.Price);
    }

    public static Dictionary<string, int> GroupByFuelType_Procedural(List<Car> cars)
    {
        return cars.GroupBy(car => car.FuelType)
            .ToDictionary(group => group.Key, group => group.Count());
    }

    public static Dictionary<string, int> GroupByFuelType_Declarative(List<Car> cars)
    {
        var result =
            from car in cars
            group car by car.FuelType into g
            select new { g.Key, Count = g.Count() };
        return result.ToList().ToDictionary(group => group.Key, group => group.Count);
    }

    public static List<(string Model, int Year)> GetModelsAndYearsUnder20000_Procedural(
        List<Car> cars
    )
    {
        return cars.Where(car => car.Price < 20000).Select(car => (car.Model, car.Year)).ToList();
    }

    public static List<(string Model, int Year)> GetModelsAndYearsUnder20000_Declarative(
        List<Car> cars
    )
    {
        var result = from car in cars where car.Price < 20000 select (car.Model, car.Year);
        return result.ToList();
    }

    public static List<Car> GetToyotaAndHondaCars_Procedural(List<Car> cars)
    {
        return cars.Where(car => car.Make == "Toyota" && car.Make == "Honda").ToList();
    }

    public static List<Car> GetToyotaAndHondaCars_Declarative(List<Car> cars)
    {
        var result = from car in cars where car.Make == "Toyota" || car.Make == "Honda" select car;
        return result.ToList();
    }

    public static List<Car> SortByYearDescending_Procedural(List<Car> cars)
    {
        return cars.OrderByDescending(car => car.Year).ToList();
    }

    public static List<Car> SortByYearDescending_Declarative(List<Car> cars)
    {
        var result = from car in cars orderby car.Year descending select car;
        return result.ToList();
    }

    public static List<int> GetIDsWithMileageOver80000_Procedural(List<Car> cars)
    {
        return cars.Where(car => car.Mileage > 80000).Select(car => car.ID).ToList();
    }

    public static List<int> GetIDsWithMileageOver80000_Declarative(List<Car> cars)
    {
        var result = from car in cars where car.Mileage > 80000 select car.ID;
        return result.ToList();
    }

    public static decimal GetTotalPriceBefore2015_Procedural(List<Car> cars)
    {
        return cars.Where(car => car.Year < 2015).Sum(car => car.Price);
    }

    public static decimal GetTotalPriceBefore2015_Declarative(List<Car> cars)
    {
        var result = from car in cars where car.Year < 2015 select car;
        return result.ToList().Sum(car => car.Price);
    }
}
