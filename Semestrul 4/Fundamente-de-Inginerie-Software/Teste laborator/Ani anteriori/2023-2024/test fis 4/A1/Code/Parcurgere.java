public class Parcurgere implements Visitor {
                
    public void visitNumar(Numar n) {
        System.out.print(n.getNumar());
    }

    public void visitSuma(Suma s) {
        s.operandSt().accept(this);
        s.operandDr().accept(this);
        System.out.print('+');
    }
    
    public void visitInmultire(Inmultire i) {
        i.operandSt().accept(this);
        i.operandDr().accept(this);
        System.out.print('*');   
    }   
}