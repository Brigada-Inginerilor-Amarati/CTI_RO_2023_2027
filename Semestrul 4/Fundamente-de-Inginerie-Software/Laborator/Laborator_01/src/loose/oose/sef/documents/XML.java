package loose.oose.sef.documents;

import java.util.ArrayList;
import java.util.List;

public class XML extends Document{

    public XML(List<String> content) {
        super(content);
    }

    @Override
    public List<String> analyze() {
        var result = new ArrayList<String>();
        // va stii ca var are un tip concret

        // content.for --> selectam ce vrem noi

        for (String s : content) {
            if(!s.startsWith("<")){
                result.add(s);
            }
        }

        return result;
    }
}
