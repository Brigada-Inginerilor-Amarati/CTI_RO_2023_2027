package loose.oose.sef;

import loose.oose.sef.documents.Document;
import loose.oose.sef.documents.JSON;
import loose.oose.sef.documents.XML;
import loose.oose.sef.processors.CompositeProcessor;
import loose.oose.sef.processors.Processor;
import loose.oose.sef.processors.SearchProcessor;

import java.util.List;

public class Main {
    //psvm quick command sau sout - print
    public static void main(String[] args) {
        Document xml = new XML(
                List.of("<tag>", "value1", "</tag1>", "<tag2>", "value2", "</tag2>")
        );
        Document json = new JSON(
                List.of("key1:", "value1", ",", "key2:", "value2", ",", "key3:", "value3")
        );

        Processor sp1 = new SearchProcessor("value1");
        Processor sp2 = new SearchProcessor("value2");
        Processor sp3 = new SearchProcessor("value3");
        Processor cp1 = new CompositeProcessor(List.of(sp1, sp2));
        Processor cp2 = new CompositeProcessor(List.of(cp1, sp3));

        int result = cp2.process(List.of(xml, json));

        System.out.println(result);
    }
}
