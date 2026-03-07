/*
O clasa Articol_stiintific_de_conferinta, care mosteneste Articol_stiintific si contine: (1p)
   - proprietatile: cod_wos (string) (public get, protected set)
   - un constructor pentru initializarea membrilor
   - o metoda Salut() care sa afiseze 'Salut, sunt Articol_stiintific_de_conferinta'
   - o metoda ToString() care sa returneze un string valorile concatenate ale membrilor
*/

namespace Test1;

public class Articol_stiintific_de_conferinta : Articol_stiintific
{
    public string Cod_wos { get; protected set; }

    public Articol_stiintific_de_conferinta(
        string titlu,
        string autor,
        int an_publicare,
        int nr_pagini,
        string ISBN,
        string cod_wos
    )
        : base(titlu, autor, an_publicare, nr_pagini, ISBN)
    {
        Cod_wos = cod_wos;
    }

    public override void Salut()
    {
        Console.WriteLine("Salut, sunt Articol_stiintific_de_conferinta");
    }

    public override string ToString()
    {
        return base.ToString() + $" {Cod_wos}";
    }
}
