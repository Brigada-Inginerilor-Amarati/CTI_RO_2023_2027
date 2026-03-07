/*
3. Implementați o clasă Cont, care are proprietățile nume și sold (inițializate de constructor), 

și o metodă Retragere care permite retragerea de fonduri. 

Metoda primește un parametru care specifică suma retrasă și un parametru out în care returnează 

soldul rămas. Dacă suma completă poate fi retrasă, metoda returnează true. 

Dacă suma nu poate fi retrasă, metoda returnează false. Metoda va avea următoarea semnătură:

public bool Retragere(double suma, out double soldRamas)
*/

using System;

namespace Exercitiu_03{
    class Cont{
        public string Nume {get; set;}
        public double Sold {get; private set;}

        public Cont(string nume, double sold){
            Nume = nume;
            Sold = sold;
        }

        public bool Retragere(double suma, out double soldRamas){
            if(suma > Sold){
                soldRamas = Sold;
                return false;
            }
            else{
                Sold = Sold - suma;
                soldRamas = Sold;
                return true;
            }
        }
    }

    class Program{
        public static void Main(string[] args){
            Cont cont1 = new Cont("Daria", 3100);

            bool result = cont1.Retragere(1800, out double soldRamas);
            Console.WriteLine($"Result: {result}");
            Console.WriteLine($"Sold ramas: {soldRamas}");
        }
    }
}