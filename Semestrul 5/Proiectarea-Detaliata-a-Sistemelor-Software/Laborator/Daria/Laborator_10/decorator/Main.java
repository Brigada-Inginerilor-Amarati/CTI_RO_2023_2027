package Laborator.Daria.Laborator_10.decorator;

public class Main {
    public static void main(String[] args) {
        Pizza pizza = new SimplePizza();
        System.out.println(pizza.getDescription() + " Cost: " + pizza.getCost() + " RON");

        Pizza hamPizza = new Ham(new SimplePizza());
        System.out.println(hamPizza.getDescription() + " Cost: " + hamPizza.getCost() + " RON");

        Pizza complexPizza = new Salami(new Mushroom(new ExtraCheese(new Ham(new SimplePizza()))));
        System.out.println(complexPizza.getDescription() + " Cost: " + complexPizza.getCost() + " RON");
        
        Pizza customPizza = new ExtraCheese(new Mushroom(new SimplePizza()));
        System.out.println(customPizza.getDescription() + " Cost: " + customPizza.getCost() + " RON");
    }
}
