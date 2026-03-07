
package problem3;

public class File extends ProjectFile {
    private String content;

    public File(String name, String content) {
        super(name);
        this.content = content;
    }

    @Override
    public boolean isLeaf() {
        return true;
    }

    @Override
    public Object getContent() {
        return content;
    }

    @Override
    public void accept(AnalysisVisitor visitor) {
        visitor.visit(this);
    }
}
