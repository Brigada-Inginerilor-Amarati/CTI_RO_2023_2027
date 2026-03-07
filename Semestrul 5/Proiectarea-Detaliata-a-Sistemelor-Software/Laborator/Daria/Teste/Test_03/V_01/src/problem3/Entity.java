
package problem3;

public abstract class Entity {
    protected String name;

    public Entity(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public abstract double getSize();
    
    // Visitor acceptance
    public abstract void accept(Program program);
}
