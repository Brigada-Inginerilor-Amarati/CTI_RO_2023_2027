using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    /*public static Func<int, int> MaxF(int x, Func<int, int> f, Func<int, int> g)
    {
        if(f(x) > g(x))
        {
            return f;
        }
        else
        {
            return g;
        }
    }

    public static float DivizibileCu3(List<float> floatList)
    {
        return floatList.Where(x => x % 3 == 0).Sum();
    }

    public static bool allSatisfy(List<float> lista, Func<float, bool> conditie)
    {
        if(lista is null || lista.Count == 0)
        {
            Console.WriteLine("Lista nu contine elemente.");
        }
        else
        {
            return lista.All(condition);
        }
    }*/

    public static int MaxInX(List<int> intList, Func<int, int> f)
    {
        int maxim = 0;
        foreach(var element in intList)
        {
            if(f(element) > maxim)
            {
                maxim = f(element);
            }
        }
        return maxim;
    }

    public static List<float> listaImpare(List<float> floatList)
    {
        return floatList.Where(x => Math.Abs((int)x) % 2 == 1).ToList();
    }

    public static bool maiMariCa5(List<float> floatList, Func<float, bool> condition)
    {
        return floatList.Any(condition);
    }

    public static void Main(string[] args)
    {
        /*List<float> lista = { 1.2f, 3.4f, 4.5f, 6.6f, 8.2f};
        Func<float, bool> conditie = x => x % 4 == 0;
        bool ok = allSatisfy(lista, conditie);
        Console.WriteLine($"Elementele indeplinesc conditia?: {ok}.");*/

        List<int> intList = new List<int> { -1, -2, 0, 1, -3};
        Func<int, int> f = x => x * x;
        int m = MaxInX(intList, f);
        Console.WriteLine($"Functia are valoarea maxima egala cu {m}");
        List<float> floatList = new List<float> { 1.2f, 2.5f, 3.7f, 4.2f, 5.3f };
        List<float> OddList = listaImpare(floatList);
        foreach(float element in OddList)
        {
            Console.WriteLine(element + " ");
        }
        Func<float, bool> condition = x => x > 5;
        bool ok = maiMariCa5(floatList, condition);
        Console.WriteLine($"Sunt toate numerele mai mari ca 5? {ok}");
    }
}