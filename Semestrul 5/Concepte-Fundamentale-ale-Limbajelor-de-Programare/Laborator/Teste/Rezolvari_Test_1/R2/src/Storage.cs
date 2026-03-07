/*
O clasa abstracta Storage, care contine: (1p)
- Manufacturer
- MaxCapacity
- CurrentCapacity
- Un constructor care initializeaza cele 3 proprietati.
- O metoda abstracta Load (int)
- O metoda abstracta Unload (int)
*/

namespace Test_1_R2;

abstract class Storage
{
    protected string Manufacturer { get; set; }
    protected int MaxCapacity { get; set; }
    protected int CurrentCapacity { get; set; }

    public Storage(string manufacturer, int maxCapacity, int currentCapacity)
    {
        Manufacturer = manufacturer;
        MaxCapacity = maxCapacity;
        CurrentCapacity = currentCapacity;
    }

    public abstract void Load(int capacity);
    public abstract void Unload(int capacity);
}
