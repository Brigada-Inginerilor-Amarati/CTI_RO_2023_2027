public class Inmultire extends ExpresieBinara {

    public Inmultire(Expresie st, Expresie dr) {
        super(st,dr);
    }

    public void accept(Visitor v) {
        v.visitInmultire(this);
    }
    
}