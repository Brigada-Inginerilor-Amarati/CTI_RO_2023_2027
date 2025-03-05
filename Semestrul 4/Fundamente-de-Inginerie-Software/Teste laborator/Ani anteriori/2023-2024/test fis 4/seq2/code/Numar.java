public class Numar extends Expresie {

    private int literal;

    public Numar(int literal) {
        this.literal = literal;
    }

    public int getNumar() {
        return literal;
    }

    public void accept(Visitor v) {
        v.visit(this);
    }
}