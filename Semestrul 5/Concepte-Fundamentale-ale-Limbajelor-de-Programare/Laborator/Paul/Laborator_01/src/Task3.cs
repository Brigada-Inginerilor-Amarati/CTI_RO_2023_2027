/*
3. Scrieti un program care citeste datele a n studenti si le salveaza intr-un array de obiecte Student. Ulterior, programul afiseaza datele studentului cu cea mai mare medie.

Clasa student va avea urmatoarea structura:

	Student:
	- name
	- year
	- grade1
	- grade2
	- grade3

Clasa student va avea un constructor, o proprietate care calculateaza media si o metoda ToString() pentru afisarea detaliilor studentului. Toate campurile vor fi read-only.
*/

class Student{
    private string Name { get; }
    private int Year { get; }
    private float Grade1 { get; }
    private float Grade2 { get; }
    private float Grade3 { get; }

    public Student(string name, int year, float grade1, float grade2, float grade3){
        Name = name;
        Year = year;
        Grade1 = grade1;
        Grade2 = grade2;
        Grade3 = grade3;
    }

    public float CalculateAverage(){
        return (Grade1 + Grade2 + Grade3) / 3;
    }

    public override string ToString(){
        return $"Name: {Name}, Year: {Year}, Grade1: {Grade1}, Grade2: {Grade2}, Grade3: {Grade3}, Average: {CalculateAverage()}";
    }
}

class Task3{

    public static Student CreateStudent(){
        Console.WriteLine("Introduceti numele studentului:");
        string name = Console.ReadLine();

        Console.WriteLine("Introduceti anul studentului:");
        int year = Convert.ToInt32(Console.ReadLine());

        Console.WriteLine("Introduceti nota la disciplina 1:");
        float grade1 = Convert.ToSingle(Console.ReadLine());

        Console.WriteLine("Introduceti nota la disciplina 2:");
        float grade2 = Convert.ToSingle(Console.ReadLine());

        Console.WriteLine("Introduceti nota la disciplina 3:");
        float grade3 = Convert.ToSingle(Console.ReadLine());

        Console.WriteLine();
        return new Student(name, year, grade1, grade2, grade3);
    }

    public static Student GetMaxAverageStudent(Student[] students){
        Student maxStudent = students[0];
        for(int i = 1; i < students.Length; i++){
            if(students[i].CalculateAverage() > maxStudent.CalculateAverage()){
                maxStudent = students[i];
            }
        }
        return maxStudent;
    }

    public static void Main(){
        Console.WriteLine("Introduceti numarul de studenti:");
        int n = Convert.ToInt32(Console.ReadLine());

        Student[] students = new Student[n];

        for(int i = 0; i < n; i++){
            students[i] = CreateStudent();
        }

        Student maxStudent = GetMaxAverageStudent(students);
        Console.WriteLine("Studentul cu cea mai mare medie este: " + maxStudent);
    }
}
