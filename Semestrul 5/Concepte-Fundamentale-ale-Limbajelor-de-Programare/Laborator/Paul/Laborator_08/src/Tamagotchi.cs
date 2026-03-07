namespace Laborator_08;

class Tamagotchi
{
    private string Name;
    private int Food;
    private int HungerRate;
    private char Key;
    private InputReader inputReader;
    private bool IsAlive;

    private const int FOOD_INCREMENT = 5;
    private const int MAX_FOOD = 20;
    private const int FOOD_DECREMENT = 3;

    public Tamagotchi(string name, int food, int hungerRate, char key, InputReader ir)
    {
        Name = name;
        Food = food;
        HungerRate = hungerRate;
        IsAlive = true;
        Key = key;
        inputReader = ir;
        Subscribe();
    }

    public void Subscribe()
    {
        inputReader.OnKeyPressed += HandleKeyPressed;
    }

    public void Unsubscribe()
    {
        inputReader.OnKeyPressed -= HandleKeyPressed;
    }

    public void HandleKeyPressed(object sender, string chars)
    {
        if (chars.Contains(Key))
        {
            Food += FOOD_INCREMENT;
        }
    }

    public async Task Run()
    {
        while (IsAlive)
        {
            await Task.Delay(HungerRate * 1000);
            Food -= FOOD_DECREMENT;
            Console.WriteLine(this);
            if (Food <= 0 || Food > MAX_FOOD)
            {
                IsAlive = false;
            }
        }

        Console.WriteLine(this);
    }

    public override string ToString()
    {
        if (IsAlive)
        {
            return $"{Name} este sănătos și în viață. Mâncare rămasă: {Food}";
        }
        else
        {
            return $"{Name} este mort :(";
        }
    }
}
