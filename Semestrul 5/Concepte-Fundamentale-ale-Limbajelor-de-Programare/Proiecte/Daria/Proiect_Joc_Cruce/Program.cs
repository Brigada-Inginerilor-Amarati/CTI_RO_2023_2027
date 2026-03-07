/*
5. Sa se realizeze un proiect care sa permita simularea unui joc de cruce cu 4 parteneri.

Proiectul NU isi propune sa implementeze un AI care sa participe si sa castige jocul. 

Proiectul isi propune sa asiste cele 6 ture in care fiecare jucator pune cate o carte jos.

Cartile sunt 2,3,4,9,10,11 (as).

Culorile sunt rosu, duba, verde, ghinda.

In total sunt 24 de carti.

Jocul se joaca in perechi de jucatori, deci 4 jucatori formeaza 2 perechi.

Jocul incepe cu o licitatie pe numarul de puncte mari estimate de fiecare jucator.

De regula se pot licita 0,1,2,3,4 puncte mari.

Un punct mare este 33 de puncte mici. 
Acestea se vor calcula la final de joc prin adunarea cartilor castigate de o pereche de jucatori exeptand cartile de 9.

Jucatorul care liciteaza cel mai mult pe baza culorii primei carti puse pe masa va stabili culoarea tromfului pentru partida curenta.

Regulamentul se gaseste la adresa https://tromf.ro/tutorial.htm

Alte informatii si gameplay-ul se poate exersa pe https://www.tromf.ro


*/
using System;
using System.Collections.Generic;
using System.Linq;

enum Culoare
{
    Rosu,
    Duba,
    Verde,
    Ghinda
}

class Carte
{
    public int Numar { get; set; }
    public Culoare Culoare { get; set; }
    
    public Carte(int numar, Culoare culoare)
    {
        Numar = numar;
        Culoare = culoare;
    }
}

class Jucator
{
    public string Nume { get; set; }
    public int Licitatie { get; set; }
    public int EchipaOriginala { get; set; } // 1 pt echipa 1, 2 pt echipa 2
    public List<Carte> Carti { get; set; }

    public Jucator(string nume, int licitatie, int echipaOriginala)
    {
        Nume = nume;
        Licitatie = licitatie;
        Carti = new List<Carte>();
        EchipaOriginala = echipaOriginala;
    }

    public Carte PuneCarte(Jucator jucator)
    {
        int alegere;
        bool validInput;
        do
        {
            Console.WriteLine($"{jucator.Nume}, alege o carte:");
            for (int i = 0; i < jucator.Carti.Count; i++)
            {
                Console.WriteLine($"{i+1}. {jucator.Carti[i].Numar} de {jucator.Carti[i].Culoare}"); //afisez optiunile de carti din mana jucatorului
            }
            string input = Console.ReadLine();
            validInput = int.TryParse(input, out alegere);
            alegere--;
            if(!validInput || alegere < 0 || alegere >= jucator.Carti.Count) //verificam ca alegerea este una valida 
            {
                Console.WriteLine("Alegere invalida! Te rog sa introduci un numar corespunzator listei tale de optiuni!");
            }
        }
        while(!validInput || alegere < 0 || alegere >= jucator.Carti.Count);
        Carte carteAleasa = jucator.Carti[alegere];
        jucator.Carti.RemoveAt(alegere);  // Elimina cartea din mana jucatorului
        return carteAleasa;
    } 

    

}

class Joc
{
    public Culoare StabilireaTromfului(List<Jucator> jucatori, Carte primaCarte)
    {
        int licitatieMaxima = jucatori.Max(j => j.Licitatie);
        Jucator jucatorTromf = jucatori.First(j => j.Licitatie == licitatieMaxima);
        
        // Conform regulilor: "Cand se joaca in 4 clasic, tromful va fi culoarea primei carti jucate (data jos) de castigatorul licitatiei."
        Culoare tromf = primaCarte.Culoare;
        
        Console.WriteLine($"Jucatorul {jucatorTromf.Nume} a stabilit tromful cu licitatia {licitatieMaxima}.");
        Console.WriteLine($"Tromful este {tromf} (culoarea primei carti jucate: {primaCarte.Numar} de {primaCarte.Culoare}).");
        return tromf;
    }

