
package problem3;

public class SizeCalculatorProgram implements Program {
    private double totalSize = 0;

    @Override
    public void visit(File file) {
        totalSize += file.getSize();
    }

    @Override
    public void visit(Folder folder) {
        // Logic for folder: usually just sum of children.
        // The traversal logic can be inside the Visitor (here) or inside the Structure (Folder).
        // If we want FULL control here:
        for (Entity child : folder.getChildren()) {
            child.accept(this);
        }
        // Folder itself might have size 0 overhead.
    }

    @Override
    public void visit(SymbolicLink link) {
        // Link size logic. Should we follow the link?
        // "calculeaza dimensiunea unei entitati... capabil sa ruleze pe toate tipurile"
        // In OS, 'du' usually counts the link itself, or follows it.
        // Let's count just the link itself to avoid double counting if the target is also in the tree.
        totalSize += link.getSize(); 
    }
    
    public double getTotalSize() {
        return totalSize;
    }
}
