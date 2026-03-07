/*
1. Implementati o metoda ConvertTemperature care primeste ca parametru temperatura in Kelvin si 
returneaza true daca temperatura este mai mare decat 0K. In plus, metoda returneaza temperatura in 
grade Celsius prin intermediul unui alt parametru. (2p)
C = K – 273.15


2. Implementati o metoda All care primeste ca parametru o lista de float si o conditie (o
funcție care primește un float și returnează un bool) si returneaza true daca toate elementele listei 
respecta conditia. In caz contrar, metoda returneaza false. (2p)

3. Creati urmatoare ierarhie de clase:
O clasa abstracta Appliance, care contine: (1p)
- Brand
- MaxPower
- CurrentPower
- un constructor care initializeaza cele 3 proprietati.
- o metoda abstracta Activate
- o metoda abstracta Deactivate
O clasa WashingMachine, care mosteneste Appliance si contine: (1.5p)
- override la metoda Activate, care seteaza nivelul de putere pe MaxPower
- override la metoda Deactivate, care seteaza nivelul de putere pe 0.
- override la metoda ToString pentru a afisa toate proprietatile clasei.
O clasa Refrigerator, care mosteneste Appliance si contine: (1.5p)
- IdlePower – initializat prin constructor
- override la metoda Activate, care seteaza nivelul de putere pe MaxPower / 2
- override la metoda Deactivate, care seteaza nivelul de putere pe IdlePower
- override la metoda ToString pentru a afisa toate proprietatile clasei.
Adaugati cel putin un obiect din fiecare clasa (WashingMachine si Refrigerator) intr-o lista de tip 
Appliance, apoi apelati metodele implementate pentru fiecare obiect astfel incat sa se poata observa 
modul de functionare al acestora. Pentru afisarea starii obiectelor se va folosi metoda ToString. (1p)
Oficiu: 1p

*/

namespace T1R1{
    // task 1
    class Task1{
    public static bool ConvertTemperature(in double Kelvin, out double Celsius){   // in pentru a evita copierea valorii Kelvin si out pentru a returna temperatura in Celsius
        if (Kelvin < 0){
            Celsius = 0;
            return false;
        }

            Celsius = Kelvin - 273.15;
            return true;
        }
    }

    // task 2

    class Task2{
        public static bool All(List<float> list, Predicate<float> predicate){       // de ce Predicate nu are bool? Pentru ca este un delegat care poate fi orice functie care primeste un float si returneaza un bool
            foreach (var item in list){
                if (!predicate(item)){
                    return false;
                }
            }
            return true;
        }
    }

    // task 3
    abstract class Appliance{
        protected string Brand { get; set; }
        protected double MaxPower { get; set; }
        protected double CurrentPower { get; set; }

        public Appliance(string brand, double maxPower, double currentPower){
            Brand = brand;
            MaxPower = maxPower;
            CurrentPower = currentPower;
        }

        public abstract void Activate();
        public abstract void Deactivate();
    }

    class WashingMachine : Appliance{

        public WashingMachine(string brand, double maxPower, double currentPower) : base(brand, maxPower, currentPower){
        }

        public override void Activate(){
            CurrentPower = MaxPower;
        }

        public override void Deactivate(){
            CurrentPower = 0;
        }

        public override string ToString(){
            return $"WashingMachine: Brand={Brand}, MaxPower={MaxPower}, CurrentPower={CurrentPower}";
        }
    }
    class Refrigerator : Appliance{
        protected double IdlePower { get; set; }
        
        public Refrigerator(string brand, double maxPower, double currentPower, double idlePower) : base(brand, maxPower, currentPower){
            IdlePower = idlePower;
        }
        
        public override void Activate(){
            CurrentPower = MaxPower / 2;
        }

        public override void Deactivate(){
            CurrentPower = IdlePower;
        }

        public override string ToString(){
            return $"Refrigerator: Brand={Brand}, MaxPower={MaxPower}, CurrentPower={CurrentPower}, IdlePower={IdlePower}";
        }
    }   

    class Program{
        public static void Main(string[] args){
            // test 1
            Console.WriteLine("Task 1:");
            double Kelvin = 303.15;
            double Celsius = 0.0;
            if (Task1.ConvertTemperature(in Kelvin, out Celsius)){
                Console.WriteLine($"Temperatura in Celsius: {Celsius}");
            }
            else{
                Console.WriteLine("Temperatura este sub 0K");
            }

            // test 2
            Console.WriteLine("Task 2:");
            // random list of floats
            List<float> list = new List<float>();
            for (int i = 0; i < 10; i++){
                list.Add(Random.Shared.NextSingle() * 100);
            }
            Console.WriteLine("Lista: " + string.Join(" ", list));
            Console.WriteLine("Toate elementele listei sunt pozitive: " + Task2.All(list, (x) => x > 0));

            // test 3
            Console.WriteLine("Task 3:");
            List<Appliance> appliances = new List<Appliance>();
            appliances.Add(new WashingMachine("WashingMachine", 1000, 0));
            appliances.Add(new Refrigerator("Refrigerator", 1000, 0, 100));
            foreach (var appliance in appliances){
                Console.WriteLine(appliance.ToString());
                appliance.Activate();
                Console.WriteLine("Activated: " + appliance.ToString());
                appliance.Deactivate();
                Console.WriteLine("Deactivated: " + appliance.ToString());
                Console.WriteLine("--------------------------------");
            }
            Console.WriteLine("Appliances: " + string.Join(" ", appliances));
            Console.WriteLine("--------------------------------");

        }
    }

}