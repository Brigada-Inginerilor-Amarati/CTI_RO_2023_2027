package loose.oose.sef.processors;

import loose.oose.sef.documents.Document;

import java.util.List;
import java.util.Objects;

public class SearchProcessor implements Processor {
    private String query;

    // inteliij stie sa genereze constructor

    // right click -> generate -> constructor -> select query -> ok


    public SearchProcessor(String query) {
        this.query = query;
    }

    @Override
    public int process(List<Document> documents) {
        int counter = 0;

        for(Document doc : documents){
            for (String s : doc.analyze()) {
                if(Objects.equals(s, query)){
                    counter++;
                }
            }
        }

        return counter;
    }


    public String getQuery(){
        return query;
    }
}
