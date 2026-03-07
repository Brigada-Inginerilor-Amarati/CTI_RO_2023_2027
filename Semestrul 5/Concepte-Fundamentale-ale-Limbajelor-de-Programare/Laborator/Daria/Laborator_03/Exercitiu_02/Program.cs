/*
2. Implementați o metodă statică în clasa Program, care primește doi Coords și 

returnează mijlocul segmentului definit de cei doi Coords. 

Coord este o structură cu următoarea structură:

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
*/

using System;

namespace Exercitiu_02{
    public struct Coords{
        public float X { get; set; }
        public float Y { get; set; }

        public Coords(float x, float y){
            X = x;
            Y = y;
        }

        public override string ToString(){
            return $"({X}, {Y})";
        }
    }

    class Program{
        public static Coords GetMiddlePoint(Coords coord1, Coords coord2){
            Coords middlePoint = new Coords();
            middlePoint.X = (coord1.X + coord2.X) / 2;
            middlePoint.Y = (coord1.Y + coord2.Y) / 2;
            return middlePoint;
        }
        
        public static void Main(string[] args){
            Coords coord1 = new Coords(13, 31);
            Coords coord2 = new Coords(31, 13);

            Coords middlePoint = GetMiddlePoint(coord1, coord2);
            Console.WriteLine($"Middle point: {middlePoint}");
            Console.WriteLine($"Coord1: {coord1}");
            Console.WriteLine($"Coord2: {coord2}");
        }
    }
}