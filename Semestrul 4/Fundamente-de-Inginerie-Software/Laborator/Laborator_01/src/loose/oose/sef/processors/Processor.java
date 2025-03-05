package loose.oose.sef.processors;

import loose.oose.sef.documents.Document;

import java.util.List;

public interface Processor {
    public  int process(List<Document> documents);
}
