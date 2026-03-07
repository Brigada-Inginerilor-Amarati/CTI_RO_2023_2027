/*
O clasa HardDisk, care mosteneste Storage si contine: (1.5p)
- override la metoda Load, care adauga capacitatea primita ca parametru la CurrentCapacity, tinand
cont ca CurrentCapacity nu poate sa creasca peste MaxCapacity.
- override la metoda Unload, care elibereaza capacitatea primita ca parametru din CurrentCapacity,
tinand cont ca CurrentCapacity nu poate sa scada sub 0.
- override la metoda ToString, pentru a afisa toate proprietatile clasei
*/

namespace Test_1_R2;

class HardDisk : Storage
{
    public HardDisk(string manufacturer, int maxCapacity, int currentCapacity)
        : base(manufacturer, maxCapacity, currentCapacity) { }

    public override void Load(int capacity)
    {
        int nextCapacity = CurrentCapacity + capacity;
        CurrentCapacity = nextCapacity > MaxCapacity ? MaxCapacity : nextCapacity;
    }

    public override void Unload(int capacity)
    {
        int nextCapacity = CurrentCapacity - capacity;
        CurrentCapacity = nextCapacity < 0 ? 0 : nextCapacity;
    }

    public override String ToString()
    {
        return $"HardDisk: Manufacturer={Manufacturer}, MaxCapacity={MaxCapacity}, CurrentCapacity={CurrentCapacity}";
    }
}
