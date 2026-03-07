
package problem3;

public class Main {
    public static void main(String[] args) {
        // Create structure to test Bonus
        Folder fol1 = new Folder("fol1");
        File f1 = new File("fol1/f1", "content1"); // size 8
        File f2 = new File("fol1/f2", "content22"); // size 9
        File f3 = new File("fol1/f3", "content333"); // size 10
        
        fol1.addEntity(f1);
        fol1.addEntity(f2);
        fol1.addEntity(f3);
        
        Folder subfol = new Folder("fol1/subfol");
        // Link to f4. f4 must exist in same folder as link? "aflat in acelasi folder" -> "link aflat in subfol, f4 in subfol" or "f4 in fol1"?
        // Text: "un subfolder (subfol) care contine un link simbolic care sa 'pointeze' catre un al patrulea fisier (f4), aflat in acelasi folder"
        // Interpretation: f4 is in 'subfol' along with the link.
        
        File f4 = new File("fol1/subfol/f4", "data4"); // size 5
        SymbolicLink link = new SymbolicLink("fol1/subfol/linkToF4", f4);
        
        subfol.addEntity(f4);
        subfol.addEntity(link); // link size 1
        
        fol1.addEntity(subfol);
        
        // Calculate size of fol1 using the Program
        SizeCalculatorProgram calc = new SizeCalculatorProgram();
        fol1.accept(calc);
        
        System.out.println("Total Size of fol1: " + calc.getTotalSize());
        
        // Expected: f1(8) + f2(9) + f3(10) + subfol( f4(5) + link(1) ) = 27 + 6 = 33.
    }
}
