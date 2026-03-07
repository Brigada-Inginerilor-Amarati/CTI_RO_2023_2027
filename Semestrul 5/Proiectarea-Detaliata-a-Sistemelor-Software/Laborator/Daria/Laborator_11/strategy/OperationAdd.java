package Laborator.Daria.Laborator_11.strategy;

public class OperationAdd implements Strategy {
    @Override
    public int calculate(int a, int b) {
        return a + b;
    }
}
