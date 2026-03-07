/*
1. Implementați o metodă statică, care primește doi întregi ca parametri ref și îi interschimbă.
*/

using System;

class Program{
    public static void Swap(ref int a, ref int b){
        int temp = a;
        a = b;
        b = temp;
    }
    
    public static void Main(string[] args){
        int a = 13;
        int b = 31;

        Console.WriteLine($"a = {a}, b = {b}");
        Swap(ref a, ref b);
        Console.WriteLine($"a = {a}, b = {b}");
    }
}