    public int CalculeazaPunctajPereche(List<Carte> carti)
    {
        int TotalEchipa = carti.Where(c => c.Numar != 9).Sum(c => c.Numar); // Exclude cartile de 9
        return TotalEchipa;
    }

    public int PuncteMari(int TotalEchipa)
    {
        return TotalEchipa / 33; // Transforma punctele mici in puncte mari
    }

    public void GestioneazaTureJoc(List<Jucator> jucatori, Culoare tromf, ref int punctajEchipa1, ref int punctajEchipa2, Jucator jucatorCareIncepe, List<Carte> cartiPrimaTura)
    {
        int numarTure = 6; 
        List<Carte> cartiPeMasa = new List<Carte>(); // o lista provizorie valabila pentru fiecare tura a jocului
        int indexJucatorCurent = jucatori.IndexOf(jucatorCareIncepe); 

        for(int tura = 1; tura <= numarTure; tura++)
        {
            Console.WriteLine($"\nTura {tura}:");
            cartiPeMasa.Clear(); //curatam cartile de pe masa dupa fiecare tura
            
            // Pentru prima tura, folosim cartile deja jucate
            if(tura == 1)
            {
                cartiPeMasa.AddRange(cartiPrimaTura);
            }

            int startIndex = (tura == 1) ? 1 : 0; // Prima tura incepe de la al doilea jucator (primul a jucat deja)
            
            for(int i = startIndex; i < jucatori.Count; i++)
            {
                int indexJucator = (indexJucatorCurent + i) % jucatori.Count;
                Jucator jucator = jucatori[indexJucator];
                
                // Determinam culoarea obligatorie (culoarea primei carti sau tromf daca nu are culoarea)
                Culoare? culoareObligatorie = null;
                if(cartiPeMasa.Count > 0)
                {
                    culoareObligatorie = cartiPeMasa.First().Culoare;
                }

                //Verificam anunturile pentru fiecare jucator cand este randul lui
                bool areAnunt40 = VerificaAnunt40(jucator, tromf);
                List<Culoare> anunturi20 = VerificaAnunt20(jucator, tromf);
                
                // if(areAnunt40)
                // {
                //     Console.WriteLine($"\nJucatorul {jucator.Nume} are anunt de tromf (3 si 4 de {tromf}) - 40 puncte!");
                // }
                
                // if(anunturi20.Count > 0)
                // {
                //     foreach (var c in anunturi20)
                //     {
                //         Console.WriteLine($"\nJucatorul {jucator.Nume} are anunt de 20 puncte (3 si 4 de {c})!");
                //     }
                // }
                
                // Validam ca jucatorul joaca o carte valida (culoarea obligatorie sau tromf daca nu are culoarea)
                Carte carteJucata = null;
                bool carteValida = false;
                
                // Verificam ce carti are jucatorul inainte de a juca
                bool areCuloareObligatorie = culoareObligatorie.HasValue && 
                    jucator.Carti.Any(c => c.Culoare == culoareObligatorie.Value);
                bool areTromfi = jucator.Carti.Any(c => c.Culoare == tromf);
                
                do
                {
                    carteJucata = jucator.PuneCarte(jucator);
                    
                    if(culoareObligatorie.HasValue)
                    {
                        // Daca are culoarea obligatorie, trebuie sa joace culoarea
                        if(areCuloareObligatorie && carteJucata.Culoare != culoareObligatorie.Value)
                        {
                            Console.WriteLine($"Eroare! Trebuie sa joci culoarea {culoareObligatorie.Value}!");
                            jucator.Carti.Add(carteJucata); // Returnam cartea
                            carteValida = false;
                        }
                        // Daca nu are culoarea obligatorie, trebuie sa joace tromf
                        else if(!areCuloareObligatorie && carteJucata.Culoare != tromf)
                        {
                            if(areTromfi)
                            {
                                Console.WriteLine($"Eroare! Nu ai culoarea {culoareObligatorie.Value}, trebuie sa joci tromf!");
                                jucator.Carti.Add(carteJucata); // Returnam cartea
                                carteValida = false;
                            }
                            else
                            {
                                // Nu are nici culoarea, nici tromf - poate juca orice
                                carteValida = true;
                            }
                        }
                        else
                        {
                            carteValida = true;
                        }
                    }
                    else
                    {
                        // Prima carte a turei - poate juca orice
                        carteValida = true;
                    }
                }
                while(!carteValida);
                
                cartiPeMasa.Add(carteJucata);
                Console.WriteLine($"{jucator.Nume} a jucat {carteJucata.Numar} de {carteJucata.Culoare}.\n");
                
                // Acordam punctele pentru anunturi daca jucatorul a jucat cartea corecta
                if(areAnunt40 && carteJucata.Culoare == tromf && (carteJucata.Numar == 3 || carteJucata.Numar == 4))
                {
                    Console.WriteLine($"\nAnuntul de tromf este valid! Echipa lui {jucator.Nume} primeste 40 de puncte.");
                    if (jucator.EchipaOriginala == 1)
                    {
                        punctajEchipa1 += 40;
                    }
                    else
                    {
                        punctajEchipa2 += 40;
                    }
                }
                else if(anunturi20.Contains(carteJucata.Culoare) && (carteJucata.Numar == 3 || carteJucata.Numar == 4))
                {
                    Console.WriteLine($"\nAnuntul de 20 puncte este valid! Echipa lui {jucator.Nume} primeste 20 de puncte.");
                    if (jucator.EchipaOriginala == 1)
                    {
                        punctajEchipa1 += 20;
                    }
                    else
                    {
                        punctajEchipa2 += 20;
                    }
                }
            }
            int indexCastigator = DeterminaCastigatorulTurei(cartiPeMasa, jucatori, tromf, indexJucatorCurent);
            int punctajTura = CalculeazaPunctajPereche(cartiPeMasa);

            indexJucatorCurent = indexCastigator;

            // Determinam echipa castigatoare pe baza echipei originale a jucatorului castigator
            Jucator castigator = jucatori[indexCastigator];
            if(castigator.EchipaOriginala == 1)
            {
                punctajEchipa1 = punctajEchipa1 + punctajTura;
                Console.WriteLine($"\nEchipa 1 castiga tura si obtine {punctajTura} puncte. Punctaj total: {punctajEchipa1} puncte.");
            }
            else
            {
                punctajEchipa2 = punctajEchipa2 + punctajTura;
                Console.WriteLine($"\nEchipa 2 castiga tura si obtine {punctajTura} puncte. Punctaj total: {punctajEchipa2} puncte.");

            }
        }
        Console.WriteLine("\nTurele s-au incheiat!");
        Console.WriteLine($"Scor final: Echipa 1 - {punctajEchipa1} puncte, Echipa 2 - {punctajEchipa2} puncte.");

    }

