/*
O clasa Refrigerator, care mosteneste Appliance si contine: (1.5p)
- IdlePower – initializat prin constructor
- override la metoda Activate, care seteaza nivelul de putere pe MaxPower / 2
- override la metoda Deactivate, care seteaza nivelul de putere pe IdlePower
- override la metoda ToString pentru a afisa toate proprietatile clasei.
*/

namespace Test_1_R1;

class Refrigerator : Appliance
{
    protected double IdlePower { get; set; }

    public Refrigerator(string brand, double maxPower, double currentPower, double idlePower)
        : base(brand, maxPower, currentPower)
    {
        IdlePower = idlePower;
    }

    public override void Activate()
    {
        CurrentPower = MaxPower / 2;
    }

    public override void Deactivate()
    {
        CurrentPower = IdlePower;
    }

    public override string ToString()
    {
        return $"Refrigerator: Brand={Brand}, MaxPower={MaxPower}, CurrentPower={CurrentPower}, IdlePower={IdlePower}";
    }
}
