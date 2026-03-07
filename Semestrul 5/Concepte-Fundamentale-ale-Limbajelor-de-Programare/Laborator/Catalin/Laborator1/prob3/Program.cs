using System;

class Student
{
    private string name;
    private int year;
    private  double grade1;
    private  double grade2;
    private  double grade3;

    public Student(string name, int year, double grade1, double grade2, double grade3)
    {
        this.name = name;
        this.year = year;
        this.grade1 = grade1;
        this.grade2 = grade2;
        this.grade3 = grade3;
    }

    public double Media
    {
       get{ return (grade1 + grade2 + grade3) / 3.0; }
    }

    public string ToString()
    {
         return $"mume: {name}, an: {year}, note: {grade1}, {grade2}, {grade3}, media: {Media:F2}";
    }
}

public class Exercise3
{
    static void Main()
    {
        Console.Write("nr studenti: ");
        int n = int.Parse(Console.ReadLine());

        Student[] studenti = new Student[n];

        for (int i = 0; i < n; i++)
        {
            Console.WriteLine($"studentul #{i + 1}:");
            Console.Write("nume: ");
            string name = Console.ReadLine();
            Console.Write("an: ");
            int year = int.Parse(Console.ReadLine());
            Console.Write("nota 1: ");
            double g1 = double.Parse(Console.ReadLine());
            Console.Write("nota 2: ");
            double g2 = double.Parse(Console.ReadLine());
            Console.Write("nota 3: ");
            double g3 = double.Parse(Console.ReadLine());
            studenti[i] = new Student(name, year, g1, g2, g3);
        }

        Student best = studenti[0];
        for (int i = 1; i < n; i++)
            if (studenti[i].Media > best.Media)
                best = studenti[i];

        Console.WriteLine("cea mai mare nota:");
        Console.WriteLine(best.ToString());
    }
}




