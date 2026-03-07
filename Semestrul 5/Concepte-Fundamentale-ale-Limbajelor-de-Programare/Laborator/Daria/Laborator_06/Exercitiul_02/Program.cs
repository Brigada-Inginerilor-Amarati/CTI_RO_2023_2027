/*

2. Implementați o metodă statică FGX, care primește 2 delegați ca parametri și un float x și returnează valoarea compusă a celor două funcții date.

public static float FGX(MyDelegate del1, MyDelegate del2, float x)

Testați implementarea folosind următoarele funcții:

public static float f(float x)
{
    return x * 3;
}

public static float g(float x)
{
    return x - 2;
}
*/

namespace Exercitiul_02{
    delegate float MyDelegate(float x);

    class Program{
        public static float FGX(MyDelegate del1, MyDelegate del2, float x){
            return del1(del2(x));
        }

        public static float f(float x){
            return x * 3;
        }

        public static float g(float x){
            return x - 2;
        }

        public static void Main(string[] args){
            MyDelegate del1 = Program.f;
            MyDelegate del2 = Program.g;

            float x = 10;
            Console.WriteLine(FGX(del1, del2, x));
        }
    }
}