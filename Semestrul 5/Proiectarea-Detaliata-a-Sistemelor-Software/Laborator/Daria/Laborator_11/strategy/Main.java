package Laborator.Daria.Laborator_11.strategy;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter first number: ");
        int a = scanner.nextInt();

        System.out.print("Enter second number: ");
        int b = scanner.nextInt();

        System.out.print("Enter operation (+, -, *, /): ");
        String operation = scanner.next();

        Context context = null;

        switch (operation) {
            case "+":
                context = new Context(new OperationAdd());
                break;
            case "-":
                context = new Context(new OperationSubtract());
                break;
            case "*":
                context = new Context(new OperationMultiply());
                break;
            case "/":
                context = new Context(new OperationDivide());
                break;
            default:
                System.out.println("Invalid operation");
                return;
        }

        System.out.println("Result: " + context.executeStrategy(a, b));
    }
}
