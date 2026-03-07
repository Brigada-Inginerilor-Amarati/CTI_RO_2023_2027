public class PublicationFileNotFoundException : Exception
{
    public PublicationFileNotFoundException(string filePath)
        : base($"File '{filePath}' not found.")
    {
        FilePath = filePath;
    }

    public string FilePath { get; }
}

public class InvalidFileFormatException : Exception
{
    public InvalidFileFormatException(string filePath, string expectedFormat)
        : base($"File '{filePath}' is not a valid {expectedFormat} file.")
    {
        FilePath = filePath;
        ExpectedFormat = expectedFormat;
    }

    public string FilePath { get; }
    public string ExpectedFormat { get; }
}

public class InvalidDataException : Exception
{
    public InvalidDataException(string message)
        : base(message) { }
}
