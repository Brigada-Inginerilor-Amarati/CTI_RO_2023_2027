
package problem2;

public class BasicBrochure extends Brochure {
    private Car car;

    public BasicBrochure(Car car) {
        this.car = car;
    }

    @Override
    public void print() {
        System.out.println("Brand: " + car.getBrand());
        System.out.println("Model: " + car.getModel());
    }
}
