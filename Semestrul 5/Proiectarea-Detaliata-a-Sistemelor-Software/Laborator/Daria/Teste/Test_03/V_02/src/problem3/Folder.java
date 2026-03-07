
package problem3;

import java.util.ArrayList;
import java.util.List;

public class Folder extends ProjectFile {
    private List<ProjectFile> children = new ArrayList<>();

    public Folder(String name) {
        super(name);
    }

    public void addFile(ProjectFile file) {
        children.add(file);
    }

    @Override
    public boolean isLeaf() {
        return false;
    }

    @Override
    public Object getContent() {
        return children;
    }
    
    // Helper for visitor to get children cleanly without casting Object
    public List<ProjectFile> getChildren() {
        return children;
    }

    @Override
    public void accept(AnalysisVisitor visitor) {
        visitor.visit(this);
    }
}
