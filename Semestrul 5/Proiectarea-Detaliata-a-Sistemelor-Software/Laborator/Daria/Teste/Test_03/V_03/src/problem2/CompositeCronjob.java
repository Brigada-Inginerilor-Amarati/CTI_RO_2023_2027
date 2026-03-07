
package problem2;

import java.util.ArrayList;
import java.util.List;

public class CompositeCronjob implements Cronjob {
    private List<Cronjob> jobs = new ArrayList<>();

    public void addJob(Cronjob job) {
        jobs.add(job);
    }

    @Override
    public void perform(Context context) {
        for (Cronjob job : jobs) {
            job.perform(context);
        }
    }
}
