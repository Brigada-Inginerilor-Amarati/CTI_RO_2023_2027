/*
O clasa abstracta Appliance, care contine: (1p)
- Brand
- MaxPower
- CurrentPower
- un constructor care initializeaza cele 3 proprietati.
- o metoda abstracta Activate
- o metoda abstracta Deactivate
*/

namespace Test_1_R1;

abstract class Appliance
{
    protected string Brand { get; set; }
    protected double MaxPower { get; set; }
    protected double CurrentPower { get; set; }

    public Appliance(string brand, double maxPower, double currentPower)
    {
        Brand = brand;
        MaxPower = maxPower;
        CurrentPower = currentPower;
    }

    public abstract void Activate();
    public abstract void Deactivate();
}
