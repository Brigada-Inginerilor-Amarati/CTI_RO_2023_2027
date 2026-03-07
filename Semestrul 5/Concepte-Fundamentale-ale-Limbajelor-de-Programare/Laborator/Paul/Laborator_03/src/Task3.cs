/*
3. Implementați o clasă Cont, care are proprietățile nume și sold (inițializate de constructor), și o metodă Retragere care permite retragerea de fonduri. Metoda primește un parametru care specifică suma retrasă și un parametru out în care returnează soldul rămas. Dacă suma completă poate fi retrasă, metoda returnează true. Dacă suma nu poate fi retrasă, metoda returnează false. Metoda va avea următoarea semnătură:

public bool Retragere(double suma, out double soldRamas)
*/
namespace Laborator_03;

public class Account
{
    public string Name { get; private set; }
    public double Balance { get; private set; }

    public Account(string name, double balance)
    {
        Name = name;
        Balance = balance;
    }

    public bool Withdraw(double sum, out double remainingBalance)
    {
        if (sum <= Balance)
        {
            Balance -= sum;
            remainingBalance = Balance;
            return true;
        }
        remainingBalance = Balance;
        return false;
    }
}
