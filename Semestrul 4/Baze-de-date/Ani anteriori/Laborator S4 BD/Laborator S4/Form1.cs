using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.Sql;
using System.Data.SqlClient;

namespace Laborator_S4
{
    public partial class Form1 : Form
    {
        SqlConnection connection = new SqlConnection (@"Data Source=(LocalDB)\v11.0;AttachDbFilename=C:\Users\student-b529\Downloads\Laborator S4\Laborator S4\Vanzari.mdf;Integrated Security=True");
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            connection.Open();
            SqlCommand cmd = connection.CreateCommand();
            cmd.CommandType = CommandType.Text;
            cmd.CommandText = "SELECT * FROM [CLIENT]";
            cmd.ExecuteNonQuery();
            connection.Close();
        }
    }
}
