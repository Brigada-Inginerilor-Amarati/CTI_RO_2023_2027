package employee;

public class TimeCard {
    private double workedHours;
    private RealEmployee re;

    public TimeCard(double workedHours) {
        this.workedHours = workedHours;
    }

    public double generateIncome(double perHour) {
        return workedHours * perHour;
    }

    public void setRealEmployee(RealEmployee re) {
        this.re = re;
    }
}
