using System;
using System.IO;
using static Constants;

public class CsvExporter
{
    public void ExportToCsv(PublicationRepository repository, string filePath)
    {
        if (repository == null)
            throw new ArgumentNullException(nameof(repository));
        if (string.IsNullOrWhiteSpace(filePath))
            throw new ArgumentException("File path cannot be null or empty.", nameof(filePath));

        // Ensure directory exists
        var directory = Path.GetDirectoryName(filePath);
        if (!string.IsNullOrEmpty(directory) && !Directory.Exists(directory))
        {
            Directory.CreateDirectory(directory);
        }

        using var csvFile = new StreamWriter(filePath);
        csvFile.WriteLine(CsvHeader);

        repository.GetAll().ToList().ForEach(csvFile.WriteLine);
    }
}
