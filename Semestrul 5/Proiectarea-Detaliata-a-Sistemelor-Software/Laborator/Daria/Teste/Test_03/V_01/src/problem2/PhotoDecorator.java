
package problem2;

public class PhotoDecorator extends BrochureDecorator {
    private Car car;

    public PhotoDecorator(Brochure brochure, Car car) {
        super(brochure);
        this.car = car;
    }

    @Override
    public void print() {
        System.out.println("Photo: " + car.getProfilePictureUrl()); // Printing BEFORE other elements as per requirement example logic
        super.print();
    }
}
