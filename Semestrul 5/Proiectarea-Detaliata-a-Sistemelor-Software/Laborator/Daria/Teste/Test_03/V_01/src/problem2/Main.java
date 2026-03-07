
package problem2;

import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        Car car = new Car("SUV", "Tesla", "Model X", 80000, 120000, "http://tesla.com/img/modelx.jpg");

        // Order: Photo -> Price -> Type -> Variants -> Brand/Model
        // Construction: Photo( Price( Type( Variants( Basic ) ) ) )
        
        Brochure b = new BasicBrochure(car);
        b = new VariantDecorator(b, car, Arrays.asList("Autopilot", "Long Range", "Plaid"));
        b = new TypeDecorator(b, car);
        b = new PriceDecorator(b, car);
        b = new PhotoDecorator(b, car);

        b.print();
    }
}
