/*
Joc - această clasă va stoca următoarele proprietăți:

    string Nume
    string Dezvoltator
    DateTime DataLansare
    float Preț
    List<string> Etichete

Proprietățile vor fi setate folosind constructorul. O metodă ToString() va fi folosită pentru afișare.
*/

namespace Laborator_09;

class Game
{
    public string Name { get; }
    public string Developer { get; }
    public DateTime LaunchDate { get; }
    public float Price { get; }
    public List<string> Labels { get; }

    public Game(
        string name,
        string developer,
        DateTime launchDate,
        float price,
        List<string> labels
    )
    {
        Name = name;
        Developer = developer;
        LaunchDate = launchDate;
        Price = price;
        Labels = labels;
    }

    public override string ToString()
    {
        string labelsString = string.Join(", ", Labels);
        return $"Name: {Name}; Developer: {Developer}; Launch Date: {LaunchDate:yyyy-MM-dd}; Price: ${Price:F2}; Labels: {labelsString}";
    }
}
