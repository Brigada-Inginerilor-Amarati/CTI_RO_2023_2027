/*
Scrieți un program care gestionează conturile unei bănci. O bancă are următoarea structură:
Banca:

    Nume
    Swift
    List<Cont>

Un cont folosește următoarea structură:
Cont:

    Titular de cont
    Tip de cont (persoană / companie)
    Iban
    Suma

Notă: TipCont va fi un tip enum declarat. Toate proprietățile ar trebui să fie publice, doar cu citire. Următoarele operațiuni sunt disponibile pentru un cont:

    Depunere de bani
    Retragere de bani
    Afișare detalii cont (ToString)

Următoarele operațiuni sunt disponibile pentru o bancă:

    Deschidere de cont nou
    Găsirea unui cont după iban și afișarea detaliilor sale
    Depunere de bani într-un cont
    Retragere de bani dintr-un cont
    Transfer de bani între două conturi

Sfat: Puteți defini o metodă privată suplimentară GetAccount(string iban) pentru a găsi un cont cu un anumit iban.
*/

class Program
{
    public static void Main(string[] args)
    {
        Bank bank = new Bank("Banca Comerciala Romana", "BCR", new List<Account>());
        Account account1 = new Account("Paul", AccountType.Person, "RO1234567890", 1000);
        Account account2 = new Account("Dan", AccountType.Business, "RO0987654321", 2000);

        bank.OpenAccount(account1);
        bank.OpenAccount(account2);

        Console.WriteLine(bank.GetAccountByIban("RO1234567890"));
        Console.WriteLine(bank.GetAccountByIban("RO0987654321"));

        bank.Deposit("RO1234567890", 1000);
        bank.Withdraw("RO0987654321", 1000);

        Console.WriteLine(bank.GetAccountByIban("RO1234567890"));
        Console.WriteLine(bank.GetAccountByIban("RO0987654321"));

        bank.Transfer("RO1234567890", "RO0987654321", 500);

        Console.WriteLine(bank.GetAccountByIban("RO1234567890"));
        Console.WriteLine(bank.GetAccountByIban("RO0987654321"));

        try
        {
            bank.Transfer("RO1234567890", "RO0987654321", 2000);
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }

        try
        {
            bank.OpenAccount(account1);
        }
        catch (Exception e)
        {
            Console.WriteLine(e.Message);
        }
    }
}