    public void ReordoneazaJucatori(List<Jucator> jucatori, Jucator jucatorCareIncepe)
    {

        // Mutam jucatorul care incepe primul in lista
        int index = jucatori.IndexOf(jucatorCareIncepe);
        if (index > 0)
        {
            List<Jucator> reordonati = jucatori.Skip(index).Concat(jucatori.Take(index)).ToList();
            jucatori.Clear();
            jucatori.AddRange(reordonati);
        }

        List<Jucator> echipa1 = jucatori.Where(j => j.EchipaOriginala == 1).ToList();
        List<Jucator> echipa2 = jucatori.Where(j => j.EchipaOriginala == 2).ToList();
        
        Console.WriteLine("\nEchipa 1 dupa reordonare:");
        foreach (var jucator in echipa1)
        {
            Console.WriteLine(jucator.Nume);
        }
        
        Console.WriteLine("\nEchipa 2 dupa reordonare:");
        foreach (var jucator in echipa2)
        {
            Console.WriteLine(jucator.Nume);
        }
    }


    public int DeterminaCastigatorulTurei(List<Carte> cartiPeMasa, List<Jucator> jucatori, Culoare tromf, int indexJucatorCurent)
    {
        Carte carteCastigatoare = null;
        int indexCastigator = -1;
        Culoare culoarePrimaCarte = cartiPeMasa.First().Culoare; //retinem culoarea primei carti

        var cartiDeTromf = cartiPeMasa.Where(c => c.Culoare == tromf).ToList();
        if(cartiDeTromf.Any())
        {
            //daca avem vreo carte de tromf, sau mai multe, se alege prima din lista
            carteCastigatoare = cartiDeTromf.OrderByDescending(c => c.Numar).First(); //ordonam lista descrescator pentru a extrage tromful cel mai mare
        }
        else //daca nu avem carti de tromf, alegem cartea de culoare cea mai mare
        {
            var cartiDeCuloare = cartiPeMasa.Where(c => c.Culoare == culoarePrimaCarte).ToList();
            if(cartiDeCuloare.Any()) //verificare daca exista macar o carte de culoare (fie mai multe, fie doar prima care a fost data)
            {
                carteCastigatoare = cartiDeCuloare.OrderByDescending(c => c.Numar).First(); //se alege prima carte de culoare 
            }
        }
        int indexInListaCarti = cartiPeMasa.IndexOf(carteCastigatoare); //indexul in lista de carti
        // Calculam indexul jucatorului castigator in lista de jucatori
        indexCastigator = (indexJucatorCurent + indexInListaCarti) % jucatori.Count;
        Jucator castigator = jucatori[indexCastigator]; 
        Console.WriteLine($"\nCastigatorul turei este {castigator.Nume} cu {carteCastigatoare.Numar} de {carteCastigatoare.Culoare}.");
        return indexCastigator;
    }

