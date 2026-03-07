
package problem2.template;

public class Tea extends Beverage {
    @Override
    protected void brew() {
        System.out.println("Putting tea infusion");
    }

    @Override
    protected void addCondiments() {
        System.out.println("Adding lemon");
        System.out.println("Adding honey");
    }
}
