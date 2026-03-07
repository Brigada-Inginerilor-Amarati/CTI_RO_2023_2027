
package problem2;

public abstract class CronjobDecorator implements Cronjob {
    protected Cronjob wrappedJob;

    public CronjobDecorator(Cronjob wrappedJob) {
        this.wrappedJob = wrappedJob;
    }

    @Override
    public void perform(Context context) {
        wrappedJob.perform(context);
    }
}
