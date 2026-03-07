import java.util.*;
import java.util.stream.Collectors;

class StudentsProvider {

    static Collection<Student> getTestStudents() {
        Student ana = new Student("Ana Ionescu", "ana.ionescu@gmail.com", 23, "UPT");
        Student marius = new Student("Marius Blide", "mblide@yahoo.com", 28, "UPT");
        Student gheorghe = new Student("Gheorghe Iova", "iovag@me.com", 10, "UPT");
        Student maria = new Student("Maria Tiurbe", "maria.tiurbe@yahoo.com", 20, "UPT");
        Student ion = new Student("Ion Lazar", "lazari@mail.com", 26, "UVT");
        Student cristian = new Student("Cristian Paul", "cristip@mail.com", 22, "UVT");
        Student nandor = new Student("Nandor Turzo", "nandor_t@gmail.com", 27, "UVT");
        Student iza = new Student("Izabella Kiss", "kissiza@mail.com", 17, "UMFT");
        Student adela = new Student("Adela Stefan", "adelas@gmail.com", 21, "UMFT");
        Student sergiu = new Student("Sergiu Bogdan", "sergiu.b@gmail.com", 25, "USV");
        Student andreea = new Student("Andreea Achim", "andreea32@hotmail.com", 18, null);
        Student cristi = new Student("Cristi Boc", "cristi.b@email.com", 29, null);
        ana.setColleagues(Arrays.asList(marius, gheorghe, maria, andreea));
        marius.setColleagues(Arrays.asList(ana, gheorghe, maria, andreea));
        andreea.setColleagues(Arrays.asList(ana, marius, gheorghe, maria));
        gheorghe.setColleagues(Arrays.asList(ana, marius, andreea, maria));
        maria.setColleagues(Arrays.asList(ana, marius, andreea, gheorghe));
        ion.setColleagues(Arrays.asList(cristian, nandor));
        cristian.setColleagues(Arrays.asList(ion, nandor));
        nandor.setColleagues(Arrays.asList(ion, cristian));
        iza.setColleagues(Arrays.asList(adela, cristi));
        adela.setColleagues(Arrays.asList(iza, cristi));
        cristi.setColleagues(Arrays.asList(iza, adela));
        sergiu.setColleagues(Arrays.asList(ana, marius, gheorghe, maria, ion, cristian, nandor, iza, adela, sergiu,
                andreea, cristi));

        return Arrays.asList(
                ana,
                marius,
                cristian,
                ion,
                iza,
                andreea,
                gheorghe,
                adela,
                maria,
                nandor,
                sergiu,
                cristi);
    }

    static Set<String> getNonNullUniversitiesSet() {
        return getTestStudents().stream().map(Student::getUniversity).filter(Objects::nonNull)
                .collect(Collectors.toSet());
    }

    static Set<String> getEmailsSet() {
        return getTestStudents().stream().map(Student::getEmail).collect(Collectors.toSet());
    }

    static List<String> makeStudentNamesUppercaseAndReturnItAsSortedDistinctList() {
        return getTestStudents().stream()
                .peek(s -> s.setName(s.getName().toUpperCase()))
                .map(Student::getName)
                .sorted()
                .distinct()
                .collect(Collectors.toList());
    }

    static List<String> getStudentEmailsSortedByAgeUnderTheAgeOf(int age) {
        return getTestStudents().stream()
                .filter(student -> student.getAge() < age)
                .sorted(Comparator.comparingInt(Student::getAge))
                .map(Student::getEmail)
                .collect(Collectors.toList());
    }

    public static Optional<Student> getTheStudentWithNthShortestEmail(int n) {
        return getTestStudents().stream()
                .sorted(Comparator.comparingInt(student -> student.getEmail().length()))
                .skip(n - 1)
                .findFirst();
    }

    public static Optional<String> getTheNameOfTheSecondOldestStudent() {
        return getTestStudents().stream()
                .sorted(Comparator.comparing(Student::getAge).reversed())
                .skip(1)
                .map(Student::getName)
                .findFirst();
    }

    public static OptionalDouble getAverageAgeOfNStudentsInUniversity(int n, String university) {
        return getTestStudents().stream()
                .filter(student -> isInUniversity(student, university))
                .mapToInt(Student::getAge)
                .limit(n)
                .average();
    }

    public static long countStudentsWithNamesLongerThan(int n) {
        return getTestStudents().stream()
                .map(Student::getName)
                .mapToInt(String::length)
                .filter(len -> len > n)
                .count();
    }

    static long countNumberOfStudentsWithAtLeastNColleaguesInDifferentUniversity(int n) {
        return getTestStudents().stream()
                .filter(student -> student.getColleagues() != null &&
                        student.getColleagues().stream()
                                .map(Student::getUniversity)
                                .filter(univ -> !isInUniversity(student, univ))
                                .count() >= n)
                .count();
    }

    private static boolean isInUniversity(Student student, String university) {
        if (university == null)
            return student.getUniversity() == null;
        return university.equals(student.getUniversity());
    }

    static List<Student> getStudentsWithAtLeastOneColleagueWithSameEmailDomain() {
        return getTestStudents().stream()
                .filter(student -> student.getColleagues() != null &&
                        student.getColleagues().stream()
                                .map(Student::getEmail)
                                .map(StudentsProvider::getEmailDomain)
                                .anyMatch(domain -> getEmailDomain(student.getEmail()).equals(domain)))
                .collect(Collectors.toList());
    }

    private static String getEmailDomain(String email) {
        if (email.indexOf('@') == -1) {
            return "";
        }
        return email.substring(email.indexOf('@') + 1);
    }
}
