// 1. Scrieti un program care citeste n numere si afiseaza suma acestora

using System;

    class Exercitiu_01_Daria{
        static void Main(string[] args){
            Console.WriteLine("Introduceti numarul de numere: ");
            
            int n = 0;

            try{
                n = int.Parse(Console.ReadLine());
            }
            catch(Exception e){
                Console.WriteLine("Eroare: " + e.Message);
            }

            int[] numere = new int[n];

            for(int i = 0; i < n; i++){
                Console.WriteLine("Introduceti numarul " + (i + 1) + ": ");
                numere[i] = int.Parse(Console.ReadLine());
            }
            
            int suma = 0;

            for(int i = 0; i < n; i++){
                suma += numere[i];
            }

            Console.WriteLine("Suma numerelor este: " + suma);
        }
    }