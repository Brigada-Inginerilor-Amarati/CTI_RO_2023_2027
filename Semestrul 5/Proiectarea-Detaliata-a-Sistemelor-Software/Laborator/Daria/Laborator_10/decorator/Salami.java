package Laborator.Daria.Laborator_10.decorator;

public class Salami extends PizzaDecorator {
    public Salami(Pizza pizza) {
        super(pizza);
    }

    @Override
    public String getDescription() {
        return super.getDescription() + ", Salami";
    }

    @Override
    public double getCost() {
        return super.getCost() + 5.0;
    }
}
