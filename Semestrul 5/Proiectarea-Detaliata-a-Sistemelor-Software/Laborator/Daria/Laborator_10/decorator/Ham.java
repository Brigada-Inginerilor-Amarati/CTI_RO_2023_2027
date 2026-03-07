package Laborator.Daria.Laborator_10.decorator;

public class Ham extends PizzaDecorator {
    public Ham(Pizza pizza) {
        super(pizza);
    }

    @Override
    public String getDescription() {
        return super.getDescription() + ", Ham";
    }

    @Override
    public double getCost() {
        return super.getCost() + 5.0;
    }
}
