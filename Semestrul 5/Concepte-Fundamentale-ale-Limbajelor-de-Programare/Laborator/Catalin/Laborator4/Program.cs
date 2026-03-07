namespace Laborator4;

class MainClass
{
    interface IRentable
    {
        bool IsRented { get; set;}
        int MonthlyRent { get; set; }
    }


    abstract class Property
    {
        public string Address { get; set; }

        public int IndoorArea{get;set;}
        
        int PropertyValue{get;set;}

        public Property(string address, int indoorArea, int propertyValue)
        {
            Address = address;
            IndoorArea = indoorArea;
            PropertyValue = propertyValue;
        }
    public override string ToString()
    {
        return $"{Address} {IndoorArea} {PropertyValue}";
    }
        
    }

    class House : Property
    {
        
        public int OutdoorArea { get; set; }
        public int TotalArea { get; set; }

        public House(string address, int indoorArea, int propertyValue, int outdoorArea) : base(address, indoorArea, propertyValue)
        {
            this.OutdoorArea = outdoorArea;
            this.TotalArea = OutdoorArea + base.IndoorArea;
        }

        public override string ToString()
        {
            return base.ToString() + $" {OutdoorArea} {TotalArea}";
        }
    }
    
    class Apartament : Property
    {
        
        public int Floor { get; set; }
        public bool HasElevator { get; set; }

        public Apartament(int floor, bool hasElevator, string address, int indoorArea, int propertyValue) : base(address, indoorArea, propertyValue)
        {
         
            this.Floor = floor;
            this.HasElevator = hasElevator;
        }

        public override string ToString()
        {
            return base.ToString() + $" {Floor} {HasElevator}";
        }
    }

    class RentableApartment : Apartament, IRentable
    {
        public bool IsRented { get; set; }
        public int MonthlyRent { get; set; }

        public RentableApartment(int monthlyRent, int floor, bool hasElevator, string address, int propertyValue, int indoorArea) : base(floor, hasElevator, address, indoorArea, propertyValue)
        {
            this.IsRented = false;
            this.MonthlyRent = monthlyRent;
        }

        public override string ToString()
        {
            return base.ToString() + " " + IsRented + " " + MonthlyRent;
        }
        
    }

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

            if (property is IRentable rentable)
            {
                if (rentable.IsRented)
                {
                    throw new Exception("Rented");
                }

                rentable.IsRented = true;
            }
            else
            {
                throw new Exception("Not rentable");
            }
        }

        public override string ToString()
        {
            return $"Properties:\n{string.Join("\n", Properties.Select(p => p.ToString()))}";
        }
    }


    static void Main()
    {
        Property p1 = new House("Livada", 1000, 100, 100);
        Property p2 = new Apartament(1, true, "Circumvalatiuni", 2000, 200);
        Property p3 = new RentableApartment(3000, 1, true, "Marcus", 3000, 300);
        RealEstateAgency a = new RealEstateAgency();
        a.AddProperty(p1);
        a.AddProperty(p2);
        a.AddProperty(p3);
        Console.WriteLine(a);

      
        try
        {
            a.RentProperty("Livada");
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
        
        try
        {
            a.RentProperty("Marcus");
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
     
        try
        {
            a.RentProperty("Nuexista");
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
     
    }
    
}