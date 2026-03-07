
package problem3;

public interface AnalysisVisitor {
    void visit(File file);
    void visit(Folder folder);
    
    // For extensibility example (Bonus)
    void visit(ConfigurationFile configFile);
}
