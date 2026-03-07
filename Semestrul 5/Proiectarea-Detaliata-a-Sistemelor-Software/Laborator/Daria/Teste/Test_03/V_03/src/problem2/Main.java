
package problem2;

// Main demonstrates using one reference to run multiple jobs ordered.
// Jobs: c1, c2, c3
public class Main {
    public static void main(String[] args) {
        Cronjob c1 = new SimpleCronjob("c1");
        Cronjob c2 = new SimpleCronjob("c2");
        Cronjob c3 = new SimpleCronjob("c3");
        
        CronjobExecutor executor = new CronjobExecutor();

        System.out.println("--- Solution 1: Composite ---");
        CompositeCronjob composite = new CompositeCronjob();
        composite.addJob(c1);
        composite.addJob(c2);
        composite.addJob(c3);
        // Can be passed as single Cronjob reference
        executor.run(composite);


        System.out.println("\n--- Solution 2: Decorator ---");
        // Decorator implies wrapping. 
        // If we want c1 then c2 then c3.
        // We can create a chain.
        // Decorator typically wraps "what to do FIRST" or "adds behavior around it".
        // My impl: SequentialCronjobDecorator(current, next) runs current then next.
        
        // Let's build it backwards?
        // Wrapper(c1, Wrapper(c2, c3)) -> perform c1, then next.perform() -> perform c2, then next(c3).perform().
        
        // Note: My decorator takes (current, next).
        // Technically standard decorator wraps ONE object.
        // Typically: Decorator(Decorated).
        // If I make SequentialDecorator(next) wrapping 'current'?
        // The requirement says "Decorator pattern".
        // Standard Decorator adds functionality. Here functionality is "Run another job".
        
        // Let's usage:
        // Cronjob chain = new SequentialCronjobDecorator(c1, new SequentialCronjobDecorator(c2, c3));
        // Run chain -> runs c1, then runs the "next" (which runs c2, then c3).
        
        Cronjob chain = new SequentialCronjobDecorator(c1, 
                            new SequentialCronjobDecorator(c2, c3));
        
        executor.run(chain);
    }
}
