/*
O clasa CloudStorage, care mosteneste Storage si contine: (1.5p)
- ReservedCapacity – initializat prin constructor
- override la metoda Load, care adauga 1.2 * capacitatea primita ca parametru la CurrentCapacity,
tinand cont ca CurrentCapacity nu poate sa creasca peste MaxCapacity.
- override la metoda Unload, care elibereaza capacitatea primita ca parametru din CurrentCapacity,
tinand cont ca CurrentCapacity nu poate sa scada sub ReservedCapacity.
- override la metoda ToString, pentru a afisa toate proprietatile clasei
*/
namespace Test_1_R2;

class CloudStorage : Storage
{
    private const double RESERVED_CAPACITY_MULTIPLIER = 1.2;

    protected int ReservedCapacity { get; set; }

    public CloudStorage(
        string manufacturer,
        int maxCapacity,
        int currentCapacity,
        int resevedCapacity
    )
        : base(manufacturer, maxCapacity, currentCapacity)
    {
        ReservedCapacity = resevedCapacity;
    }

    public override void Load(int capacity)
    {
        int nextCapacity = CurrentCapacity + (int)(capacity * RESERVED_CAPACITY_MULTIPLIER);
        CurrentCapacity = nextCapacity > MaxCapacity ? MaxCapacity : nextCapacity;
    }

    public override void Unload(int capacity)
    {
        int nextCapacity = CurrentCapacity - capacity;
        CurrentCapacity = nextCapacity < ReservedCapacity ? ReservedCapacity : nextCapacity;
    }

    public override String ToString()
    {
        return $"CloudStorage: Manufacturer={Manufacturer}, MaxCapacity={MaxCapacity}, CurrentCapacity={CurrentCapacity}, ReservedCapacity={ReservedCapacity}";
    }
}
