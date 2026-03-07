
package problem2;

import java.util.List;

public class VariantDecorator extends BrochureDecorator {
    private Car car;
    private List<String> variants;

    public VariantDecorator(Brochure brochure, Car car, List<String> variants) {
        super(brochure);
        this.car = car;
        this.variants = variants;
    }

    @Override
    public void print() {
        System.out.println("Variants: " + String.join(", ", variants));
        super.print();
    }
}
