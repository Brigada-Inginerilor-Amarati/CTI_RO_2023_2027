
package problem2.template;

public class Coffee extends Beverage {
    @Override
    protected void brew() {
        System.out.println("Grinding beans");
    }

    @Override
    protected void addCondiments() {
        System.out.println("Adding milk");
        System.out.println("Adding sugar");
        System.out.println("Adding foam");
    }
}
