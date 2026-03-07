using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

public static class Utils
{
    public static string CreateFilePath(string fileName)
    {
        return Path.Combine(Constants.DataDirectory, fileName);
    }

    public static void ValidateFileExists(string filePath)
    {
        if (!File.Exists(filePath))
        {
            throw new PublicationFileNotFoundException(filePath);
        }
    }

    public static void ValidateFileIsExcel(string filePath)
    {
        if (!filePath.EndsWith(".xlsx", StringComparison.OrdinalIgnoreCase))
        {
            throw new InvalidFileFormatException(filePath, "Excel (.xlsx)");
        }
    }

    public static List<string> ProcessArguments(string[] args)
    {
        if (args.Length == 0)
        {
            throw new ArgumentException(
                "Usage: dotnet run <file_name.xlsx>\n"
                    + "Or: dotnet run generate (to generate test files)"
            );
        }

        if (args[0].Equals("generate", StringComparison.OrdinalIgnoreCase))
        {
            TestDataGenerator.GenerateTestFiles();
            return new List<string>(); // Return empty list to signal generation was done
        }

        return args.Select(arg =>
            {
                // If path already contains data directory or is absolute, use as-is
                if (
                    arg.StartsWith(
                        Constants.DataDirectory + Path.DirectorySeparatorChar,
                        StringComparison.OrdinalIgnoreCase
                    )
                    || arg.StartsWith(
                        Constants.DataDirectory + Path.AltDirectorySeparatorChar,
                        StringComparison.OrdinalIgnoreCase
                    )
                    || Path.IsPathRooted(arg)
                )
                {
                    return arg;
                }
                return CreateFilePath(arg);
            })
            .ToList();
    }
}
