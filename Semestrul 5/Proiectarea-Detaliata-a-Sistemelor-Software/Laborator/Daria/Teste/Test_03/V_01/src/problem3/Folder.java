
package problem3;

import java.util.ArrayList;
import java.util.List;

public class Folder extends Entity {
    private List<Entity> children = new ArrayList<>();

    public Folder(String name) {
        super(name);
    }

    public void addEntity(Entity entity) {
        children.add(entity);
    }
    
    public List<Entity> getChildren() {
        return children;
    }

    @Override
    public double getSize() {
        double total = 0;
        for (Entity e : children) {
            total += e.getSize();
        }
        return total;
    }

    @Override
    public void accept(Program program) {
        program.visit(this);
    }
}
