
package problem3;

public abstract class ProjectFile {
    protected String name;

    public ProjectFile(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public abstract boolean isLeaf();
    
    // Per requirement: getContent() returns Object
    // Bonus Question addresses this design choice.
    public abstract Object getContent();
    
    public abstract void accept(AnalysisVisitor visitor);
}
