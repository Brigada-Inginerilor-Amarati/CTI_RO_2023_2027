using System;
using System.Collections.Generic;
using System.ComponentModel.Design;


namespace Laborator2
{

    class Account
    {
        protected string AccountHolder { get; }

        public enum AccountType
        {
            Person =0,
            Comapny =1
        }

        protected AccountType TypeAccount { get; }
        
        public string Iban { get;}
        public long Amount{get; private set; }
        
        public Account(string accountholder, AccountType accounttype,  string iban, long amount)
        {
            AccountHolder = accountholder;
            TypeAccount = accounttype;
            Iban = iban;
            Amount = amount;
        }

        public void DepunereNumerar(long amount)
        {
            Amount += amount;
        }
        
        public void RetragereNumerar(long amount)
        {
            if(Amount - amount > 0)
                Amount -= amount;
            else
            {
                Console.WriteLine("Banii insuficienti");
            }
        }

        public string ToString()
        {
            return $"Holder: {AccountHolder}, Type: {TypeAccount}, Iban: {Iban}, Amount: {Amount}";
        }
    }

    class Bank
    {
        
        public string Name { get; set; }
        public string Swift { get; set; }
        private List<Account> Accounts { get; }

        public Bank(string name, string swift)
        {
            Name = name;
            Swift = swift;
            Accounts = new List<Account>();
        }

        public void CreateAccount(Account account)
        {
            if(!Accounts.Contains(account))
                Accounts.Add(account);
        }

        public Account GetAccount(string iban)
        {
            foreach (var account in Accounts)
            {
                if (account.Iban == iban)
                  //  Console.Write(account.ToString());
                    return account;
            }

            return null;
        }

        public void DepunereNumerar(string iban, long amount)
        {
            Account account = GetAccount(iban); 
            account.DepunereNumerar(amount);
        }

        public void RetragereNumerar(string iban, long amount)
        {
            Account account = GetAccount(iban); 
            account.RetragereNumerar(amount);
        }

        public void TransferCounturi(string iban1, string iban2, long amount)
        {
            Account account1 = GetAccount(iban1);
            Account account2 = GetAccount(iban2);

            if (account1.Amount > amount)
            {
                account1.DepunereNumerar(amount);
                account2.RetragereNumerar(amount);
            }
            else
            {
                Console.Write("Banii insuficienti");
            }
        }


    }
    class Program
    {
        static void Main()
        {
            Console.WriteLine("Creare Banca..");
         
            Console.WriteLine("Nume Banca:");
            string numeBanca = Console.ReadLine();
            Console.WriteLine("Swift:");
            string swift = Console.ReadLine();

            Bank banca = new Bank(numeBanca, swift);
            
         Console.WriteLine("Numarul conturilor:");
         
         int n = int.Parse(Console.ReadLine());
         List<Account> accounts = new List<Account>(n);
         Account.AccountType type1;

         for (int i = 0; i < n; i++)
         {
             Console.WriteLine("AccountHolder:");
             string accountHolder = Console.ReadLine();
             Console.WriteLine("Iban:");
             string iban = Console.ReadLine();
             Console.WriteLine("Type(0= Persoan, 1= Company):");
             int type = int.Parse(Console.ReadLine());
             if (type == 0)
             {
                 type1 = Account.AccountType.Person;
             }
             else
             {
                 type1 = Account.AccountType.Comapny;
             }
             Console.WriteLine("Amount:");
             long amount = long.Parse(Console.ReadLine());
             Account account = new Account(accountHolder, type1, iban, amount);
             banca.CreateAccount(account);
         }

         Account cp = banca.GetAccount("1");
         Account cp2 = banca.GetAccount("2");
         banca.DepunereNumerar("1", 100);
         Console.WriteLine(cp.ToString());
         banca.RetragereNumerar("1", 100);
         Console.WriteLine(cp.ToString());
         cp.DepunereNumerar(100);
         Console.WriteLine(cp.ToString());
         banca.TransferCounturi("1", "2", 100);
         Console.WriteLine(cp.ToString());
         Console.WriteLine(cp2.ToString());
         
        }
    }
}