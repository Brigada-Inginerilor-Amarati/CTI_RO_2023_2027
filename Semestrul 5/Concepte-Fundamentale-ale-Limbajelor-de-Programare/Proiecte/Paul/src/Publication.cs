public record Publication(
    string Title,
    string DOI,
    string WOS,
    string ISBN,
    string Author,
    bool ISIRed,
    bool ISIYellow,
    int PublicationYear,
    string PublicationType
)
{
    public bool IsDuplicate(Publication other) =>
        (!string.IsNullOrWhiteSpace(DOI) && DOI == other.DOI)
        || (!string.IsNullOrWhiteSpace(WOS) && WOS == other.WOS)
        || (!string.IsNullOrWhiteSpace(ISBN) && ISBN == other.ISBN);

    public override string ToString() =>
        $"{Title},{DOI},{WOS},{ISBN},{Author},{ISIRed},{ISIYellow},{PublicationYear},{PublicationType}";
}
