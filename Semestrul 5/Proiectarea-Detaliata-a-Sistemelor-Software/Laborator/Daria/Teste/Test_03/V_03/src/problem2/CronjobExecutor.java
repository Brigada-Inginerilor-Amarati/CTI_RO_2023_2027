
package problem2;

public class CronjobExecutor {
    public void run(Cronjob c) {
        // Can only execute a single object reference
        Context context = new Context(){};
        c.perform(context);
    }
}
