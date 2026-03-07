
package problem3;

public class SymbolicLink extends Entity {
    private Entity target;

    public SymbolicLink(String name, Entity target) {
        super(name);
        this.target = target;
    }
    
    public Entity getTarget() {
        return target;
    }

    @Override
    public double getSize() {
        // Symbolic link size is negligible or size of path, 
        // but for recursion safety let's say it's just the reference size (e.g., 1)
        // avoiding infinite loops if we simply delegates blindly. 
        // Requirement implies calculating size of the VIEWED system if we traverse?
        // Or just the overhead? Let's assume 1.
        return 1.0; 
    }

    @Override
    public void accept(Program program) {
        program.visit(this);
    }
}
