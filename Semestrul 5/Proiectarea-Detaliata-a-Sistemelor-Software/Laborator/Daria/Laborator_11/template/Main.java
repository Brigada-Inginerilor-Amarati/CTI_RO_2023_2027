package Laborator.Daria.Laborator_11.template;

public class Main {
    public static void main(String[] args) {
        System.out.println("--- Simple Worker (Base Class) ---");
        Worker simple = new Worker(5);
        int resultSimple = simple.makeStuff();
        System.out.println("Result: " + resultSimple);

        System.out.println("\n--- Specialized Worker ---");
        Worker specialized = new SpecializedWorker(5, 2);
        int resultSpecialized = specialized.makeStuff();
        System.out.println("Result: " + resultSpecialized);
    }
}
