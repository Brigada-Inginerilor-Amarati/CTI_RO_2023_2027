/*
Creați o clasă AgențieImobiliară, care gestionează diverse proprietăți. Proprietatea trebuie implementată folosind următoarea diagramă de clasă:
nr -> poza 


Fiecare clasă din ierarhie trebuie să conțină proprietățile corespunzătoare afișate în diagrama de mai sus și să suprascrie metoda ToString() corespunzătoare.

Notă: Proprietatea SuprafațăTotală va calcula suma dintre SuprafațăInterioară și SuprafațăExterioară.

Clasa AgențieImobiliară va conține o listă de proprietăți. Va avea următoarele metode:

AdaugăProprietate(Proprietate proprietate) - adaugă o nouă proprietate în listă
ÎnchiriazăProprietate(string adresă) - închiriază proprietatea de la adresa dată. (Este necesară o verificare pentru a se asigura că proprietatea este închiriabilă.)
Adăugați cel puțin o casă, un apartament și un apartament închiriabil în lista de proprietăți.
*/

using System;
using System.Collections.Generic;
using System.Linq;

namespace Agentie{
    // interfata
    public interface IRentable{
        bool IsRented { get; set; }
        double MonthlyRent { get; set; }
    }

    // clasa abstracta
    public abstract class Property{
        public string Address { get; set; }
        public double IndoorArea { get; set; }
        public double PropertyValue { get; set; }

        public virtual double TotalArea => IndoorArea;

        public Property(string address, double indoorArea, double propertyValue){
            Address = address;
            IndoorArea = indoorArea;
            PropertyValue = propertyValue;
        }

        public override string ToString(){
            return $"Property: Address: {Address}, Indoor area: {IndoorArea} m2, Property value: {PropertyValue} euro";
        }
    }

    // clasa House
    public class House : Property{
        public double OutdoorArea { get; set; }
        public override double TotalArea => IndoorArea + OutdoorArea;

        public House(string address, double indoorArea, double propertyValue, double outdoorArea) : base(address, indoorArea, propertyValue){
            OutdoorArea = outdoorArea;
        }

        public override string ToString(){
            return $"House: {base.ToString()}, Outdoor area: {OutdoorArea} m2, Total area: {TotalArea} m2";
        }
    }

    // clasa Apartment
    public class Apartment : Property{
        public int Floor { get; set; }
        public bool HasElevator { get; set; }

        public Apartment(string address, double indoorArea, double propertyValue, int floor, bool hasElevator) : base(address, indoorArea, propertyValue){
            Floor = floor;
            HasElevator = hasElevator;
        }

        public override string ToString(){
            return $"Apartment: {base.ToString()}, Floor: {Floor}, Has elevator: {HasElevator}";
        }
    }

    // clasa Apartament de inchiriat
    public class RentableApartment : Apartment, IRentable{
        public bool IsRented { get; set; }
        public double MonthlyRent { get; set; }

        public RentableApartment(string address, double indoorArea, double propertyValue, int floor, bool hasElevator, double monthlyRent) : base(address, indoorArea, propertyValue, floor, hasElevator){
            MonthlyRent = monthlyRent;
            IsRented = false;
        }

        public override string ToString(){
            string rentedStatus = IsRented ? "Rented" : "Not rented";
            return $"Rentable Apartment: {base.ToString()}, Monthly rent: {MonthlyRent} euro, Rented status: {rentedStatus}";
        }
    }

    // clasa AgențieImobiliară
    public class RealEstateAgency{
        private List<Property> properties = new List<Property>();

        public void AddProperty(Property property){
            properties.Add(property);
            Console.WriteLine($"Property added: {property.ToString()}");
        }

        public void RentProperty(string address) {
            var property = properties.FirstOrDefault(p => p.Address.Equals(address, StringComparison.OrdinalIgnoreCase));

            if (property == null) {
                Console.WriteLine($"No property found at address: {address}");
                return;
            }

            if (property is IRentable rentable) {
                if (!rentable.IsRented) {
                    rentable.IsRented = true;
                    Console.WriteLine($"Property at {address} has been rented for {rentable.MonthlyRent}.");
                }
                else {
                    Console.WriteLine($"Property at {address} is already rented!");
                }
            }
            else {
                Console.WriteLine($"Property at {address} is not rentable.");
            }
        }

        public void showAllProperties(){
            Console.WriteLine("\n All properties:\n");

            foreach (Property property in properties){
                Console.WriteLine(property.ToString());
                Console.WriteLine();
            }
        }
    }

    public class Program{
        public static void Main(string[] args){
            RealEstateAgency agency = new RealEstateAgency();

            agency.AddProperty(new House("Str Branduselor nr 26", 100, 100000, 200));
            agency.AddProperty(new Apartment("Piata Victoriei nr 7", 80, 80000, 2, true));
            agency.AddProperty(new RentableApartment("Str Trandafirilor nr 10", 70, 70000, 1, false, 1000));

            agency.showAllProperties();

            agency.RentProperty("Str Branduselor nr 26");
            agency.RentProperty("Str Trandafirilor nr 10");
            agency.RentProperty("Piata Victoriei nr 7");
            agency.RentProperty("Str Lalelelor nr 12");
        }
    }

}