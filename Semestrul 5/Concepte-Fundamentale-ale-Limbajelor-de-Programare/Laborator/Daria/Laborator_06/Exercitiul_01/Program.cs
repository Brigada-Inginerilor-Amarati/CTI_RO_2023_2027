/*

1. Implementați o funcție numită Filtru, care primește o funcție booleană 

ca delegat și o listă și returnează o listă nouă care conține elementele care îndeplinesc condiția.

public static List<int> Filtru(MyDelegate condiție, List<int> listă)

*/

namespace Exercitiul_01{
    delegate bool MyDelegate(int x);

    class Program{
        public static List<int> Filtru(MyDelegate condition, List<int> list){
            List<int> filtered = new List<int>();
            foreach(var item in list){
                if(condition(item)){
                    filtered.Add(item);
                }
            }
            return filtered;
        }

        public static bool isUneven(int x){
            return x % 2 != 0;
        }

        public static void Main(string[] args){
            List<int> list = new List<int>(){1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

            List<int> filtered = Filtru(isUneven, list);
            
            Console.WriteLine(string.Join(", ", filtered));
        }
    }
}