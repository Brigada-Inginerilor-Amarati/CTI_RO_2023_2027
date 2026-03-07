
package problem2;

public class TypeDecorator extends BrochureDecorator {
    private Car car;

    public TypeDecorator(Brochure brochure, Car car) {
        super(brochure);
        this.car = car;
    }

    @Override
    public void print() {
        System.out.println("Type: " + car.getType());
        super.print();
    }
}
