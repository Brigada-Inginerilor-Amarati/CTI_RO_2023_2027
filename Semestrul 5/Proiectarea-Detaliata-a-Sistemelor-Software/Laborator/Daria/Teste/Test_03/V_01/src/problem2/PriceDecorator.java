
package problem2;

public class PriceDecorator extends BrochureDecorator {
    private Car car;

    public PriceDecorator(Brochure brochure, Car car) {
        super(brochure);
        this.car = car;
    }

    @Override
    public void print() {
        System.out.println("Price Range: " + car.getMinPrice() + " - " + car.getMaxPrice());
        super.print();
    }
}
