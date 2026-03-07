import java.util.List;
import java.util.Objects;

public class Student {

    private String name;
    private String email;
    private int age;
    private String university;
    private List<Student> colleagues;

    public Student(String name, String email, int age, String university) {
        this.name = name;
        this.email = email;
        this.age = age;
        this.university = university;
    }

    public Student(String name, String email, int age, String university, List<Student> colleagues) {
        this.name = name;
        this.email = email;
        this.age = age;
        this.university = university;
        this.colleagues = colleagues;
    }

    public boolean isOverage() {
        return age >= 18;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public String getUniversity() {
        return university;
    }

    public void setUniversity(String university) {
        this.university = university;
    }

    @Override
    public String toString() {
        return name + " " + email + " " + age + " " + university;
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

    public List<Student> getColleagues() {
        return colleagues;
    }

    public void setColleagues(List<Student> colleagues) {
        this.colleagues = colleagues;
    }
}
