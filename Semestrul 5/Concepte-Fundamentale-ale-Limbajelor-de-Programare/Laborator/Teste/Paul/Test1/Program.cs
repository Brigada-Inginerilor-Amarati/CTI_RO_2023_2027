// STUDENT 12

namespace Test1;

class Program
{
    /*
     1. Implementati o functie India23() care primeste 2 numere int si le inverseaza daca ambele sunt mai mari decat 81. (2p)
     */

    static void India23(ref int a, ref int b)
    {
        if (a > 81 && b > 81)
        {
            int temp = a;
            a = b;
            b = temp;
        }
    }

    /*
    2. Implementati o functie India12() care primeste o lista de ulong si doua functii.
    Prima functie reprezinta o conditie, adica primeste un ulong si returneaza un boolean, iar a doua functie primeste un ulong si returneaza un ulong.
    India12() va returna o noua lista in care toate elementele din lista initiala care indeplinesc conditia primita ca parametru vor fi transformate in alta valoare de a doua functie primita ca parametru. (2p)
    */

    public delegate bool MyPredicate(ulong x);
    public delegate ulong MyFunction(ulong x);

    static List<ulong> India12(List<ulong> list, MyPredicate predicate, MyFunction function)
    {
        var result = new List<ulong>();
        foreach (var item in list)
            if (predicate(item))
                result.Add(function(item));

        return result;
    }

    /*
    3. In programul principal, creati o colectie de tip Articol_stiintific si adaugati cel putin 4 obiecte.(1p)
    Parcurgeti colectia si apelati metodele Salut(). (0.5p)
    Parcurgeti colectia si afisati reprezentarile ToString()
    */

    static void Test3()
    {
        var articole = new List<Articol_stiintific>();
        articole.Add(
            new Articol_stiintific_de_jurnal("Articol 1", "Autor 1", 2000, 100, "1234", 3.14f)
        );
        articole.Add(
            new Articol_stiintific_de_conferinta("Articol 2", "Autor 2", 2005, 120, "1234", "1")
        );
        articole.Add(
            new Articol_stiintific_de_jurnal("Articol 3", "Autor 3", 2015, 150, "5678", 2.71f)
        );
        articole.Add(
            new Articol_stiintific_de_conferinta("Articol 4", "Autor 4", 2025, 200, "5678", "2")
        );

        foreach (var articol in articole)
        {
            articol.Salut();
            Console.WriteLine(articol.ToString());
        }
    }

    static void Main(string[] args)
    {
        var a = 100;
        var b = 90;
        India23(ref a, ref b);
        Console.WriteLine($"a = {a}, b = {b}");

        a = 100;
        b = 80;
        India23(ref a, ref b);
        Console.WriteLine($"a = {a}, b = {b}");

        Console.WriteLine("--------------------------------");

        MyPredicate predicate = (x) => x % 2 == 0;
        MyFunction function = (x) => x * 2;

        var list = new List<ulong> { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        Console.WriteLine(string.Join(", ", list));

        var result = India12(list, predicate, function);
        Console.WriteLine(string.Join(", ", result));

        Console.WriteLine("--------------------------------");

        Test3();
    }
}
