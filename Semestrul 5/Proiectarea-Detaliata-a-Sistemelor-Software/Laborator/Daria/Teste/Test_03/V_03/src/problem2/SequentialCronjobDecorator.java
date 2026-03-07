
package problem2;

public class SequentialCronjobDecorator extends CronjobDecorator {
    private Cronjob nextJob;

    public SequentialCronjobDecorator(Cronjob currentJob, Cronjob nextJob) {
        super(currentJob);
        this.nextJob = nextJob;
    }

    @Override
    public void perform(Context context) {
        super.perform(context);
        nextJob.perform(context);
    }
}
