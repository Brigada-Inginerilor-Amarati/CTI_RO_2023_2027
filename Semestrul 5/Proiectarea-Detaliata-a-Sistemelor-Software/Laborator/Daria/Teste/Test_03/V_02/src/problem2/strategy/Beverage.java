
package problem2.strategy;

public class Beverage {
    private PreparationStrategy strategy;

    public Beverage(PreparationStrategy strategy) {
        this.strategy = strategy;
    }

    public void setStrategy(PreparationStrategy strategy) {
        this.strategy = strategy;
    }

    public void fixDrink() {
        boilWater();
        // Strategy handles the specific parts. 
        // Note: To truly avoid duplication, common parts should be here.
        // But if steps are interleaved (like pourInCup happening in middle), 
        // Strategy might need to handle the 'middle' distinct parts or the context passes control.
        // Simple approach: Delegate distinct logic to strategy.
        
        // However, standard Strategy pattern usually encapsulates the WHOLE algorithm or a specific behaviors.
        // If we want to keep boilWater and serve here:
        if (strategy != null) {
            strategy.prepare(); // This would contain brew + condiments
        }
        stearAndServe();
    }

    private void boilWater() {
        System.out.println("Boiling water");
    }

    private void stearAndServe() {
        System.out.println("Stearing and serving");
    }
}
