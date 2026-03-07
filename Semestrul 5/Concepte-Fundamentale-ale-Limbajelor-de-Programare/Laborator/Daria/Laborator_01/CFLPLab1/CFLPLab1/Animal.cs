using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CFLPLab1
{
    public class Animal
    {
        private string nume;

        public string NumeAnimal { get; private set; }

        public Animal(string nume)
        {
            Nume = nume;
        }

        public string GetNume()
        {
            return nume;
        }

        public void SetNume(string nume)
        {
            this.nume = nume;
        }

        // public string Nume { get { return nume; } set { nume = value; } }
        public string Nume
        {
            get
            {
                return nume;
            }
            set
            {
                if (!string.IsNullOrEmpty(value))
                    nume = value;
            }
        }



        public override string ToString()
        {
            return Nume;
        }
    }
}
