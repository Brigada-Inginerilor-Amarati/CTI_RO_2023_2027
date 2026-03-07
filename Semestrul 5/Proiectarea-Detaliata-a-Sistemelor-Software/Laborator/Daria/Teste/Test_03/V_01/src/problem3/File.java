
package problem3;

public class File extends Entity {
    private String content;

    public File(String name, String content) {
        super(name);
        this.content = content;
    }

    @Override
    public double getSize() {
        return content.length();
    }

    @Override
    public void accept(Program program) {
        program.visit(this);
    }
}
