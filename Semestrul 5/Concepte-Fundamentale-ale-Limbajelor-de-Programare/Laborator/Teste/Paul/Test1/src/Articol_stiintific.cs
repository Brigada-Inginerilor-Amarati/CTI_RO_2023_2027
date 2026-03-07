/*
O clasa abstracta Articol_stiintific, care contine: (1p)
   - proprietatile: titlu autor an_publicare nr_pagini ISBN (string) (public get, protected set)
   - un constructor pentru initializarea proprietatilor
   - o metoda abstracta void Salut()
   - o metoda ToString() care sa returneze un string valorile concatenate ale membrilor
*/

namespace Test1;

public abstract class Articol_stiintific
{
    public string Titlu { get; protected set; }
    public string Autor { get; protected set; }
    public int An_publicare { get; protected set; }
    public int Nr_pagini { get; protected set; }
    public string ISBN { get; protected set; }

    public Articol_stiintific(
        string titlu,
        string autor,
        int an_publicare,
        int nr_pagini,
        string ISBN
    )
    {
        Titlu = titlu;
        Autor = autor;
        An_publicare = an_publicare;
        Nr_pagini = nr_pagini;
        this.ISBN = ISBN;
    }

    public abstract void Salut();

    public override string ToString()
    {
        return $"{Titlu} {Autor} {An_publicare} {Nr_pagini} {ISBN}";
    }
}
