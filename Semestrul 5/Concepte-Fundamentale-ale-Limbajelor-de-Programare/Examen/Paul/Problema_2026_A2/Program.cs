/*
2. Având clasa ScientificArticle cu următoarele câmpuri: title, author, year_of_publication, number_of_pages, impact_factor, scrie interogări declarative LINQ pentru a rezolva următoarele cerințe:
*/

using System.Collections;

record ScientificArticle(
    string Title,
    string Author,
    int YearOfPublication,
    int NumberOfPages,
    int ImpactFactor
);

class ScientificRepository
{
    private List<ScientificArticle> Articles { get; } = new List<ScientificArticle>();

    public void Add(ScientificArticle article)
    {
        Articles.Add(article);
    }

    /*
    i) Selectează toate obiectele ScientificArticle unde year_of_publication este mai mare decât 2019.
    */
    public List<ScientificArticle> SelectArticlesReleasedAfter2019()
    {
        var articles = from a in Articles where a.YearOfPublication > 2019 select a;
        return articles.ToList();
    }

    /*
    ii) Găsește obiectul ScientificArticle cu cea mai mare valoare a number_of_pages.
    */
    public List<ScientificArticle> SelectHighestPageCountArticle()
    {
        var articles =
            from a in Articles
            where a.NumberOfPages == Articles.Max(ar => ar.NumberOfPages)
            select a;
        return articles.ToList();
    }

    /*
    iii) Calculează valoarea medie a number_of_pages pentru toate obiectele ScientificArticle unde year_of_publication este mai mare decât 2020.
    */
    public double SelectAveragePageCountForArticlesReleasedAfter2020()
    {
        var pages = from a in Articles where a.YearOfPublication > 2020 select a.NumberOfPages;
        return pages.Average();
    }

    /*
    iv) Grupează obiectele ScientificArticle după an și afișează câte obiecte sunt în fiecare grup.
    */
    public void PrintGroupArticlesByReleaseYear()
    {
        var articles = from a in Articles group a by a.YearOfPublication into g select g.ToList();

        foreach (var group in articles)
        {
            Console.WriteLine("Year: " + group[0].YearOfPublication);
            Console.WriteLine("Count: " + group.Count);
        }
    }
}

class MainClass
{
    static void Main(string[] args)
    {
        var art1 = new ScientificArticle("Title1", "Author1", 2018, 100, 5);
        var art2 = new ScientificArticle("Title2", "Author2", 2022, 200, 10);
        var art3 = new ScientificArticle("Title3", "Author3", 2023, 300, 15);

        var repo = new ScientificRepository();
        repo.Add(art1);
        repo.Add(art2);
        repo.Add(art3);

        var a = repo.SelectArticlesReleasedAfter2019();
        Console.WriteLine("Articles after 2019: " + a.Count);
        var b = repo.SelectHighestPageCountArticle();
        Console.WriteLine("Articles with highest page count: " + b.Count);
        var c = repo.SelectAveragePageCountForArticlesReleasedAfter2020();
        Console.WriteLine("Average page count for articles released after 2020: " + c);

        repo.PrintGroupArticlesByReleaseYear();
    }
}