    public bool VerificaAnunt40(Jucator jucator, Culoare tromf)
    {
        bool areTreiTromf = jucator.Carti.Any(c => c.Numar == 3 && c.Culoare == tromf);
        bool arePatruTromf = jucator.Carti.Any(c => c.Numar == 4 && c.Culoare == tromf);

        return areTreiTromf && arePatruTromf;
    }

    //functie pentru verificarea unui anunt de 20 de puncte, adica NU anunt de tromf
    // Trebuie sa aiba 3 si 4 de aceeasi culoare (diferita de tromf)
    // Returneaza culoarea anuntului sau null daca nu exista
    // Verificam toate anunturile posibile de 20 (pentru toate culorile care nu sunt tromf)
    public List<Culoare> VerificaAnunt20(Jucator jucator, Culoare tromf)
    {
        List<Culoare> anunturi = new List<Culoare>();
        // Verificam daca jucatorul are 3 si 4 de aceeasi culoare (diferita de tromf)
        foreach (Culoare culoare in Enum.GetValues(typeof(Culoare)))
        {
            if (culoare != tromf)
            {
                bool areTreiCarte = jucator.Carti.Any(c => c.Numar == 3 && c.Culoare == culoare);
                bool arePatruCarte = jucator.Carti.Any(c => c.Numar == 4 && c.Culoare == culoare);
                
                if (areTreiCarte && arePatruCarte)
                {
                    anunturi.Add(culoare);
                }
            }
        }
        return anunturi;
    }

