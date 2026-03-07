
package problem3;

// Bonus type for extensibility demo
public class ConfigurationFile extends ProjectFile {
    public ConfigurationFile(String name) {
        super(name);
    }

    @Override
    public boolean isLeaf() {
        return true;
    }

    @Override
    public Object getContent() {
        return "Config Data";
    }

    @Override
    public void accept(AnalysisVisitor visitor) {
        visitor.visit(this);
    }
}
