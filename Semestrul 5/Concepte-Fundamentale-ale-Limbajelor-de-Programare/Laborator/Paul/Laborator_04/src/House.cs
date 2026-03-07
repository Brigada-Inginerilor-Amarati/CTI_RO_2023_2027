namespace RealEstateNamespace;

class House : Property
{
    public decimal OutdoorArea { get; }
    public decimal TotalArea { get; private set; }

    public House(string Address, decimal PropertyValue, decimal IndoorArea, decimal OutdoorArea)
        : base(Address, PropertyValue, IndoorArea)
    {
        this.OutdoorArea = OutdoorArea;
        this.TotalArea = OutdoorArea + base.IndoorArea;
    }

    public override string ToString()
    {
        return base.ToString() + $", OutdoorArea: {OutdoorArea}, TotalArea: {TotalArea}";
    }
}
