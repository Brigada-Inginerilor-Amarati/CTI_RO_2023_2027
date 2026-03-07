
package problem2.template;

public class Main {
    public static void main(String[] args) {
        System.out.println("--- Template Method: Coffee ---");
        Beverage coffee = new Coffee();
        coffee.fixDrink();

        System.out.println("\n--- Template Method: Tea ---");
        Beverage tea = new Tea();
        tea.fixDrink();
    }
}
