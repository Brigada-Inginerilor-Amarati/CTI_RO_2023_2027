namespace RealEstateNamespace;

abstract class Property
{
    public string Address { get; }
    public decimal PropertyValue { get; }
    public decimal IndoorArea { get; }

    public Property(string Address, decimal PropertyValue, decimal IndoorArea)
    {
        this.Address = Address;
        this.PropertyValue = PropertyValue;
        this.IndoorArea = IndoorArea;
    }

    public override string ToString()
    {
        return $"Address: {Address}, PropertyValue: {PropertyValue}, IndoorArea: {IndoorArea}";
    }
}
