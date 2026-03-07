import java.util.ArrayList;
import java.util.Collection;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Optional;
import java.util.OptionalDouble;
import java.util.Set;
import java.util.stream.Collectors;

public class StudentRepository {
    private Collection<Student> students;

    public StudentRepository(Collection<Student> students) {
        this.students = new ArrayList<>(students);
    }

    public List<String> getStudentEmailsSortedByAgeUnderTheAgeOf(int age) {
        return students.stream()
                .filter(s -> s.getAge() < age)
                .sorted((s1, s2) -> Integer.compare(s1.getAge(), s2.getAge()))
                .map(Student::getEmail)
                .toList();
    }

    public List<String> makeStudentNamesUppercaseAndReturnThemAsSortedDistinctList() {
        return students.stream()
                .peek(s -> s.setName(s.getName().toUpperCase()))
                .map(Student::getName)
                .distinct()
                .sorted()
                .toList();
    }

    public Set<String> getNonNullUniversities() {
        return students.stream()
                .map(Student::getUniversity)
                .filter(u -> u != null)
                .collect(Collectors.toSet());
    }

    public Map<String, Student> getStudentsMappedByEmail() {
        return students.stream()
                .filter(s -> s.getEmail() != null)
                .collect(Collectors.toMap(Student::getEmail, s -> s));
    }

    public Map<String, List<Student>> getOverageStudentsGroupedByUniversity() {
        return students.stream()
                .filter(s -> s.getUniversity() != null)
                .filter(Student::isOverage)
                .collect(Collectors.groupingBy(Student::getUniversity));
    }

    public Optional<Student> getTheStudentWithTheNthShortestEmail(int n) {
        return students.stream()
                .filter(s -> s.getEmail() != null)
                .sorted(Comparator.comparingInt((Student s) -> s.getEmail().length())
                        .thenComparing(Student::getEmail, String.CASE_INSENSITIVE_ORDER))
                .skip(n - 1)
                .findFirst();
    }

    public Optional<String> getTheNameOfTheSecondOldestStudent() {
        return students.stream()
                .sorted(Comparator.comparingInt(Student::getAge).reversed())
                .skip(1)
                .map(Student::getName)
                .findFirst();
    }

    public OptionalDouble getAverageAgeOfNStudentsInUniversity(int n, String university) {
        return students.stream()
                .filter(s -> s.getUniversity() != null && isInUniversity(s, university))
                .limit(n)
                .mapToInt(Student::getAge)
                .average();
    }

    public long countStudentsWithNamesLongerThan(int n) {
        return students.stream()
                .map(Student::getName)
                .filter(Objects::nonNull)
                .filter(name -> name.length() > n)
                .count();
    }

    public long countNumberOfStudentsWithAtLeastNColleaguesInDifferentUniversity(int n) {
        return students.stream()
                .filter(s -> s.getColleagues() != null && !s.getColleagues().isEmpty())
                .filter(s -> s.getColleagues().stream()
                        .filter(Objects::nonNull)
                        .filter(col -> !isInUniversity(col, s.getUniversity()))
                        .limit(n)
                        .count() >= n)
                .count();
    }

    private static boolean isInUniversity(Student student, String university) {
        if (university == null) return student.getUniversity() == null;
        return university.equals(student.getUniversity());
    }

    public List<Student> getStudentsWithAtLeastOneColleagueWithSameEmailDomain() {
        return students.stream()
                .filter(s -> s.getColleagues() != null && !s.getColleagues().isEmpty())
                .filter(s -> {
                    String domain = getEmailDomain(s.getEmail());
                    return s.getColleagues().stream()
                            .filter(st -> getEmailDomain(st.getEmail()).equals(domain))
                            .findAny()
                            .isPresent();
                })
                .toList();
    }

    private static String getEmailDomain(String email) {
        if (email == null || !email.contains("@")) return "";
        return email.substring(email.indexOf('@') + 1);
    }
}
