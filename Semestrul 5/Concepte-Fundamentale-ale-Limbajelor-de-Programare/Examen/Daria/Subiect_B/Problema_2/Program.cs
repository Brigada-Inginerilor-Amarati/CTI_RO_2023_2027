/*
2. Având clasa PC_Game cu următoarele câmpuri: name, producer, release_year, number_of_quests, number_of_opponents, 

scrie cod declarativ LINQ pentru a rezolva următoarele cerințe:
*/

using System;
using System.Collections.Generic;
using System.Linq;

public class PC_Game
{
    public string Name { get; set; }
    public string Producer { get; set; }
    public int ReleaseYear { get; set; }
    public int NumberOfQuests { get; set; }
    public int NumberOfOpponents { get; set; }

    public PC_Game(string name, string producer, int year, int quests, int opponents)
    {
        Name = name;
        Producer = producer;
        ReleaseYear = year;
        NumberOfQuests = quests;
        NumberOfOpponents = opponents;
    }

    public override string ToString()
    {
        return $"Name: {Name}, Producer: {Producer}, Year: {ReleaseYear}, Quests: {NumberOfQuests}, Opponents: {NumberOfOpponents}";
    }
}

public class Program{
    public static void Main(string[] args)
    {
        List<PC_Game> games = new List<PC_Game>
        {
            new PC_Game("The Witcher 3", "CD Projekt Red", 2015, 100, 50),
            new PC_Game("Cyberpunk 2077", "CD Projekt Red", 2020, 50, 100),
            new PC_Game("Skyrim", "Bethesda", 2011, 200, 75),
            new PC_Game("Red Dead Redemption 2", "Rockstar", 2018, 80, 60),
            new PC_Game("GTA V", "Rockstar", 2013, 60, 40)
        };

        /*
        i) Selectează toate obiectele PC_Game unde release_year este mai mic decât 2025.
        */
        var gamesBefore2025 = (from g in games
                                where g.ReleaseYear < 2025
                                select g
                            ).ToList();

        Console.WriteLine("Jocuri lansate inainte de 2025:");
        Console.WriteLine(gamesBefore2025);

        /*
        ii) Găsește obiectul PC_Game cu cea mai mare valoare a câmpului number_of_quests.
        */
        var mostQuestsGame = (
            from g in games
            orderby g.NumberOfQuests descending
            select g
        ).FirstOrDefault();

        Console.WriteLine("\nJocul cu cele mai multe quest-uri:");
        Console.WriteLine(mostQuestsGame);

        /*
        iii) Calculează valoarea medie a câmpului number_of_opponents pentru toate obiectele PC_Game care 
        au number_of_quests mai mare decât 10.
        */
        var avgOpponents = (
            from g in games
            where g.NumberOfQuests > 10
            select g.NumberOfOpponents
        ).Average();

        Console.WriteLine("\nMedia numarului de opponents pentru jocurile cu mai mult de 10 quest-uri:");
        Console.WriteLine(avgOpponents);

        /*
        iv) Grupează obiectele PC_Game după câmpul release_year și afișează câte obiecte sunt în fiecare grup.
        */
        var groupedByYear =
            from g in games
            group g by g.ReleaseYear into grp
            select new{
                Year = grp.Key,
                Count = grp.Count()
            };

        Console.WriteLine("\nJocuri grupate dupa anul de lansare:");

        foreach(var group in groupedByYear)
        {
            Console.WriteLine($"Anul {group.Year} are {group.Count} jocuri.");
        }
    }
}
