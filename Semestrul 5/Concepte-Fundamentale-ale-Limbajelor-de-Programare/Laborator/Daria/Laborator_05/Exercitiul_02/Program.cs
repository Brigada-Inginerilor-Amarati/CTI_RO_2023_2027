/*
2. Implementați o metodă statică care primește două liste de tip List<int> 

și returnează o List<int> care conține elementele prezente în ambele liste. 

Asigurați-vă că lista rezultată nu are duplicate.

public static List Intersection(List l1, List l2)
*/

class Program{
    public static List<int> Intersection(List<int> list1, List<int> list2){
        List<int> intersection = new List<int>();

        foreach(int item in list1){
            if(list2.Contains(item)){
                intersection.Add(item);
            }
        }

        return intersection;
    }

    public static void Main(string[] args){
        List<int> list1 = new List<int> { 1, 2, 3, 4, 5 };
        List<int> list2 = new List<int> { 3, 4, 5, 6, 7 };
        
        Console.WriteLine(string.Join(" ", Intersection(list1, list2)));
    }
}