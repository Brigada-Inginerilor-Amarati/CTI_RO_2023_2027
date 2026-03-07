/* 
2. Având clasa ScientificArticle cu următoarele câmpuri: 

title, author, year_of_publication, number_of_pages, impact_factor, 

scrie interogări declarative LINQ pentru a rezolva următoarele cerințe:
*/
using System;
using System.Collections.Generic;
using System.Linq;

public class ScientificArticle
{
    public string Title { get; set; }
    public string Author { get; set; }
    public int YearOfPublication { get; set; }
    public int NumberOfPages { get; set; }
    public double ImpactFactor { get; set; }

    public ScientificArticle(string title, string author, int year, int pages, double impactFactor)
    {
        Title = title;
        Author = author;
        YearOfPublication = year;
        NumberOfPages = pages;
        ImpactFactor = impactFactor;
    }

    public override string ToString()
    {
        return $"Title: {Title}, Author: {Author}, Year: {YearOfPublication}, Pages: {NumberOfPages}, Impact Factor: {ImpactFactor}";
    }
}

public class Program
{
    public static void Main(string[] args)
    {
        List<ScientificArticle> articles = new List<ScientificArticle>
        {
            new ScientificArticle("AI Research", "John Doe", 2021, 50, 3.5),
            new ScientificArticle("Quantum Computing", "Alice Smith", 2020, 40, 4.0),
            new ScientificArticle("Climate Change", "Bob Brown", 2019, 35, 2.8),
            new ScientificArticle("Cybersecurity Trends", "Charlie Lee", 2022, 60, 3.9),
            new ScientificArticle("Deep Learning", "Eva Green", 2023, 55, 4.5)
        };

        /*
        i) Selectează toate obiectele ScientificArticle unde year_of_publication este mai mare decât 2019.
        */
        var articlesAfter2019  = from a in articles
                                where a.YearOfPublication > 2019
                                select a;

        Console.WriteLine("Articole publicate dupa 2019:");
        foreach (var article in articlesAfter2019) Console.WriteLine(article);

        /*
        ii) Găsește obiectul ScientificArticle cu cea mai mare valoare a câmpului number_of_pages.
        */
        var mostPagesArticle = from a in articles
                                orderby a.NumberOfPages descending
                                select a;

        Console.WriteLine("\nArticolul cu cele mai multe pagini:");
        Console.WriteLine(mostPagesArticle.FirstOrDefault());

        /*
        iii) Calculează valoarea medie a câmpului number_of_pages pentru toate obiectele 
        
        ScientificArticle care au year_of_publication mai mare decât 2020.
        */
        var avgPages = from a in articles
                        where a.YearOfPublication > 2020
                        select a.NumberOfPages;

        Console.WriteLine("\nMedia paginilor pentru articolele dupa 2020:");
        Console.WriteLine(avgPages.Average());
        /*
        iv) Grupează obiectele ScientificArticle după câmpul year_of_publication și 
        afișează câte obiecte sunt în fiecare grup.
        */
        var groupedByYear = from a in articles
                            group a by a.YearOfPublication into g
                            select new {
                                Year = g.Key,
                                Count = g.Count()
                            };

        Console.WriteLine("\nArticole grupate dupa anul de publicare:");
        foreach (var group in groupedByYear)
        {
            Console.WriteLine($"\nAnul: {group.Year}, {group.Count}");
        }
    }
}
