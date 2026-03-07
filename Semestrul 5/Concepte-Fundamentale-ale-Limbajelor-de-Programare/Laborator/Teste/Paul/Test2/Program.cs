// R1

/*
1. Implementați o funcție FilterIndexes

Funcția primește:

    o listă de numere întregi,

    un predicat Func<int,bool> aplicat pe index. Returnați o listă cu elementele aflate pe pozițiile pentru care predicatul este adevărat. (1 p)
*/

List<int> FilterIndexes(List<int> list, Func<int, bool> predicate)
{
	List<int> result = new List<int>();
	for (int i = 0; i < list.Count; i++)
	{
		if (predicate(i))
		{
			result.Add(list[i]);
		}
	}
	return result;
}

List<int> list = new List<int> { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

List<int> filteredList = FilterIndexes(list, x => x % 2 == 0);

Console.WriteLine(string.Join(", ", filteredList));

/*
2.

a) Folosind LINQ, implementați o funcție care primește o listă de numere întregi și returnează suma pătratelor numerelor pare. (1p)
b) Folosind LINQ, implementați o funcție care, pentru o listă de numere reale și un selector Func<float,float>, returnează valoarea maximă după transformare. (1p)
*/

int SumOfSquaresOfEvenNumbers(List<int> list)
{
	return list.Where(x => x % 2 == 0).Select(x => x * x).Sum();
}

List<int> list2 = new List<int> { 1, 2, 3, 4, 5, 10 }; // 2^2 + 4^2 + 10^2 = 4 + 16 + 100 = 120

int sumOfSquaresOfEvenNumbers = SumOfSquaresOfEvenNumbers(list2);

Console.WriteLine(sumOfSquaresOfEvenNumbers);

float MaxValueAfterTransformation(List<float> list, Func<float, float> selector)
{
	return list.Select(selector).Max();
}

List<float> list3 = new List<float> { -1.1f, 2.2f, -3.3f, 4.4f };

float maxValueAfterTransformation = MaxValueAfterTransformation(list3, x => x * x);

Console.WriteLine(maxValueAfterTransformation);

/*
3. Sistem de simulare a animalelor

    Clasa abstractă Animal (Name: read-only, Energy: int public get, private set, Eat() abstract)(1 p)

    Clase derivate Lion și Elephant (suprascriu Eat())

Lion: +[20..50] energie; Elephant: +[10..30].(1 p)

    Clasa ZooManager (listă de Animal, FeedAll())

Apelează Eat() , afișează Energy. (1.5 p)

    Clasa FeedingTimer ( un event Tick)

Hrănire periodică. (1.5 p)

    Main

contine 2 lei + 2 elefanți, abonare FeedAll() sau handler la Tick. (1 p)
*/

ZooManager zoo = new ZooManager();
zoo.AddAnimal(new Lion("L1"));
zoo.AddAnimal(new Lion("L2"));
zoo.AddAnimal(new Elephant("E1"));
zoo.AddAnimal(new Elephant("E2"));

FeedingTimer timer = new FeedingTimer(2000); // 2 second timer
timer.Tick += zoo.FeedAll;

Console.WriteLine("Starting simulation... Press Enter to stop.");
timer.Start();

Console.ReadLine();
timer.Stop();

abstract class Animal
{
	public readonly string Name;
	public int Energy { get; private set; }

	public Animal(string name)
	{
		Name = name;
		Energy = 0;
	}

	public abstract void Eat();

	protected void AddEnergy(int amount)
	{
		Energy += amount;
	}
}

class Lion : Animal
{
	public Lion(string name)
		: base(name) { }

	public override void Eat()
	{
		int energyGain = new Random().Next(20, 51);
		AddEnergy(energyGain);
	}

	public override string ToString()
	{
		return $"{Name} (Lion) has {Energy} energy";
	}
}

class Elephant : Animal
{
	public Elephant(string name)
		: base(name) { }

	public override void Eat()
	{
		int energyGain = new Random().Next(10, 31);
		AddEnergy(energyGain);
	}

	public override string ToString()
	{
		return $"{Name} (Elephant) has {Energy} energy";
	}
}

class ZooManager
{
	private List<Animal> animals;

	public ZooManager()
	{
		animals = new List<Animal>();
	}

	public void AddAnimal(Animal animal)
	{
		animals.Add(animal);
	}

	public void FeedAll()
	{
		Console.WriteLine("\nFeeding time!");
		foreach (Animal animal in animals)
		{
			animal.Eat();
			Console.WriteLine(animal);
		}
	}
}

class FeedingTimer
{
	private System.Timers.Timer timer;
	public event Action? Tick;

	public FeedingTimer(int interval)
	{
		timer = new System.Timers.Timer(interval);
		timer.Elapsed += OnTimedEvent;
		timer.AutoReset = true;
	}

	private void OnTimedEvent(Object? sender, System.Timers.ElapsedEventArgs e)
	{
		Tick?.Invoke();
	}

	public void Start()
	{
		timer.Start();
	}

	public void Stop()
	{
		timer.Stop();
	}
}
