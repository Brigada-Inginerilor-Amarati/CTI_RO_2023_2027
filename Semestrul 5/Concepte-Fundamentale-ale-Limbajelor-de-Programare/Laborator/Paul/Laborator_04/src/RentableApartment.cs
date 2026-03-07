namespace RealEstateNamespace;

class RentableApartment : Apartment, Rentable
{
    public bool IsRented { get; set; }
    public decimal MonthlyRent { get; set; }

    public RentableApartment(
        decimal MonthlyRent,
        int Floor,
        bool HasElevator,
        string Address,
        decimal PropertyValue,
        decimal IndoorArea
    )
        : base(Floor, HasElevator, Address, PropertyValue, IndoorArea)
    {
        this.IsRented = false;
        this.MonthlyRent = MonthlyRent;
    }

    public override string ToString()
    {
        return base.ToString() + $", IsRented: {IsRented}, MonthlyRent: {MonthlyRent}";
    }
}
