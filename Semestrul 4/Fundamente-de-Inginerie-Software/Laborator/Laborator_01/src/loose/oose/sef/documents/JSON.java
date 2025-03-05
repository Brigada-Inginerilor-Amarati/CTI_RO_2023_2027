package loose.oose.sef.documents;

import java.util.ArrayList;
import java.util.List;

public class JSON extends Document {

    public JSON(List<String> content) {
        super(content);
    }

    @Override
    public List<String> analyze() {
        var result = new ArrayList<String>();

        for (String s : content) {
            if(!s.endsWith(":")){
                result.add(s);
            }
        }

        return result;
    }
}
