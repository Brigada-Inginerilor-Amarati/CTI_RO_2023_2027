public abstract class ExpresieBinara extends Expresie {

    private Expresie operandSt, operandDr;

    public ExpresieBinara(Expresie operandSr, Expresie operandDr) {
        this.operandSt = operandSr;
        this.operandDr = operandDr;
    }

    public Expresie operandSt() {
        return operandSt;
    }

    public Expresie operandDr() {
        return operandDr;
    }
    
}