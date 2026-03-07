namespace T1R2{
    /*
            1. Implementati o metoda CalculateScore care primeste 2 valori basePoints si multiplier si 
        returneaza true daca basePoints * multiplier este mai mare decat 0. In plus, metoda returneaza 
        basePoints * multiplier prin intermediul unui alt parametru. (2p)
    */
    class Task1{
        public static bool CalculateScore(in double basePoints, in double multiplier, out double result){
            if(basePoints * multiplier < 0){
                result = 0;
                return false;
            }

            result = basePoints * multiplier;
            return true;
        }
    }

    /*
            2. Implementati o metoda Any care primeste ca parametru o lista de double si o conditie (o
        funcție care primește un double și returnează un bool) si returneaza true daca exista cel putin un 
        element in lista care respecta conditia. In caz contrar, metoda returneaza false. (2p)
    */

    class Task2{
        public static bool Any(List<double> list, Predicate <double> predicate){
            foreach(var item in list){
                if(predicate(item)){
                    return true;
                }
            }
            return false;
        }
    }

    /*
                3. Creati urmatoare ierarhie de clase:
            O clasa abstracta Storage, care contine: (1p)
            - Manufacturer
            - MaxCapacity
            - CurrentCapacity
            - Un constructor care initializeaza cele 3 proprietati.
            - O metoda abstracta Load (int)
            - O metoda abstracta Unload (int)
            O clasa HardDisk, care mosteneste Storage si contine: (1.5p)
            - override la metoda Load, care adauga capacitatea primita ca parametru la CurrentCapacity, tinand 
            cont ca CurrentCapacity nu poate sa creasca peste MaxCapacity.
            - override la metoda Unload, care elibereaza capacitatea primita ca parametru din CurrentCapacity, 
            tinand cont ca CurrentCapacity nu poate sa scada sub 0.
            - override la metoda ToString, pentru a afisa toate proprietatile clasei
            O clasa CloudStorage, care mosteneste Storage si contine: (1.5p)
            - ReservedCapacity – initializat prin constructor
            - override la metoda Load, care adauga 1.2 * capacitatea primita ca parametru la CurrentCapacity, 
            tinand cont ca CurrentCapacity nu poate sa creasca peste MaxCapacity.
            - override la metoda Unload, care elibereaza capacitatea primita ca parametru din CurrentCapacity, 
            tinand cont ca CurrentCapacity nu poate sa scada sub ReservedCapacity.
            - override la metoda ToString, pentru a afisa toate proprietatile clasei
            Adaugati cel putin un obiect din fiecare clasa ( HardDisk si CloudStorage) intr-o lista de tip 
            Storage, apoi apelati metodele implementate pentru fiecare obiect astfel incat sa se poata observa 
            modul de functionare al acestora. Pentru afisarea starii obiectelor se va folosi metoda ToString. (1p)
            Oficiu: 1p
    */
    abstract class Storage{
        protected string Manufacturer { get; set; }
        protected double MaxCapacity { get; set; }
        protected double CurrentCapacity { get; set; }

        public Storage(string manufacturer, double maxCapacity, double currentCapacity){
            Manufacturer = manufacturer;
            MaxCapacity = maxCapacity;
            CurrentCapacity = currentCapacity;
        }

        public abstract void Load(int capacity);
        public abstract void Unload(int capacity);
    }

    class HardDisk : Storage{
        public HardDisk(string manufacturer, double maxCapacity, double currentCapacity) : base(manufacturer, maxCapacity, currentCapacity){

        }

        public override void Load(int capacity){
            double nextCapacity = CurrentCapacity + capacity;
            CurrentCapacity = nextCapacity > MaxCapacity ? MaxCapacity : nextCapacity;
        }

        public override void Unload(int capacity){
            double nextCapacity = CurrentCapacity - capacity;
            CurrentCapacity = nextCapacity < 0 ? 0 : nextCapacity;
        }

        public override string ToString(){
            return $"HardDisk: Manufacturer={Manufacturer}, MaxCapacity={MaxCapacity}, CurrentCapacity={CurrentCapacity}";
        }
    }

    class CloudStorage : Storage{
        protected double ReservedCapacity { get; set; }

        public CloudStorage(string manufacturer, double maxCapacity, double currentCapacity, double reservedCapacity) : base(manufacturer, maxCapacity, currentCapacity){
            ReservedCapacity = reservedCapacity;
        }

        public override void Load(int capacity){
            double nextCapacity = CurrentCapacity + (capacity * 1.2);
            CurrentCapacity = nextCapacity > MaxCapacity ? MaxCapacity : nextCapacity;
        }

        public override void Unload(int capacity){
            double nextCapacity = CurrentCapacity - capacity;
            CurrentCapacity = nextCapacity < ReservedCapacity ? ReservedCapacity : nextCapacity;
        }

        public override string ToString(){
            return $"CloudStorage: Manufacturer={Manufacturer}, MaxCapacity={MaxCapacity}, CurrentCapacity={CurrentCapacity}, ReservedCapacity={ReservedCapacity}";
        }
    }


    class Program{
        public static void Main(string[] args){

            // test 1
            Console.WriteLine("Task 1:");
            double basePoints = 10.0;
            double multiplier = 10.0;
            double result = 0;
            if(Task1.CalculateScore(in basePoints, in multiplier, out result)){
                Console.WriteLine("Result: " + result);
            }
            else{
                Console.WriteLine("Result is negative!");
            }

            // test 2
            Console.WriteLine("Task 2:");
            List<double> list = new List<double>();
            list.Add(1.0);
            list.Add(2.0);
            list.Add(3.0);
            list.Add(4.0);
            list.Add(5.0);
            if(Task2.Any(list, (x) => x > 0)){
                Console.WriteLine("There is at least one positive element in the list!");
            }
            else{
                Console.WriteLine("There is no positive element in the list!");
            }

            // test 3
            Console.WriteLine("Task 3:");
            List<Storage> storage = new List<Storage>();
            storage.Add(new HardDisk("HardDisk", 1000, 0));
            storage.Add(new CloudStorage("CloudStorage", 1000, 0, 100));
            foreach(var item in storage){
                Console.WriteLine(item.ToString());
            }
            foreach(var item in storage){
                item.Load(100);
                Console.WriteLine("Loaded: " + item.ToString());
                item.Unload(100);
                Console.WriteLine("Unloaded: " + item.ToString());
            }
            Console.WriteLine("Storage: " + string.Join(" ", storage));
        }
    }
}