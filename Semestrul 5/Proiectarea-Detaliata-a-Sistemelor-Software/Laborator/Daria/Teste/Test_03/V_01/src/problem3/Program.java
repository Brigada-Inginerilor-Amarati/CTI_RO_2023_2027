
package problem3;

public interface Program {
    void visit(File file);
    void visit(Folder folder);
    void visit(SymbolicLink link);
}
