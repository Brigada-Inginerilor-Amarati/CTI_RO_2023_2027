/*
Creați o clasă AgențieImobiliară, care gestionează diverse proprietăți. Proprietatea trebuie implementată folosind următoarea diagramă de clasă:
Fiecare clasă din ierarhie trebuie să conțină proprietățile corespunzătoare afișate în diagrama de mai sus și să suprascrie metoda ToString() corespunzătoare.

Notă: Proprietatea SuprafațăTotală va calcula suma dintre SuprafațăInterioară și SuprafațăExterioară.

Clasa AgențieImobiliară va conține o listă de proprietăți. Va avea următoarele metode:

    AdaugăProprietate(Proprietate proprietate) - adaugă o nouă proprietate în listă
    ÎnchiriazăProprietate(string adresă) - închiriază proprietatea de la adresa dată. (Este necesară o verificare pentru a se asigura că proprietatea este închiriabilă.)

Adăugați cel puțin o casă, un apartament și un apartament închiriabil în lista de proprietăți.
*/
using RealEstateNamespace;

class Program
{
    static void Main()
    {
        Property property1 = new House("Address123", 1000, 100, 100);
        Property property2 = new Apartment(1, true, "Address456", 2000, 200);
        Property property3 = new RentableApartment(3000, 1, true, "Address789", 3000, 300);

        RealEstateAgency agency = new RealEstateAgency();
        agency.AddProperty(property1);
        agency.AddProperty(property2);
        agency.AddProperty(property3);
        Console.WriteLine(agency);

        agency.RentProperty("Address789");
        try
        {
            agency.RentProperty("Address789");
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
    }
}
