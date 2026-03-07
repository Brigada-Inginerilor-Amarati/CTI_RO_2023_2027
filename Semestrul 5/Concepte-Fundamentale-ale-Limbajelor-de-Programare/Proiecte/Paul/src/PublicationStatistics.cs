using System;
using System.Collections.Generic;
using System.Linq;

public class PublicationStatistics
{
    private readonly PublicationRepository _repository;

    public PublicationStatistics(PublicationRepository repository)
    {
        _repository = repository ?? throw new ArgumentNullException(nameof(repository));
    }

    public void PrintStatistics(System.IO.TextWriter? output = null)
    {
        output ??= Console.Out;

        output.WriteLine($"Total publications: {_repository.Count}");
        output.WriteLine($"Total ISI Red: {_repository.CountISIRed}");
        output.WriteLine($"Total ISI Yellow: {_repository.CountISIYellow}");
    }

    public void PrintPublications(System.IO.TextWriter? output = null)
    {
        output ??= Console.Out;

        _repository.GetAll().ToList().ForEach(p => output.WriteLine(p));
    }
}
