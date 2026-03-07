
package problem2;

public abstract class BrochureDecorator extends Brochure {
    protected Brochure brochure;

    public BrochureDecorator(Brochure brochure) {
        this.brochure = brochure;
    }

    @Override
    public void print() {
        brochure.print();
    }
}
