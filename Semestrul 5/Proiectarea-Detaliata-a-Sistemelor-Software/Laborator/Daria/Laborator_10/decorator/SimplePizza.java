package Laborator.Daria.Laborator_10.decorator;

public class SimplePizza implements Pizza {
    @Override
    public String getDescription() {
        return "SimplePizza (ketchup, mozzarella)";
    }

    @Override
    public double getCost() {
        return 10.0;
    }
}
