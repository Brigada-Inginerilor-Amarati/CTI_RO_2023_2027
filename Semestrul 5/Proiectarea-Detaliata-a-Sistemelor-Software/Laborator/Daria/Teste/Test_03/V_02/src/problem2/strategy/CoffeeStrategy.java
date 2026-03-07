
package problem2.strategy;

public class CoffeeStrategy implements PreparationStrategy {
    @Override
    public void prepare() {
        System.out.println("Grinding beans");
        System.out.println("Pouring into cup (part of flow)");
        System.out.println("Adding milk");
        System.out.println("Adding sugar");
        System.out.println("Adding foam");
    }
}
