
package problem2;

public class SimpleCronjob implements Cronjob {
    private String name;

    public SimpleCronjob(String name) {
        this.name = name;
    }

    @Override
    public void perform(Context context) {
        System.out.println("Executing job: " + name);
    }
}
