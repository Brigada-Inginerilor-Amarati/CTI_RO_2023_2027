/*
1. Implementați o funcție numită Filtru, care primește o funcție booleană ca delegat și o listă și returnează o listă nouă care conține elementele care îndeplinesc condiția. public static List<int> Filtru(MyDelegate condiție, List<int> listă)

2. Implementați o metodă statică FGX, care primește 2 delegați ca parametri și un float x și returnează valoarea compusă a celor două funcții date.

public static float FGX(MyDelegate del1, MyDelegate del2, float x)

Testați implementarea folosind următoarele funcții:

public static float f(float x){ return x * 3; }

public static float g(float x){ return x - 2; }

3. Implementati o metoda statica Comp, care primeste 2 functii (int->int) f si g, si returneaza o functie care reprezinta f compus cu g.
*/

delegate bool MyPredicate(int x);

delegate float MyFloatDelegate(float x);

delegate int MyIntDelegate(int x);

class Program
{
    // TASK 1
    static bool MyIsEven(int x)
    {
        return x % 2 == 0;
    }

    static List<int> Filter(MyPredicate predicate, List<int> list)
    {
        List<int> filtered = new List<int>();
        foreach (var x in list)
            if (predicate(x))
                filtered.Add(x);
        return filtered;
    }

    static void PopulateList(List<int> list, int n)
    {
        list.Clear();
        for (var i = 0; i < n; i++)
            list.Add(i);
    }

    // TASK 2
    static float f(float x)
    {
        return x * 3;
    }

    static float g(float x)
    {
        return x - 2;
    }

    static float FGX(MyFloatDelegate f, MyFloatDelegate g, float x)
    {
        return f(g(x));
    }

    static int f(int x)
    {
        return x + 3;
    }

    static int g(int x)
    {
        return x * 3;
    }

    static MyIntDelegate Comp(MyIntDelegate f, MyIntDelegate g)
    {
        return x => f(g(x));
    }

    static void Main(string[] args)
    {
        //Predicate<int> isEven = n => n % 2 == 0;
        MyPredicate MyIsEven = Program.MyIsEven;

        List<int> list = new List<int>();
        PopulateList(list, 10);

        List<int> filteredList = Filter(MyIsEven, list);
        foreach (var item in filteredList)
            Console.Write(item + " ");

        MyFloatDelegate float_f = Program.f;
        MyFloatDelegate float_g = Program.g;

        float x = 10;
        Console.WriteLine("\nF(G(X)) = " + FGX(float_f, float_g, x));

        int y = 10;
        MyIntDelegate int_f_g = Comp(Program.f, Program.g);
        Console.WriteLine("\nF(G(X)) = " + int_f_g(y));
    }
}
