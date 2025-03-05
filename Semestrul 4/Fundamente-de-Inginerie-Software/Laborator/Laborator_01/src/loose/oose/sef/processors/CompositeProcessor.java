package loose.oose.sef.processors;

import loose.oose.sef.documents.Document;

import java.util.List;

public class CompositeProcessor implements Processor {
    private List<Processor> processors;

    public CompositeProcessor(List<Processor> processors) {
        this.processors = processors;
    }

    @Override
    public int process(List<Document> documents) {
        int counter = 0;

        for(Processor p : processors){
            counter += p.process(documents);
        }

        return counter;
    }
}
