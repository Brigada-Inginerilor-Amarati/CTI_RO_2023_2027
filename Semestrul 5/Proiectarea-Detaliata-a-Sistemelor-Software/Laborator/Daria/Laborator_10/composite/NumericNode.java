package Laborator.Daria.Laborator_10.composite;

public class NumericNode implements Expression {
    private double value;

    public NumericNode(double value) {
        this.value = value;
    }

    @Override
    public double calculate() {
        return value;
    }

    @Override
    public String print() {
        if (value == (long) value) {
            return String.format("%d", (long) value);
        }
        return String.valueOf(value);
    }
}
