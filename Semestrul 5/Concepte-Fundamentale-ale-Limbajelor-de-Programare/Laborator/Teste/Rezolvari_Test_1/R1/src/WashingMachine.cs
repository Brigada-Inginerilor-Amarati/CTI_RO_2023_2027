/*
O clasa WashingMachine, care mosteneste Appliance si contine: (1.5p)
- override la metoda Activate, care seteaza nivelul de putere pe MaxPower
- override la metoda Deactivate, care seteaza nivelul de putere pe 0.
- override la metoda ToString pentru a afisa toate proprietatile clasei.
*/

namespace Test_1_R1;

class WashingMachine : Appliance
{
    public WashingMachine(string brand, double maxPower, double currentPower)
        : base(brand, maxPower, currentPower) { }

    public override void Activate()
    {
        CurrentPower = MaxPower;
    }

    public override void Deactivate()
    {
        CurrentPower = 0;
    }

    public override string ToString()
    {
        return $"WashingMachine: Brand={Brand}, MaxPower={MaxPower}, CurrentPower={CurrentPower}";
    }
}
