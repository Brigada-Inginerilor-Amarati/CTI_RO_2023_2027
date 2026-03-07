import java.util.ArrayList;
import java.util.List;

public class CarsProvider {
    
    public static List<Car> getTestCars() {
        List<Car> cars = new ArrayList<>();
        
        // Create some test persons
        Person john = new Person("John", "Doe", 30);
        Person jane = new Person("Jane", "Smith", 25);
        Person bob = new Person("Bob", "Johnson", 35);
        Person alice = new Person("Alice", "Brown", 28);
        Person charlie = new Person("Charlie", "Wilson", 40);
        
        // Create test cars with various scenarios for comprehensive testing
        cars.add(new Car("Toyota", "Red", 2020, true, john));        // FaceLifted, 2020, has owner
        cars.add(new Car("Honda", "Blue", 2019, false, jane));        // Not faceLifted, 2019, has owner
        cars.add(new Car("BMW", "Black", 2021, true, bob));          // FaceLifted, 2021, has owner
        cars.add(new Car("Mercedes", "White", 2018, false, alice));  // Not faceLifted, 2018, has owner
        cars.add(new Car("Audi", "Black", 2022, true, charlie));      // FaceLifted, 2022, has owner
        cars.add(new Car("Toyota", "Green", 2020, true, null));      // FaceLifted, 2020, no owner
        cars.add(new Car("Honda", null, 2019, false, john));         // Not faceLifted, 2019, null color, has owner
        cars.add(new Car("BMW", "Silver", 2017, true, null));        // FaceLifted, 2017, no owner
        cars.add(new Car("Mercedes", "Black", 2023, false, jane));  // Not faceLifted, 2023, has owner
        cars.add(new Car("Audi", "Red", 2021, true, bob));          // FaceLifted, 2021, has owner
        
        return cars;
    }
    
    public static List<Car> getCarsWithFaceLifts() {
        List<Car> cars = new ArrayList<>();
        
        Person person1 = new Person("Alice", "Johnson", 32);
        Person person2 = new Person("Bob", "Smith", 28);
        
        cars.add(new Car("Toyota", "Blue", 2020, true, person1));
        cars.add(new Car("Honda", "Red", 2019, true, person2));
        cars.add(new Car("BMW", "Black", 2021, true, null));
        
        return cars;
    }
    
    public static List<Car> getCarsWithNullColors() {
        List<Car> cars = new ArrayList<>();
        
        Person person1 = new Person("Charlie", "Brown", 45);
        Person person2 = new Person("Diana", "Davis", 33);
        
        cars.add(new Car("Toyota", null, 2020, true, person1));
        cars.add(new Car("Honda", null, 2019, false, person2));
        cars.add(new Car("BMW", "Blue", 2021, true, null));
        
        return cars;
    }
}
