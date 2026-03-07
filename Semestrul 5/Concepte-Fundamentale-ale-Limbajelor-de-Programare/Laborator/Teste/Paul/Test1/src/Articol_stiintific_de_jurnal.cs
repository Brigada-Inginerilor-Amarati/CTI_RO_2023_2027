/*
O clasa Articol_stiintific_de_jurnal, care mosteneste Articol_stiintific si contine: (1p)
   - proprietatile: factor_de_impact (float) (public get, protected set)
   - un constructor pentru initializarea membrilor
   - o metoda Salut() care sa afiseze 'Salut, sunt Articol_stiintific_de_jurnal'
   - o metoda ToString() care sa returneze un string valorile concatenate ale membrilor
*/

namespace Test1;

public class Articol_stiintific_de_jurnal : Articol_stiintific
{
    public float Factor_de_impact { get; protected set; }

    public Articol_stiintific_de_jurnal(
        string titlu,
        string autor,
        int an_publicare,
        int nr_pagini,
        string ISBN,
        float factor_de_impact
    )
        : base(titlu, autor, an_publicare, nr_pagini, ISBN)
    {
        Factor_de_impact = factor_de_impact;
    }

    public override void Salut()
    {
        Console.WriteLine("Salut, sunt Articol_stiintific_de_jurnal");
    }

    public override string ToString()
    {
        return base.ToString() + $" {Factor_de_impact}";
    }
}
