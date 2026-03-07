
package problem2.strategy;

public class Main {
    public static void main(String[] args) {
        System.out.println("--- Strategy Pattern: Coffee ---");
        Beverage coffee = new Beverage(new CoffeeStrategy());
        coffee.fixDrink();

        System.out.println("\n--- Strategy Pattern: Tea ---");
        Beverage tea = new Beverage(new TeaStrategy());
        tea.fixDrink();
    }
}
