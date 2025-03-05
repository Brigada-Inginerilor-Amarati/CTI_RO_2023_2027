class Suma extends ExpresieBinara {

    public Suma(Expresie st, Expresie dr) {
        super(st,dr);
    }

    public void accept(Visitor v) {
        v.visit(this);
    }

}