    public void AmestecaSiDistribuieCarti(List<Carte> pachetCarti, List<Jucator> jucatori)
    {
        Random random = new Random(); //generator de nr aleatoare

        // Amestecam pachetul de carti - folosim Shuffle pentru a modifica lista originala
        for (int i = pachetCarti.Count - 1; i > 0; i--)
        {
            int j = random.Next(i + 1);
            Carte temp = pachetCarti[i];
            pachetCarti[i] = pachetCarti[j];
            pachetCarti[j] = temp;
        }

        int cartiPerJucator = 6;
        for (int i = 0; i < jucatori.Count; i++)
        {
            jucatori[i].Carti = pachetCarti.Skip(i * cartiPerJucator).Take(cartiPerJucator).ToList();
        }

        Console.WriteLine("\nCartile au fost amestecate si distribuite.");
        //afisam cartile fiecarui jucator
        foreach (var jucator in jucatori)
        {
            Console.WriteLine($"\n{jucator.Nume} a primit:");
            foreach (var carte in jucator.Carti)
            {
                Console.WriteLine($" - {carte.Numar} de {carte.Culoare}");
            }
        }
    }

}

class Program
{
    public static List<Tuple<Jucator, Jucator>> FormeazaPerechi(List<Jucator> jucatori)
    {
        var perechi = new List<Tuple<Jucator, Jucator>>();

        var echipa1 = new Tuple<Jucator, Jucator>(jucatori[0], jucatori[2]);
        var echipa2 = new Tuple<Jucator, Jucator>(jucatori[1], jucatori[3]);

        perechi.Add(echipa1); 
        perechi.Add(echipa2);

        Console.WriteLine("\nEchipele formate sunt:");
        Console.WriteLine($"Echipa 1: {echipa1.Item1.Nume} si {echipa1.Item2.Nume}");
        Console.WriteLine($"Echipa 2: {echipa2.Item1.Nume} si {echipa2.Item2.Nume}");

        return perechi;
    }
    
