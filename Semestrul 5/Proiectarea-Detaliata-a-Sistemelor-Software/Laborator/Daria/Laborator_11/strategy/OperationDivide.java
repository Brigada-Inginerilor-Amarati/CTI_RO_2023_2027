package Laborator.Daria.Laborator_11.strategy;

public class OperationDivide implements Strategy {
    @Override
    public int calculate(int a, int b) {
        if (b == 0) {
            throw new ArithmeticException("Division by zero");
        }
        return a / b;
    }
}
