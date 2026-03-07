/*
3. Scrieti un program care citeste datele a n studenti si le salveaza intr-un array de obiecte Student. 

Ulterior, programul afiseaza datele studentului cu cea mai mare medie.

Clasa student va avea urmatoarea structura:

	Student:
	- name
	- year
	- grade1
	- grade2
	- grade3

Clasa student va avea un constructor, o proprietate care calculateaza media si o metoda ToString() pentru afisarea detaliilor studentului. 
Toate campurile vor fi read-only.
*/

using System;

class Student{
	private string name;
	private int year;
	private float grade1;
	private float grade2;
	private float grade3;

	public Student(string name, int year, float grade1, float grade2, float grade3){
		this.name = name;
		this.year = year;
		this.grade1 = grade1;
		this.grade2 = grade2;
		this.grade3 = grade3;
	}

	public float getAverageGrade(){
		return (float)(grade1 + grade2 + grade3) / 3;
	}
	
	public override string ToString(){
		return $"Name: {name}, Year: {year}, Grades: {grade1}, {grade2}, {grade3}, Average: {getAverageGrade()}";
	}

}

class Exercitiu_03_Daria{
	static void Main(String[] args){
		Console.WriteLine("Introduceti numarul de studenti: ");

		int n = 0;

		try{
            n = int.Parse(Console.ReadLine());
        }
        catch(Exception e){
            Console.WriteLine("Eroare: " + e.Message);
        }

		Student[] studenti = new Student[n];

		for(int i = 0; i < n; i++){
			Console.WriteLine($"Introduceti datele studentului {i + 1}: ");

			Console.Write("Nume: ");
			string name = Console.ReadLine();

			Console.Write("An: ");
			int year = 0;
			year = int.Parse(Console.ReadLine());

			Console.Write("Nota 1: ");
			float grade1 = 0;
			grade1 = float.Parse(Console.ReadLine());

			Console.Write("Nota 2: ");
			float grade2 = 0;
			grade2 = float.Parse(Console.ReadLine());

			Console.Write("Nota 3: ");
			float grade3 = 0;
			grade3 = float.Parse(Console.ReadLine());
			
			studenti[i] = new Student(name, year, grade1, grade2, grade3);
		}

		int maxAverageIndex = 0;

		for(int i = 0; i < n; i++){
			if(studenti[i].getAverageGrade() > studenti[maxAverageIndex].getAverageGrade()){
				maxAverageIndex = i;
			}
		}

		Console.WriteLine(studenti[maxAverageIndex].ToString());

	}
}				