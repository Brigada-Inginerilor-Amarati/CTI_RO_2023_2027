/*
2. Implementați o metodă statică care primește două liste de tip List<int> și returnează o List<int> care conține elementele prezente în ambele liste. Asigurați-vă că lista rezultată nu are duplicate.

public static List Intersection(List l1, List l2)
*/

class Task2
{
    public static List<int> Intersection(List<int> l1, List<int> l2)
    {
        var intersect = new List<int>();

        foreach (var item in l1)
            if (l2.Contains(item))
                intersect.Add(item);

        return intersect;
    }

    public static void Main()
    {
        var l1 = new List<int> { 1, 2, 3, 4, 5 };
        var l2 = new List<int> { 3, 4, 5, 6, 7 };

        Console.WriteLine("LIST 1: " + string.Join(" ", l1));
        Console.WriteLine("LIST 2: " + string.Join(" ", l2));

        Console.WriteLine("INTERSECTION: " + string.Join(" ", Intersection(l1, l2)));
    }
}
