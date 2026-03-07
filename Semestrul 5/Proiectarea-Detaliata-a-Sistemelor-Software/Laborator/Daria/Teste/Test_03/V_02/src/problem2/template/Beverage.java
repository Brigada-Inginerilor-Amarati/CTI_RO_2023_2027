
package problem2.template;

public abstract class Beverage {
    
    // Template Method: Defines the skeleton of the algorithm
    public final void fixDrink() {
        boilWater();
        brew();         // Abstract step (grindBeans / putTeaInfusion)
        pourInCup();
        addCondiments(); // Abstract step (addMilk+Sugar / addLemon+Honey)
        stearAndServe();
        // Note: The prompt listed specific steps:
        // Coffee: boilWater, grindBeans, pourInCup, addMilk, addSugar, addFoam, stearAndServe
        // Tea: boilWater, putTeaInfusion, pourInCup, addLemon, addHoney, stearAndServe
    }

    protected void boilWater() {
        System.out.println("Boiling water");
    }

    protected void pourInCup() {
        System.out.println("Pouring into cup");
    }

    protected void stearAndServe() {
        System.out.println("Stearing and serving");
    }

    // Abstract methods to be implemented by subclasses
    protected abstract void brew();
    protected abstract void addCondiments();
}
