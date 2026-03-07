package Laborator.Daria.Laborator_10.composite;

public class OperationNode implements Expression {
    private Expression left;
    private Expression right;
    private char operation;

    public OperationNode(Expression left, char operation, Expression right) {
        this.left = left;
        this.operation = operation;
        this.right = right;
    }

    @Override
    public double calculate() {
        switch (operation) {
            case '+':
                return left.calculate() + right.calculate();
            case '-':
                return left.calculate() - right.calculate();
            case '*':
                return left.calculate() * right.calculate();
            case '/':
                if (right.calculate() == 0) {
                    throw new ArithmeticException("Division by zero");
                }
                return left.calculate() / right.calculate();
            default:
                throw new UnsupportedOperationException("Operation not supported: " + operation);
        }
    }

    @Override
    public String print() {
        return "(" + left.print() + " " + operation + " " + right.print() + ")";
    }
}
