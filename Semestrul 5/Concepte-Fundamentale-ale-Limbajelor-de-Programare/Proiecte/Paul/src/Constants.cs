public static class Constants
{
    public const int HeaderRow = 1;
    public const int DataStartRow = 2;

    // Excel column indices (1-based)
    public const int ColumnTitle = 1;
    public const int ColumnDOI = 2;
    public const int ColumnWOS = 3;
    public const int ColumnISBN = 4;
    public const int ColumnAuthor = 5;
    public const int ColumnISIRed = 6;
    public const int ColumnISIYellow = 7;
    public const int ColumnPublicationYear = 8;
    public const int ColumnPublicationType = 9;
    public const int TotalColumns = 9;

    // File paths
    public const string DataDirectory = "data";
    public const string DefaultOutputFile = "centralized.csv";

    // CSV header
    public const string CsvHeader =
        "Title,DOI,WOS,ISBN,Author,ISIRed,ISIYellow,PublicationYear,PublicationType";

    // Validation
    public const int MinPublicationYear = 1900;
    public const int MaxPublicationYear = 2100;
}
