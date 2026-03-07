/*
3. Implementati o metoda statica Comp, care primeste 2 functii (int->int) f si g, si returneaza o functie care reprezinta f compus cu g.
*/

namespace Exercitiul_03{
    delegate int MyDelegate(int x);

    class Program{
        public static MyDelegate Comp(MyDelegate f, MyDelegate g){
            return x => f(g(x));
        }

        public static int f(int x){
            return x + 2;
        }

        public static int g(int x){
            return x * 3;
        }

        public static void Main(string[] args){
            MyDelegate delF = Program.f;
            MyDelegate delG = Program.g;

            MyDelegate compFunc = Comp(delF, delG);

            int x = 5;
            Console.WriteLine(compFunc(x)); // Output: f(g(5)) = f(15) = 17
        }
    }
}