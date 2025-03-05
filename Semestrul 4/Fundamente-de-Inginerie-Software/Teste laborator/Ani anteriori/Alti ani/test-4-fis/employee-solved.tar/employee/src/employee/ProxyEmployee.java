package employee;

public class ProxyEmployee implements Employee {

    private static String password;
    private static String readPassword;
    private RealEmployee employee;

    public ProxyEmployee(int id, double perHour) {
        employee = new RealEmployee(id, perHour);
    }

    @Override
    public double computeSalary() {
        return employee.computeSalary();
    }

    @Override
    public void addTimeCard(TimeCard tc) {
        employee.addTimeCard(tc);
    }

    public static void setPassword(String passwd) {

    }

    private static void readPassword() {

    }

    private static boolean checkPassword() {
        readPassword();
        return password.equals(readPassword);
    }
}
