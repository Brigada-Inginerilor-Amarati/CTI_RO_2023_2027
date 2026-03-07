class Account
{
    public string Name { get; }
    public AccountType Type { get; }
    public string Iban { get; }
    public double Balance { get; private set; }

    public Account(string name, AccountType type, string iban, double balance)
    {
        Name = name;
        Type = type;
        Iban = iban;
        Balance = balance;
    }

    public void Deposit(double amount)
    {
        Balance += amount;
    }

    public void Withdraw(double amount)
    {
        if (Balance < amount)
        {
            throw new Exception($"Insufficient balance for account {this}");
        }
        Balance -= amount;
    }

    public override string ToString()
    {
        return $"Name: {Name}, Type: {Type}, Iban: {Iban}, Balance: {Balance}";
    }
}
