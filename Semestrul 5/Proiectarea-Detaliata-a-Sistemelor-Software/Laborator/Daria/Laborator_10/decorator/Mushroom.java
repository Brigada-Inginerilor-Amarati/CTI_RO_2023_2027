package Laborator.Daria.Laborator_10.decorator;

public class Mushroom extends PizzaDecorator {
    public Mushroom(Pizza pizza) {
        super(pizza);
    }

    @Override
    public String getDescription() {
        return super.getDescription() + ", Mushroom";
    }

    @Override
    public double getCost() {
        return super.getCost() + 4.0;
    }
}
