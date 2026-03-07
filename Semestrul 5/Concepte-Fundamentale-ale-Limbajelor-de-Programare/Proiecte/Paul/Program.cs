using System;
using System.IO;
using static Constants;

class Program
{
    static int Main(string[] args)
    {
        try
        {
            var fileNames = Utils.ProcessArguments(args);

            // If generation was requested, exit successfully
            if (fileNames.Count == 0)
            {
                return 0;
            }

            // Validate all files before processing
            fileNames.ForEach(Utils.ValidateFileExists);
            fileNames.ForEach(Utils.ValidateFileIsExcel);

            // Load and process publications
            var repository = new PublicationRepository();
            var reader = new ExcelFileReader();

            foreach (var filePath in fileNames)
            {
                try
                {
                    var publications = reader.LoadPublications(filePath);
                    foreach (var publication in publications)
                    {
                        if (!repository.TryAdd(publication))
                        {
                            Console.Error.WriteLine(
                                $"Warning: Publication '{publication.Title}' is a duplicate and was skipped."
                            );
                        }
                    }
                }
                catch (Exception ex)
                {
                    Console.Error.WriteLine($"Error loading file '{filePath}': {ex.Message}");
                    return 1;
                }
            }

            // Print statistics and publications
            var statistics = new PublicationStatistics(repository);
            statistics.PrintStatistics();
            statistics.PrintPublications();

            // Export to CSV
            var outputPath = Path.Combine(DataDirectory, DefaultOutputFile);
            var exporter = new CsvExporter();
            exporter.ExportToCsv(repository, outputPath);

            Console.WriteLine($"\nPublications exported to: {outputPath}");

            return 0;
        }
        catch (PublicationFileNotFoundException ex)
        {
            Console.Error.WriteLine($"Error: {ex.Message}");
            return 2;
        }
        catch (InvalidFileFormatException ex)
        {
            Console.Error.WriteLine($"Error: {ex.Message}");
            return 3;
        }
        catch (InvalidDataException ex)
        {
            Console.Error.WriteLine($"Data Error: {ex.Message}");
            return 4;
        }
        catch (ArgumentException ex)
        {
            Console.Error.WriteLine(ex.Message);
            return 5;
        }
        catch (Exception ex)
        {
            Console.Error.WriteLine($"Unexpected error: {ex.Message}");
            return 6;
        }
    }
}
