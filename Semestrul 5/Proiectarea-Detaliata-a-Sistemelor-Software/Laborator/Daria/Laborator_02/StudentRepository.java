import java.util.ArrayList;
import java.util.Collection;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Set;
import java.util.function.Function;
import java.util.stream.Collectors;



public class StudentRepository {
    private Collection<Student> students;

    public StudentRepository(Collection<Student> students) {
        this.students = new ArrayList<>(students);
    }

    // get the number of students older than the given age
    public long getNoOfStudentOlderThan(int age){
        return students.stream()
            .filter(student -> student.getAge() >= age)
            .count();
    }

    // check if all overage students are in university
    public boolean areAllOverageStudentsInUniversity(){
        return students.stream()
            .filter(Student::isOverage)
            .allMatch(student -> student.getUniversity() != null);
    }

    // get the age of the youngest student
    public int getAgeOfYoungestStudent(){
        return students.stream()
            .mapToInt(Student::getAge)
            .min()
            .getAsInt();
    }

    // get the oldest student
    public Optional<Student> getOldestStudent(){
        return students.stream()  
            .max(Comparator.comparing(Student::getAge));
    }

    // get the nth student by email length
    public Optional<Student> getNthStudentByEmailLength(int n){
        return students.stream() 
            .sorted(Comparator.comparingInt(student -> student.getEmail().length()))
            .skip(n - 1)
            .findFirst();
    }

    public double getAverageNAmeLengthOfAllStudents(){
        return students.stream()
            .map(Student::getName)
            .mapToInt(String::length)
            .average()
            .orElse(0.);
    }

    public List<String> getAllEmails(){
        return students.stream()
            .map(Student::getEmail)
            .collect(Collectors.toList());
    }

    public Set<String> getDistinctNamesSet(){
        return students.stream()
            .map(Student::getName)
            .collect(Collectors.toSet());
    }

    public List<String> getListOfUniversities(){
        return students.stream()
            .map(Student::getUniversity)
            .distinct()
            .collect(Collectors.toList());
    }

    public Map<String, Student> getStudentsMappedByEmail(){
        return students.stream()
            .collect(Collectors.toMap(
                Student::getEmail,
                Function.identity()
            ));
    }

    public Map<String, List<Student>> getStudentsGroupedByUniversity(){
        return students.stream()
            .collect(Collectors.groupingBy(Student::getUniversity));
    }

    public void printStudentsInUniversit(){
        students.stream() 
            .filter(student -> student.getUniversity() != null)
            .forEach(student -> System.out.printf(
                "University: %s, Name: %s, Email: %s, Age: %d%n",
                student.getUniversity(),
                student.getName(),
                student.getEmail(),
                student.getAge()
            ));
    }

    public boolean noneOfTheFiveYoungestStudentsHaveGmail(){
        return students.stream()
            .sorted(Comparator.comparingInt(Student::getAge))
            .limit(5)
            .noneMatch(student -> student.getEmail().endsWith("@gmail.com"));
    }

    // Lazy Evaluation

    public boolean allOverageStudentHaveYahooAccounts(){
        return students.stream()
            .filter(Student::isOverage)
            .map(Student::getEmail)
            .allMatch(email -> email.endsWith("@yahoo.com"));
    }
}
