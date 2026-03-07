
package problem3;

public class Main {
    public static void main(String[] args) {
        Folder root = new Folder("root");
        File src1 = new File("src1.java", "public class...");
        File src2 = new File("src2.java", "import java...");
        ConfigurationFile config = new ConfigurationFile("app.config");

        root.addFile(src1);
        root.addFile(src2);
        root.addFile(config);

        StatisticsAnalysis stats = new StatisticsAnalysis();
        root.accept(stats);
    }
}
