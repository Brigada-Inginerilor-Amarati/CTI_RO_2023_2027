using System.Collections.Generic;
using System.Linq;

public class PublicationRepository
{
    private readonly HashSet<Publication> _publications = new();
    private readonly HashSet<string> _dois = new();
    private readonly HashSet<string> _wosCodes = new();
    private readonly HashSet<string> _isbns = new();

    public int Count => _publications.Count;
    public int CountISIRed => _publications.Count(p => p.ISIRed);
    public int CountISIYellow => _publications.Count(p => p.ISIYellow);

    public IEnumerable<Publication> GetAll() => _publications;

    public bool TryAdd(Publication publication)
    {
        if (IsDuplicate(publication))
        {
            return false;
        }

        _publications.Add(publication);

        if (!string.IsNullOrWhiteSpace(publication.DOI))
            _dois.Add(publication.DOI);
        if (!string.IsNullOrWhiteSpace(publication.WOS))
            _wosCodes.Add(publication.WOS);
        if (!string.IsNullOrWhiteSpace(publication.ISBN))
            _isbns.Add(publication.ISBN);

        return true;
    }

    public void AddRange(IEnumerable<Publication> publications)
    {
        publications.ToList().ForEach(p => TryAdd(p));
    }

    public bool IsDuplicate(Publication publication)
    {
        if (!string.IsNullOrWhiteSpace(publication.DOI) && _dois.Contains(publication.DOI))
            return true;
        if (!string.IsNullOrWhiteSpace(publication.WOS) && _wosCodes.Contains(publication.WOS))
            return true;
        if (!string.IsNullOrWhiteSpace(publication.ISBN) && _isbns.Contains(publication.ISBN))
            return true;

        return false;
    }
}
