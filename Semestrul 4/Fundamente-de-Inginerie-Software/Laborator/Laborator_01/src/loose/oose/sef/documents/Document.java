package loose.oose.sef.documents;


import java.util.List;

public abstract class Document {
    protected List<String> content;

    public Document(List<String> content) {
        this.content = content;
    }

    public abstract List<String> analyze();
}
