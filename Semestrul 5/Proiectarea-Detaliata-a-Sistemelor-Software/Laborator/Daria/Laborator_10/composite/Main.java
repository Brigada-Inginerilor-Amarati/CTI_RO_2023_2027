package Laborator.Daria.Laborator_10.composite;

public class Main {
    public static void main(String[] args) {
        Expression ex1 = new NumericNode(3);
        System.out.println("Ex1: " + ex1.print() + " = " + ex1.calculate());

        Expression ex2 = new OperationNode(new NumericNode(3), '+', new NumericNode(7));
        System.out.println("Ex2: " + ex2.print() + " = " + ex2.calculate());

        Expression ex3 = new OperationNode(new NumericNode(3), '*', new NumericNode(7));
        System.out.println("Ex3: " + ex3.print() + " = " + ex3.calculate());

        Expression ex4 = new OperationNode(
            new NumericNode(3), 
            '*', 
            new OperationNode(new NumericNode(7), '-', new NumericNode(5))
        );
        System.out.println("Ex4: " + ex4.print() + " = " + ex4.calculate());
        
        Expression ex5 = new OperationNode(
            new OperationNode(
                new NumericNode(3), 
                '+', 
                new OperationNode(new NumericNode(7), '+', new NumericNode(5))
            ),
            '*',
            new NumericNode(3)
        );
        System.out.println("Ex5: " + ex5.print() + " = " + ex5.calculate());
    }
}
