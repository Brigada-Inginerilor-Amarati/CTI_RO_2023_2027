using System;
using System.Collections.Generic;
using ClosedXML.Excel;

public static class TestDataGenerator
{
    private static readonly Random random = new Random();

    private static readonly string[] publicationTitles = new[]
    {
        "Advanced Machine Learning Techniques for Data Analysis",
        "Quantum Computing Applications in Cryptography",
        "Neural Networks Optimization Algorithms",
        "Blockchain Technology in Financial Systems",
        "Deep Learning for Image Recognition",
        "Cloud Computing Security Challenges",
        "Artificial Intelligence in Healthcare",
        "Distributed Systems Architecture Patterns",
        "Natural Language Processing Methods",
        "Cybersecurity Threats and Countermeasures",
        "Big Data Analytics Frameworks",
        "Internet of Things Security Protocols",
        "Software Engineering Best Practices",
        "Database Optimization Techniques",
        "Mobile Application Development Trends",
    };

    private static readonly string[] publicationTypes = new[]
    {
        "Articol",
        "Carte",
        "Capitol",
        "Conferinta",
        "Revista",
    };

    public static void GenerateTestFiles()
    {
        GenerateFile("raport_paul.xlsx", "Paul", 7);
        GenerateFile("raport_dan.xlsx", "Dan", 6);
        GenerateFile("raport_robert.xlsx", "Robert", 8);

        Console.WriteLine("Data files generated successfully!");
    }

    private static void GenerateFile(string fileName, string researcherName, int publicationCount)
    {
        var workbook = new XLWorkbook();
        var worksheet = workbook.Worksheets.Add("Publicatii");

        // Header row
        worksheet.Cell(1, 1).Value = "Titlu";
        worksheet.Cell(1, 2).Value = "Cod DOI";
        worksheet.Cell(1, 3).Value = "Cod WOS";
        worksheet.Cell(1, 4).Value = "Cod ISBN";
        worksheet.Cell(1, 5).Value = "Autor Fișier";
        worksheet.Cell(1, 6).Value = "ISI Roșu";
        worksheet.Cell(1, 7).Value = "ISI Galben";
        worksheet.Cell(1, 8).Value = "An Publicare";
        worksheet.Cell(1, 9).Value = "Tip Publicație";

        // Style header row
        var headerRange = worksheet.Range(1, 1, 1, 9);
        headerRange.Style.Font.Bold = true;
        headerRange.Style.Fill.BackgroundColor = XLColor.LightGray;

        // Generate publication data
        for (var i = 0; i < publicationCount; i++)
        {
            var row = i + 2;

            worksheet.Cell(row, 1).Value = publicationTitles[random.Next(publicationTitles.Length)];
            worksheet.Cell(row, 2).Value = GenerateDOI();
            worksheet.Cell(row, 3).Value = GenerateWOS();
            worksheet.Cell(row, 4).Value = GenerateISBN();
            worksheet.Cell(row, 5).Value = researcherName;
            worksheet.Cell(row, 6).Value = random.Next(2); // 0 sau 1 pentru ISI Roșu
            worksheet.Cell(row, 7).Value = random.Next(2); // 0 sau 1 pentru ISI Galben
            worksheet.Cell(row, 8).Value = random.Next(2020, 2025); // An între 2020-2024
            worksheet.Cell(row, 9).Value = publicationTypes[random.Next(publicationTypes.Length)];
        }

        // Auto-fit columns
        worksheet.Columns().AdjustToContents();

        // Save file
        string filePath = Utils.CreateFilePath(fileName);
        workbook.SaveAs(filePath);
    }

    private static string GenerateDOI()
    {
        return $"10.{random.Next(1000, 9999)}/{random.Next(10000, 99999)}.{random.Next(1000, 9999)}";
    }

    private static string GenerateWOS()
    {
        return $"WOS:{random.Next(100000000, 999999999)}";
    }

    private static string GenerateISBN()
    {
        // Format ISBN-13: 978-xxx-xxxxx-xxx-x
        return $"978-{random.Next(100, 999)}-{random.Next(10000, 99999)}-{random.Next(100, 999)}-{random.Next(0, 9)}";
    }
}
