import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Manager {
    private List<Car> carList;
    
    public Manager(List<Car> carList) {
        this.carList = carList;
    }
    
    /*
     * returns a report of the cars it contains given some parameters
     */
    public String getSomeCarDetails(int year, String brand, String color) {
        Map<Person, Car> firstResult = firstMethod();
        Collection<String> secondResult = secondMethod(year);
        String thirdResult = thirdMethod();
        double forthResult = forthMethod(brand);
        long fifthMethodResult = fifthMethod(year);
        Person sixthResult = sixthMethod(brand, color);
        Map<String, List<Car>> stringListMap = seventhMethod();

        return "" + firstResult +
                "\n" + secondResult +
                "\n" + thirdResult +
                "\n" + forthResult +
                "\n" + fifthMethodResult +
                "\n" + sixthResult +
                "\n" + stringListMap;
    }
    /*
     * returns a map that has the owner as key and the car as value for each car in the carList
     * ATTENTION!!! In this example a Person can only own one car,
     * but a car can be owned by a Person, or can be "free of owner" (owner == null)
     */
    protected Map<Person, Car> firstMethod() {
        return carList.stream()
                .filter(car -> car.getOwner() != null)
                .collect(Collectors.toMap(
                        Car::getOwner,
                        Function.identity()
                ));
    }
    
    /*
     * returns a collection (List/Set) with the distinct first names of the owners of cars
     * that have faceLifts and are created in the year sent as parameter
     */
    protected Collection<String> secondMethod(int year) {
        return carList.stream()
                .filter(car -> car.isFaceLifted() && car.getOwner() != null && car.getYear() == year)
                .map(car -> car.getOwner().getFirstName())
                .collect(Collectors.toSet());
    }
    
    /*
     * returns the full name (firstName + " " + lastName) of the owner of the newest black car,
     * or throws a NoSuchPersonException if it doesn't find one (Hint: use Optional
     * operations)
     */
    protected String thirdMethod() {
        if (carList == null) {
            throw new NoSuchPersonException("No black car found");
        }
        
        return carList.stream()
                .filter(car -> car.getColor() != null && car.getColor().equals("Black"))
                .filter(car -> car.getOwner() != null)
                .max(Comparator.comparingInt(Car::getYear))
                .map(Car::getOwner)
                .map(owner -> owner.getFirstName() + " " + owner.getLastName())
                .orElseThrow(() -> new NoSuchPersonException("No black car found"));
    }
    
    /*
     * returns the average age of all the owners of cars with a brand,
     * or 0 if no such cars exist (Hint: use Optional operations)
     * ATTENTION!!! for this example, all people have ages
     */
    protected double forthMethod(String brand) {
        return carList.stream()
                .filter(car -> car.getBrand() != null && car.getBrand().equals(brand))
                .map(Car::getOwner)
                .filter(Objects::nonNull)
                .mapToInt(Person::getAge)
                .average()
                .orElse(0.);
    }
    
    /*
     * returns the number of cars created after the year sent as parameter
     * and sets the "faceLifted" flag for all cars to true
     */
    protected long fifthMethod(int year) {
        return carList.stream()
                .filter(car -> car.getYear() > year)
                .peek(car -> car.setFaceLifted(true))
                .count();
    }
    
    /*
     * returns the owner of the oldest car for the specified brand and color, or a new Person if
     * there is no such person
     * (Hint: use Optional operations)
     */
    protected Person sixthMethod(String brand, String color) {
        return carList.stream()
                .filter(car -> car.getBrand() != null && car.getBrand().equals(brand))
                .filter(car -> car.getColor() != null && car.getColor().equals(color))
                .filter(car -> car.getOwner() != null)
                .min(Comparator.comparingInt(Car::getYear))
                .map(Car::getOwner)
                .orElse(new Person("Unknown", "Person", 0));
    }
    
    /*
     * returns a map with all the cars grouped by their color.
     * ATTENTION!!! some cars might have the color field null!!!
     */
    protected Map<String, List<Car>> seventhMethod() {
        return carList.stream()
                .filter(car -> car.getColor() != null)
                .collect(Collectors.groupingBy(Car::getColor));
    }
}
