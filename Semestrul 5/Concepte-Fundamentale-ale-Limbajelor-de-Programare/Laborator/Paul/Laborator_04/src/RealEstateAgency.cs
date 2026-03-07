namespace RealEstateNamespace;

class RealEstateAgency
{
    public List<Property> Properties { get; private set; } = new List<Property>();

    public void AddProperty(Property property)
    {
        Properties.Add(property);
    }

    public void RentProperty(string address)
    {
        Property property = Properties.Find(p => p.Address == address);

        if (property is Rentable rentable)
        {
            if (rentable.IsRented)
            {
                throw new Exception("Property is already rented");
            }

            rentable.IsRented = true;
        }
        else
        {
            throw new Exception("Property is not rentable");
        }
    }

    public override string ToString()
    {
        return $"Properties:\n{string.Join("\n", Properties.Select(p => p.ToString()))}";
    }
}
