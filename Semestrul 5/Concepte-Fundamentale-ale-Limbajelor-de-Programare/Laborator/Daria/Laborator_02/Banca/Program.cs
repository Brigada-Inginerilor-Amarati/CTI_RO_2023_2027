/*
Scrieți un program care gestionează conturile unei bănci. O bancă are următoarea structură:
Banca:

    Nume
    Swift
    List<Cont>

Un cont folosește următoarea structură:
Cont:

    Titular de cont
    Tip de cont (persoană / companie)
    Iban
    Suma

Notă: TipCont va fi un tip enum declarat. Toate proprietățile ar trebui să fie publice, doar cu citire. Următoarele operațiuni sunt disponibile pentru un cont:

    Depunere de bani
    Retragere de bani
    Afișare detalii cont (ToString)

Următoarele operațiuni sunt disponibile pentru o bancă:

    Deschidere de cont nou
    Găsirea unui cont după iban și afișarea detaliilor sale
    Depunere de bani într-un cont
    Retragere de bani dintr-un cont
    Transfer de bani între două conturi

Sfat: Puteți defini o metodă privată suplimentară GetAccount(string iban) pentru a găsi un cont cu un anumit iban.
*/
using System;
using System.Collections.Generic;

namespace Banca{
    // enum pentru tipul de cont
    public enum TipCont{
        Persoana,
        Companie
    }

    // clasa cont
    public class Cont{
        public string NumeTitular { get; }
        public TipCont TipCont { get; }
        public String Iban { get; }
        public double Suma { get; private set; }

        public Cont(string numeTitular, TipCont tipCont, string iban, double suma){
            NumeTitular = numeTitular;
            TipCont = tipCont;
            Iban = iban;
            Suma = suma;
        }

        public void depunereDeBani(double suma){
            if(suma < 0){
                Console.WriteLine("Suma nu poate fi negativa");
                return;
            }

            Suma += suma;
            Console.WriteLine($"Suma de {suma} a fost depusa in cont");
        }

        public void retragereDeBani(double sumaRetrasa){
            if(sumaRetrasa < 0){
                Console.WriteLine("Suma nu poate fi negativa");
                return;
            }
            else if(sumaRetrasa > Suma){
                Console.WriteLine("Suma retrasa este mai mare decat suma disponibila in cont");
                return;
            }

            Suma -= sumaRetrasa;
            Console.WriteLine($"Suma de {sumaRetrasa} a fost retrasa din cont");
        }

        public override string ToString(){
            return $"Nume titular: {NumeTitular}, Tip cont: {TipCont}, Iban: {Iban}, Suma: {Suma}";
        }

    }

    // clasa banca
    public class Banca{
        public string Nume { get; }
        public string Swift { get; }
        public List<Cont> Conturi { get; }

        public Banca(string nume, string swift, List<Cont> conturi){
            Nume = nume;
            Swift = swift;
            Conturi = conturi;
        }

        public void deschidereDeCont(string numeTitular, TipCont tipCont, string iban, double suma){
            Conturi.Add(new Cont(numeTitular, tipCont, iban, suma));
            Console.WriteLine($"Contul a fost deschis cu succes");
        }

        private Cont getAccount(string iban){
            foreach(Cont cont in Conturi){
                if(cont.Iban == iban){
                    return cont;
                }
            }
            return null;
        }

        public void afisareDetaliiCont(string iban){
            Cont cont = getAccount(iban);
            if(cont != null){
                Console.WriteLine(cont);
            }
            else{
                Console.WriteLine("Contul nu a fost gasit");
            }
        }   

        public void depunereDeBaniInCont(string iban, double suma){
            var cont = getAccount(iban);

            if(cont != null){
                cont.depunereDeBani(suma);
            }
            else{
                Console.WriteLine("Contul nu a fost gasit");
            }
        }

        public void retragereDeBaniDinCont(string iban, double suma){
            var cont = getAccount(iban);

            if(cont != null){
                cont.retragereDeBani(suma);
            }
            else{
                Console.WriteLine("Contul nu a fost gasit");
            }
        }

        public void transferDeBaniIntreConturi(string ibanExtragere, string ibanDepunere, double suma){
            var contExtragere = getAccount(ibanExtragere);
            var contDepunere = getAccount(ibanDepunere);

            if(contExtragere != null && contDepunere != null){
                contExtragere.retragereDeBani(suma);
                contDepunere.depunereDeBani(suma);
            }
            else{
                Console.WriteLine("Conturile nu au fost gasite");
            }
        }
    }

    // clasa program
    public class Program{
        public static void Main(string[] args){
           Banca banca = new Banca("Banca", "BT", new List<Cont>());

           Cont cont1 = new Cont("Daria", TipCont.Persoana, "RO1234567890", 1000);
           Cont cont2 =  new Cont("Anisia", TipCont.Persoana, "RO1234567891", 2000);

           banca.deschidereDeCont(cont1.NumeTitular, cont1.TipCont, cont1.Iban, cont1.Suma);
           banca.deschidereDeCont(cont2.NumeTitular, cont2.TipCont, cont2.Iban, cont2.Suma);

           banca.afisareDetaliiCont(cont1.Iban);
           banca.afisareDetaliiCont(cont2.Iban);

           banca.depunereDeBaniInCont(cont1.Iban, 500);
           banca.retragereDeBaniDinCont(cont2.Iban, 1000);
           banca.afisareDetaliiCont(cont1.Iban);
           banca.afisareDetaliiCont(cont2.Iban);

           banca.transferDeBaniIntreConturi(cont1.Iban, cont2.Iban, 300);
           banca.afisareDetaliiCont(cont1.Iban);
           banca.afisareDetaliiCont(cont2.Iban);
        }
    }
}