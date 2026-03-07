import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

public class StudentRepository {
    private Collection<Student> students;

    public StudentRepository(Collection<Student> students) {
        this.students = new ArrayList<>(students);
    }

    public List<String> getStudentEmailsSortedByAgeUnderTheAgeOf(int age) {
        return this.students.stream()
                .filter((student) -> student.getAge() < age)
                .sorted(Comparator.comparingInt(Student::getAge))
                .map(Student::getEmail)
                .toList();
    }

    /**
     * @return returns the sorted list of distinct names.
     *
     *         SIDE EFFECT: makes all student names uppercase
     */
    public List<String> makeStudentNamesUppercaseAndReturnThemAsSortedDistinctList() {
        return this.students.stream()
                .peek(student -> student.setName(student.getName().toUpperCase()))
                .map(Student::getName)
                .sorted()
                .distinct()
                .toList();
    }

    public Set<String> getNonNullUniversities() {
        return this.students.stream()
                .map(Student::getUniversity)
                .filter(university -> university != null)
                .collect(Collectors.toSet());
    }

    public Map<String, Student> getStudentsMappedByEmail() {
        return this.students.stream()
                .collect(Collectors.toMap(Student::getEmail, Function.identity()));
    }

    public Map<String, List<Student>> getOverageStudentsGroupedByUniversity() {
        return this.students.stream()
                .filter(student -> student.getAge() >= 18)
                .filter(student -> student.getUniversity() != null)
                .collect(Collectors.groupingBy(Student::getUniversity));
    }

    public Optional<Student> getTheStudentWithTheNthShortestEmail(int n) {
        return this.students.stream()
                .sorted(Comparator.comparingInt(student -> student.getEmail().length()))
                .skip(n - 1)
                .findFirst();
    }

    public Optional<String> getTheNameOfTheSecondOldestStudent() {
        return this.students.stream()
                .sorted(Comparator.comparingInt(Student::getAge).reversed())
                .skip(1)
                .map(Student::getName)
                .findFirst();
    }

    public OptionalDouble getAverageAgeOfNStudentsInUniversity(int n, String university) {
        return this.students.stream()
                .filter(student -> student.getUniversity() == university)
                .limit(n)
                .mapToInt(Student::getAge)
                .average();
    }

    public long countStudentsWithNamesLongerThan(int n) {
        return this.students.stream()
                .filter(student -> student.getName().length() > n)
                .count();
    }

    /**
     * Students in no university (university == null) are considered to be in the
     * same university
     */
    public long countNumberOfStudentsWithAtLeastNColleaguesInDifferentUniversity(int n) {
        return this.students.stream()
                .filter(student -> student.getColleagues() != null &&
                        student.getColleagues().stream()
                                .map(Student::getUniversity)
                                .filter(univ -> !isInUniversity(student, univ))
                                .count() >= n)
                .count();
    }

    /**
     * Helper method for implementing
     * countNumberOfStudentsWithAtLeastNColleaguesInDifferentUniversity(int n)
     */
    private static boolean isInUniversity(Student student, String university) {
        if (university == null)
            return student.getUniversity() == null;
        return university.equals(student.getUniversity());
    }

    public List<Student> getStudentsWithAtLeastOneColleagueWithSameEmailDomain() {
        return this.students.stream()
                .filter(student -> student.getColleagues() != null &&
                        student.getColleagues()
                                .stream()
                                .map(Student::getEmail)
                                .map(StudentRepository::getEmailDomain)
                                .anyMatch(domain -> getEmailDomain(student.getEmail()).equals(domain)))
                .toList();
    }

    /**
     * Helper method for implementing
     * getStudentsWithAtLeastOneColleagueWithDifferentEmailDomain()
     */
    private static String getEmailDomain(String email) {
        if (email.indexOf('@') == -1) {
            return "";
        }
        return email.substring(email.indexOf('@') + 1);
    }
}
