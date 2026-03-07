class Bank
{
    public string Name { get; }
    public string Swift { get; }
    public List<Account> Accounts { get; }

    public Bank(string name, string swift, List<Account> accounts)
    {
        Name = name;
        Swift = swift;
        Accounts = accounts;
    }

    public void OpenAccount(Account account)
    {
        if (Accounts.Contains(account))
        {
            Console.WriteLine($"Account already opened: {account.Iban}");
            return;
        }
        Accounts.Add(account);
    }

    public Account GetAccountByIban(string iban)
    {
        Account account = Accounts.Find(a => a.Iban == iban);
        if (account == null)
        {
            throw new Exception($"Account not found: {iban}");
        }
        return account;
    }

    public void Deposit(string iban, double amount)
    {
        var account = GetAccountByIban(iban);
        account.Deposit(amount);
    }

    public void Withdraw(string iban, double amount)
    {
        var account = GetAccountByIban(iban);
        account.Withdraw(amount);
    }

    public void Transfer(string fromIban, string toIban, double amount)
    {
        var fromAccount = GetAccountByIban(fromIban);
        var toAccount = GetAccountByIban(toIban);
        fromAccount.Withdraw(amount);
        toAccount.Deposit(amount);
    }
}
