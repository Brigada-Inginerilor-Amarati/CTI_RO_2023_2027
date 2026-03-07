package Laborator.Daria.Laborator_11.template;

public class Worker {
    protected int x;

    public Worker(int _x) {
        x = _x;
    }

    // Template Method
    public final int makeStuff() {
        int z;
        modifyX();
        z = calculateZ();
        System.out.println("Values are:" + x + " and " + z);
        return x + z;
    }

    protected void modifyX() {
        x++;
    }

    protected int calculateZ() {
        return x * x;
    }
}
