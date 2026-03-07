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

        // 1. Selectarea articolelor publicate dupa 2019
        var articlesAfter2019 = articles.Where(a => a.YearOfPublication > 2019).ToList();
        Console.WriteLine("Articole publicate dupa 2019:");
        foreach (var article in articlesAfter2019) Console.WriteLine(article);

        // 2. Gasirea articolului cu cele mai multe pagini
        var mostPagesArticle = articles.OrderByDescending(a => a.NumberOfPages).FirstOrDefault();
        Console.WriteLine("\nArticolul cu cele mai multe pagini:");
        Console.WriteLine(mostPagesArticle);

        // 3. Calcularea mediei paginilor pentru articolele dupa 2020
        var avgPages = articles
            .Where(a => a.YearOfPublication > 2020)
            .Select(a => a.NumberOfPages)
            .DefaultIfEmpty(0)
            .Average();
        Console.WriteLine($"\nMedia paginilor pentru articolele dupa 2020: {avgPages}");

        // 4. Gruparea articolelor dupa anul de publicare
        var groupedByYear = articles.GroupBy(a => a.YearOfPublication).ToList();
        Console.WriteLine("\nArticole grupate dupa anul de publicare:");
        foreach (var group in groupedByYear)
        {
            Console.WriteLine($"\nAnul: {group.Key}, {group.Count()}");
            foreach (var article in group) Console.WriteLine(article);
        }
    }
}
