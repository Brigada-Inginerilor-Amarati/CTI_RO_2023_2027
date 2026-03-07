package Laborator.Daria.Laborator_10.decorator;

public class ExtraCheese extends PizzaDecorator {   
    public ExtraCheese(Pizza pizza) {
        super(pizza);
    }

    @Override
    public String getDescription() {
        return super.getDescription() + ", Extra Cheese";
    }

    @Override
    public double getCost() {
        return super.getCost() + 5.0;
    }
}
