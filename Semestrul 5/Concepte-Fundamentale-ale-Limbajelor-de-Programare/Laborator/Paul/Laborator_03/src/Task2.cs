/*
2. Implementați o metodă statică în clasa Program, care primește doi Coords și returnează mijlocul segmentului definit de cei doi Coords. Coord este o structură cu următoarea structură:
*/
namespace Laborator_03;

public struct Coords
{
    public float X { get; set; }
    public float Y { get; set; }

    public Coords(float x, float y)
    {
        X = x;
        Y = y;
    }

    public override string ToString()
    {
        return $"({X}, {Y})";
    }
}
