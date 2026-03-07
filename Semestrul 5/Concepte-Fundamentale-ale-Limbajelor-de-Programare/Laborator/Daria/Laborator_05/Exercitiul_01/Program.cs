/*
1. Implementați o metodă statică RemoveAt, care primește un array, 

lungimea array-ului și un index. Metoda elimină elementul de la indexul dat din array.

public static void RemoveAt(int[] array, ref int length, int n)
*/

class Program{
    public static void RemoveAt(int[] array, ref int length, int index){
        for(int i = index; i < length - 1; i++){
            array[i] = array[i + 1];
        }
        length--;
    }

    public static void Main(string[] args){
        int[] array = new int[10];
        Random random = new Random();

        for(int i = 0; i < array.Length; i++){
            array[i] = random.Next(1, 100);
        }

        Console.WriteLine("Array before removal: \n" + string.Join(", ", array));

        Console.WriteLine("\nEnter the index of the element to remove: ");
        string? input = Console.ReadLine();
        if(input == null){
            Console.WriteLine("Invalid input");
            return;
        }
        int index = int.Parse(input);
        int length = array.Length;
        if(index < 0 || index >= length){
            Console.WriteLine("Invalid index");
            return;
        }
        RemoveAt(array, ref length, index);

        Console.WriteLine("Array after removal: \n" + string.Join(", ", array));
    }
}