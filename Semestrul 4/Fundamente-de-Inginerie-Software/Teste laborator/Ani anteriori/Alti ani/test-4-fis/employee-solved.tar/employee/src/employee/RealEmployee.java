package employee;

import java.util.ArrayList;
import java.util.List;

public class RealEmployee implements Employee {

    private int id;
    private double perHour;
    private List<TimeCard> itsCards = new ArrayList<>();

    public RealEmployee(int id, double perHour) {
        this.id = id;
        this.perHour = perHour;
    }

    @Override
    public double computeSalary() {
        double salary = 0;
        for (TimeCard itsCard : itsCards) {
            salary += itsCard.generateIncome(perHour);
        }
        return salary;
    }

    @Override
    public void addTimeCard(TimeCard tc) {
        itsCards.add(tc);
    }
}