    public static void Main(string[] args)
    {
        List<Carte> pachetCarti = new List<Carte>();
        
        Carte doiRosu = new Carte(2, Culoare.Rosu);
        Carte treiRosu = new Carte(3, Culoare.Rosu);
        Carte patruRosu = new Carte(4, Culoare.Rosu);
        Carte nouaRosu = new Carte(9, Culoare.Rosu);
        Carte zeceRosu = new Carte(10, Culoare.Rosu);
        Carte unsprezeceRosu = new Carte(11, Culoare.Rosu);

        Carte doiVerde = new Carte(2, Culoare.Verde);
        Carte treiVerde = new Carte(3, Culoare.Verde);
        Carte patruVerde = new Carte(4, Culoare.Verde);
        Carte nouaVerde = new Carte(9, Culoare.Verde);
        Carte zeceVerde = new Carte(10, Culoare.Verde);
        Carte unsprezeceVerde = new Carte(11, Culoare.Verde);

        Carte doiDuba = new Carte(2, Culoare.Duba);
        Carte treiDuba = new Carte(3, Culoare.Duba);
        Carte patruDuba = new Carte(4, Culoare.Duba);
        Carte nouaDuba = new Carte(9, Culoare.Duba);
        Carte zeceDuba = new Carte(10, Culoare.Duba);
        Carte unsprezeceDuba = new Carte(11, Culoare.Duba);

        Carte doiGhinda = new Carte(2, Culoare.Ghinda);
        Carte treiGhinda = new Carte(3, Culoare.Ghinda);
        Carte patruGhinda = new Carte(4, Culoare.Ghinda);
        Carte nouaGhinda = new Carte(9, Culoare.Ghinda);
        Carte zeceGhinda = new Carte(10, Culoare.Ghinda);
        Carte unsprezeceGhinda = new Carte(11, Culoare.Ghinda);

        pachetCarti.Add(doiRosu);
        pachetCarti.Add(treiRosu);
        pachetCarti.Add(patruRosu);
        pachetCarti.Add(nouaRosu);
        pachetCarti.Add(zeceRosu);
        pachetCarti.Add(unsprezeceRosu);

        pachetCarti.Add(doiVerde);
        pachetCarti.Add(treiVerde);
        pachetCarti.Add(patruVerde);
        pachetCarti.Add(nouaVerde);
        pachetCarti.Add(zeceVerde);
        pachetCarti.Add(unsprezeceVerde);

        pachetCarti.Add(doiDuba);
        pachetCarti.Add(treiDuba);
        pachetCarti.Add(patruDuba);
        pachetCarti.Add(nouaDuba);
        pachetCarti.Add(zeceDuba);
        pachetCarti.Add(unsprezeceDuba);

        pachetCarti.Add(doiGhinda);
        pachetCarti.Add(treiGhinda);
        pachetCarti.Add(patruGhinda);
        pachetCarti.Add(nouaGhinda);
        pachetCarti.Add(zeceGhinda);
        pachetCarti.Add(unsprezeceGhinda);


        List<Jucator> jucatori = new List<Jucator>();

        for (int i = 1; i <= 4; i++)
        {
            Console.WriteLine($"Introdu numele jucatorului {i}: ");
            string nume = Console.ReadLine();
            if(i % 2 == 0)
            {
                jucatori.Add(new Jucator(nume, 0, 2)); // Initial, am setat licitatia la 0
            }
            else
            {
                jucatori.Add(new Jucator(nume, 0, 1)); // Initial, am setat licitatia la 0
            }
        }

        // Formam echipele dupa ce am colectat toti jucatorii
        List<Tuple<Jucator, Jucator>> echipe = FormeazaPerechi(jucatori);

        var echipa1 = echipe[0];
        var echipa2 = echipe[1];

        int scorEchipa1 = 0;
        int scorEchipa2 = 0;

        Console.WriteLine($"Membrii Echipa 1: {echipa1.Item1.Nume}, {echipa1.Item2.Nume}");
        Console.WriteLine($"Membrii Echipa 2: {echipa2.Item1.Nume}, {echipa2.Item2.Nume}");

        //Distribuim cartile pentru fiecare jucator
        Joc joc = new Joc();
        joc.AmestecaSiDistribuieCarti(pachetCarti, jucatori);

        // Licitatia - fiecare jucator din fiecare echipa liciteaza punctele
        int licitatieAnterioara = 0;

        foreach (var jucator in jucatori)
        {
            int licitatie = 0;
            while (true)
            {
                Console.WriteLine($"\nIntrodu punctele de licitatie pentru {jucator.Nume} (mai mari decat {licitatieAnterioara} sau 0 pentru a trece, maxim 4): ");
                if (int.TryParse(Console.ReadLine(), out licitatie) && (licitatie == 0 || licitatie > licitatieAnterioara && licitatie <= 4))
                {
                    break;
                }
                Console.WriteLine($"Valoare invalida! Introdu un numar intre 0 si 4, mai mare decat {licitatieAnterioara} sau 0 pentru a trece!");
            }

            if(licitatie > 0)
            {
                licitatieAnterioara = licitatie; // Actualizam doar daca nu este 0
            }
            jucator.Licitatie = licitatie; // Actualizam licitatia jucatorului
        }

        // Verificam daca toti jucatorii au ales 0
        if (jucatori.All(j => j.Licitatie == 0))
        {
            Console.WriteLine("\nToti jucatorii au ales bune. Jocul va incepe cu primul jucator care a ales.");
            Jucator primulJucator = jucatori.First();
            Console.WriteLine($"\nPrimul jucator care incepe este {primulJucator.Nume}.");
        }
        else
        {
            Console.WriteLine("\nLicitatia a fost realizata. Jocul poate incepe!");
            Jucator primulJucator = jucatori.First(l => l.Licitatie == licitatieAnterioara);
            Console.WriteLine($"\nPrimul jucator care incepe este {primulJucator.Nume}.");

            joc.ReordoneazaJucatori(jucatori, primulJucator); //pentru a incepe cel cu licitatia cea mai mare
        }

        int punctajEchipa1 = 0;
        int punctajEchipa2 = 0;
        
        // Castigatorul licitatiei joaca prima carte, iar tromful este culoarea acestei carti
        Jucator jucatorTromf = jucatori.First(j => j.Licitatie == jucatori.Max(j2 => j2.Licitatie));
        Console.WriteLine($"\n{jucatorTromf.Nume} (castigatorul licitatiei) joaca prima carte:");
        Carte primaCarte = jucatorTromf.PuneCarte(jucatorTromf);
        Console.WriteLine($"{jucatorTromf.Nume} a jucat {primaCarte.Numar} de {primaCarte.Culoare}.\n");
        
        Culoare tromf = joc.StabilireaTromfului(jucatori, primaCarte);
        Console.WriteLine($"Jocul incepe cu tromful {tromf}!");

        // Verificam daca primul jucator a facut un anunt valid cu prima carte (40 de puncte, deoarece a stabilit tromful)
        if (primaCarte.Numar == 3 || primaCarte.Numar == 4) 
        {
             int partenerNecesar = (primaCarte.Numar == 3) ? 4 : 3;
             bool arePartener = jucatorTromf.Carti.Any(c => c.Numar == partenerNecesar && c.Culoare == tromf);
             if (arePartener)
             {
                 Console.WriteLine($"\nJucatorul {jucatorTromf.Nume} a deschis cu anunt de 40 puncte (are 3 si 4 de tromf)!");
                 if (jucatorTromf.EchipaOriginala == 1) punctajEchipa1 += 40;
                 else punctajEchipa2 += 40;
             }
        }

        // Adaugam prima carte la lista de carti pentru prima tura
        List<Carte> cartiPrimaTura = new List<Carte> { primaCarte };
        
        joc.GestioneazaTureJoc(jucatori, tromf, ref punctajEchipa1, ref punctajEchipa2, jucatorTromf, cartiPrimaTura);

        int licitatieMaxima = jucatori.Max(j => j.Licitatie);
        Jucator jucatorCuLicitatieMaxima = jucatori.First(j => j.Licitatie == licitatieMaxima);

        int puncteMariEchipa1 = punctajEchipa1 / 33;
        int puncteMariEchipa2 = punctajEchipa2 / 33;

        // Calculam scorul final pentru fiecare echipa
        if(jucatorCuLicitatieMaxima.EchipaOriginala == 1)
        {
            if(puncteMariEchipa1 < licitatieMaxima)
            {
                Console.WriteLine($"\nEchipa 1 nu a realizat licitatia de {licitatieMaxima} puncte mari. Penalizare: -{licitatieMaxima} puncte mari (numarul de puncte licitate).");
                scorEchipa1 = -licitatieMaxima; // Penalizare cu numarul de puncte licitate
            }
            else
            {
                scorEchipa1 = puncteMariEchipa1;
                Console.WriteLine($"\nEchipa 1 a realizat licitatia de {licitatieMaxima} puncte mari.\nScor final: {scorEchipa1} puncte mari.");
            }
            // Echipa adversa primeste punctele mari castigate
            scorEchipa2 = puncteMariEchipa2;
        }
        else if(jucatorCuLicitatieMaxima.EchipaOriginala == 2)
        {
            if(puncteMariEchipa2 < licitatieMaxima)
            {
                Console.WriteLine($"\nEchipa 2 nu a realizat licitatia de {licitatieMaxima} puncte mari. Penalizare: -{licitatieMaxima} puncte mari (numarul de puncte licitate).");
                scorEchipa2 = -licitatieMaxima; // Penalizare cu numarul de puncte licitate
            }
            else
            {
                scorEchipa2 = puncteMariEchipa2;
                Console.WriteLine($"\nEchipa 2 a realizat licitatia de {licitatieMaxima} puncte mari.\nScor final: {scorEchipa2} puncte mari.");
            }
            // Echipa adversa primeste punctele mari castigate
            scorEchipa1 = puncteMariEchipa1;
        }

        Console.WriteLine($"\nScor final (puncte mari):\nEchipa 1: {scorEchipa1} puncte mari\nEchipa 2: {scorEchipa2} puncte mari");

        
    }
}

