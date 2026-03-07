namespace RealEstateNamespace;

class Apartment : Property
{
    public int Floor { get; }
    public bool HasElevator { get; }

    public Apartment(
        int Floor,
        bool HasElevator,
        string Address,
        decimal PropertyValue,
        decimal IndoorArea
    )
        : base(Address, PropertyValue, IndoorArea)
    {
        this.Floor = Floor;
        this.HasElevator = HasElevator;
    }

    public override string ToString()
    {
        return base.ToString() + $", Floor: {Floor}, HasElevator: {HasElevator}";
    }
}
