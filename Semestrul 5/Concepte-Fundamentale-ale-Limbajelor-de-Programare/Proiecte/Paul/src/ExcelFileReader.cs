using System;
using System.Collections.Generic;
using ClosedXML.Excel;
using static Constants;

public class ExcelFileReader
{
    public IEnumerable<Publication> LoadPublications(string filePath)
    {
        if (string.IsNullOrWhiteSpace(filePath))
            throw new ArgumentException("File path cannot be null or empty.", nameof(filePath));

        using var workbook = new XLWorkbook(filePath);
        var worksheet = workbook.Worksheets.First();
        var publications = new List<Publication>();

        var lastRow = worksheet.LastRowUsed();
        if (lastRow == null)
            return publications;

        for (var row = DataStartRow; row <= lastRow.RowNumber(); row++)
        {
            try
            {
                var publication = ReadPublicationFromRow(worksheet, row);
                if (publication != null)
                {
                    publications.Add(publication);
                }
            }
            catch (Exception ex)
            {
                throw new InvalidDataException(
                    $"Error reading row {row} from file '{filePath}': {ex.Message}"
                );
            }
        }

        return publications;
    }

    private static Publication? ReadPublicationFromRow(IXLWorksheet worksheet, int row)
    {
        var title = worksheet.Cell(row, ColumnTitle).GetValue<string>() ?? string.Empty;
        var doi = worksheet.Cell(row, ColumnDOI).GetValue<string>() ?? string.Empty;
        var wos = worksheet.Cell(row, ColumnWOS).GetValue<string>() ?? string.Empty;
        var isbn = worksheet.Cell(row, ColumnISBN).GetValue<string>() ?? string.Empty;
        var author = worksheet.Cell(row, ColumnAuthor).GetValue<string>() ?? string.Empty;
        var isiRed = worksheet.Cell(row, ColumnISIRed).GetValue<bool>();
        var isiYellow = worksheet.Cell(row, ColumnISIYellow).GetValue<bool>();
        var publicationYear = worksheet.Cell(row, ColumnPublicationYear).GetValue<int>();
        var publicationType =
            worksheet.Cell(row, ColumnPublicationType).GetValue<string>() ?? string.Empty;

        // Validate data
        if (string.IsNullOrWhiteSpace(title))
        {
            return null; // Skip rows with empty title
        }

        if (publicationYear < MinPublicationYear || publicationYear > MaxPublicationYear)
        {
            throw new InvalidDataException(
                $"Invalid publication year {publicationYear}. Must be between {MinPublicationYear} and {MaxPublicationYear}."
            );
        }

        return new Publication(
            title,
            doi,
            wos,
            isbn,
            author,
            isiRed,
            isiYellow,
            publicationYear,
            publicationType
        );
    }
}
