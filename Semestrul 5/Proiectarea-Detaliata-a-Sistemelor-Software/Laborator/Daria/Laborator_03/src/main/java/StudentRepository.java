import java.util.*;
import java.util.stream.Collectors;

public class StudentRepository {
    private Collection<Student> students;

    public StudentRepository(Collection<Student> students) {
        this.students = new ArrayList<>(students);
    }

    public List<String> getStudentEmailsSortedByAgeUnderTheAgeOf(int age) {
        return students.stream()
                .filter(student -> student.getAge() < age)
                .sorted(Comparator.comparingInt(Student::getAge))
                .map(Student::getEmail)
                .collect(Collectors.toList());
    }

    /**
     * @return returns the sorted list of distinct names.
     *
     * SIDE EFFECT: makes all student names uppercase
     */
    public List<String> makeStudentNamesUppercaseAndReturnThemAsSortedDistinctList() {
        return students.stream()
                .peek(student -> student.setName(student.getName().toUpperCase()))
                .map(Student::getName)
                .sorted()
                .distinct()
                .collect(Collectors.toList());
    }

    public Set<String> getNonNullUniversities() {
        return students.stream()
                .filter(student -> student.getUniversity() != null)
                .map(Student::getUniversity)                   // ori fara primul filtru si scriem dupa asta: .filter(Objects::nonNull)
                .collect(Collectors.toSet());
    }

    public Map<String, Student> getStudentsMappedByEmail() {
        return students.stream()
                .filter(student -> student.getEmail() != null)
                .collect(Collectors.toMap(
                        Student::getEmail,
                        student -> student            // sau Function.identity()
                ));
    }

    public Map<String, List<Student>> getOverageStudentsGroupedByUniversity() {
        return students.stream()
                .filter(student -> student.getUniversity() != null)
                .filter(Student::isOverage)
                .collect(Collectors.groupingBy(
                        Student::getUniversity
                ));
    }

    public Optional<Student> getTheStudentWithTheNthShortestEmail(int n) {
        return students.stream()
                .filter(student -> student.getEmail() != null)
                .sorted(Comparator.comparingInt(student -> student.getEmail().length()))
                .skip(n - 1)
                .findFirst();
    }

    public Optional<String> getTheNameOfTheSecondOldestStudent() {
        return students.stream()
                .sorted(Comparator.comparingInt(Student::getAge).reversed())
                .map(Student::getName)
                .skip(1)
                .findFirst();
    }

    public OptionalDouble getAverageAgeOfNStudentsInUniversity(int n, String university) {
        return students.stream()
                .filter(student -> student.getUniversity() != null && isInUniversity(student, university))
                .limit(n)
                .mapToInt(Student::getAge)
                .average();
    }

    public long countStudentsWithNamesLongerThan(int n) {
        return students.stream()
                .filter(student -> student.getName() != null)
                .filter(student -> student.getName().length() > n)
                .count();
    }

    /*
     ori puteam sa scriem asa:

                .map(Student::getName)
                .filter(Objects::nonNull)
                .filter(name -> name.length() > n)
                .count();

     */

    /**
     * Students in no university (university == null) are considered to be in the same university
     */
    public long countNumberOfStudentsWithAtLeastNColleaguesInDifferentUniversity(int n) {
        return students.stream()
                .filter(student -> student.getColleagues()  != null)
                .filter(studentCurent -> {
                    String universityCurent = studentCurent.getUniversity();

                    long countColleagues = studentCurent.getColleagues().stream()
                            .filter(Objects :: nonNull)
                            .filter(colleague -> !isInUniversity(colleague, universityCurent))
                            .count();

                    return countColleagues >= n;
                })
                .count();
    }

    /**
     * Helper method for implementing countNumberOfStudentsWithAtLeastNColleaguesInDifferentUniversity(int n)
     */
    private static boolean isInUniversity(Student student, String university) {
        if (university == null)
            return student.getUniversity() == null;
        return university.equals(student.getUniversity());
    }

    public List<Student> getStudentsWithAtLeastOneColleagueWithSameEmailDomain() {
        return students.stream()
                .filter(student -> student.getColleagues() != null && !student.getColleagues().isEmpty())
                .filter(studentCurent -> {
                    String domainCurent = getEmailDomain(studentCurent.getEmail());
                    long count = studentCurent.getColleagues().stream()
                            .filter(colleague -> getEmailDomain(colleague.getEmail()).equals(domainCurent))
                            .count();

                    return count > 0;
                })
                .collect(Collectors.toList());
    }


    /**
     * Helper method for implementing getStudentsWithAtLeastOneColleagueWithDifferentEmailDomain()
     */
    private static String getEmailDomain(String email) {
        if(email.indexOf('@') == -1) {
            return "";
        }
        return email.substring(email.indexOf('@') + 1);
    }
}