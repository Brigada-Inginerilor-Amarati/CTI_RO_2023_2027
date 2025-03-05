public class Afisare implements Visitor {
                
    public void visit(Numar n) {
        System.out.print(n.getNumar());
    }

    public void visit(Suma s) {
        s.operandSt().accept(this);
        s.operandDr().accept(this);
        System.out.print('+');
    }
    
    public void visit(Inmultire i) {
        i.operandSt().accept(this);
        i.operandDr().accept(this);
        System.out.print('*'); 
    }   
}