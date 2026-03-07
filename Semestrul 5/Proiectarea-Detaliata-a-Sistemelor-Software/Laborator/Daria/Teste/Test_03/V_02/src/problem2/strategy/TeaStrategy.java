
package problem2.strategy;

public class TeaStrategy implements PreparationStrategy {
    @Override
    public void prepare() {
        System.out.println("Putting tea infusion");
        System.out.println("Pouring into cup (part of flow)");
        System.out.println("Adding lemon");
        System.out.println("Adding honey");
    }
}
