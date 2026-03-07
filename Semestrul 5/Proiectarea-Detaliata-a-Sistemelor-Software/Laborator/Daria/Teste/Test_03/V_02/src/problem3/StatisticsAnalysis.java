
package problem3;

public class StatisticsAnalysis implements AnalysisVisitor {
    @Override
    public void visit(File file) {
        System.out.println("Analyzing File: " + file.getName() + ", Length: " + ((String)file.getContent()).length());
    }

    @Override
    public void visit(Folder folder) {
        System.out.println("Analyzing Folder: " + folder.getName());
        for (ProjectFile child : folder.getChildren()) {
            child.accept(this);
        }
    }

    @Override
    public void visit(ConfigurationFile configFile) {
        System.out.println("Analyzing Config: " + configFile.getName());
    }
}
