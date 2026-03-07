import java.util.Objects;

public class Student {
    private String name;
    private String email;
    private int age;
    private String university;

    // constructor
    public Student(String name, String email, int age, String university) {
        this.name = name;
        this.email = email;
        this.age = age;
        this.university = university;
    }

    public String getName() {
        return name;
    }

    public String getEmail() {
        return email;
    }

    public int getAge() {
        return age;
    }

    public String getUniversity() {
        return university;
    }

    public boolean isOverage() {
        return age >= 18;
    }

    @Override   
    public String toString() {
        return "Student{" +
                "name='" + name + '\'' +
                ", email='" + email + '\'' +
                ", age=" + age +
                ", university='" + university + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Student student = (Student) o;
        return email.equals(student.email);
    }

    @Override
    public int hashCode() {
        return Objects.hash(email);
    }
}
