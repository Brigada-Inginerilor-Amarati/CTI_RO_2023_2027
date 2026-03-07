import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class StreamInStreamExercises {

    private List<Car> carList;

    public StreamInStreamExercises(List<Car> carList) {
        this.carList = carList;
    }

    // ========== EXERCISE 1: NESTED STREAMS WITH FLATMAP ==========
    /*
     * Exercise 1: Get all unique colors from all cars, including cars with null colors
     * Hint: Use flatMap to flatten nested structures
     */
    public Set<String> getAllUniqueColors() {
        return carList.stream()
                .map(Car::getColor)
                .filter(Objects::nonNull)
                .collect(Collectors.toSet());
    }

    /*
     * Exercise 2: Get all first names of owners who have cars with faceLifts
     * Hint: Use flatMap to process nested collections
     */
    public List<String> getFirstNamesOfOwnersWithFaceLiftedCars() {
        return carList.stream()
                .filter(Car::isFaceLifted)
                .filter(car -> car.getOwner() != null)
                .map(car -> car.getOwner().getFirstName())
                .distinct()
                .collect(Collectors.toList());
    }

    // ========== EXERCISE 3: STREAMS WITH OPTIONAL ==========
    /*
     * Exercise 3: Find the brand of the car owned by the youngest person
     * Hint: Use Optional and flatMap
     */
    public Optional<String> getBrandOfCarOwnedByYoungestPerson() {
        return carList.stream()
                .filter(car -> car.getOwner() != null)
                .min(Comparator.comparingInt(car -> car.getOwner().getAge()))
                .map(Car::getBrand);
    }

    // ========== EXERCISE 4: NESTED STREAMS WITH COLLECTIONS ==========
    /*
     * Exercise 4: Group cars by brand, then for each brand get the average year
     * Hint: Use groupingBy and then mapping
     */
    public Map<String, Double> getAverageYearByBrand() {
        return carList.stream()
                .filter(car -> car.getBrand() != null)
                .collect(Collectors.groupingBy(
                        Car::getBrand,
                        Collectors.averagingInt(Car::getYear)
                ));
    }

    // ========== EXERCISE 5: COMPLEX NESTED STREAMS ==========
    /*
     * Exercise 5: Get all owners who have multiple cars, with their car counts
     * Hint: Use groupingBy, filtering, and mapping
     */
    public Map<Person, Long> getOwnersWithMultipleCars() {
        return carList.stream()
                .filter(car -> car.getOwner() != null)
                .collect(Collectors.groupingBy(
                        Car::getOwner,
                        Collectors.counting()
                ))
                .entrySet().stream()
                .filter(entry -> entry.getValue() > 1)
                .collect(Collectors.toMap(
                        Map.Entry::getKey,
                        Map.Entry::getValue
                ));
    }

    // ========== EXERCISE 6: STREAMS WITH CUSTOM COLLECTORS ==========
    /*
     * Exercise 6: Get the most popular color (color with most cars)
     * Hint: Use groupingBy, counting, and maxBy
     */
    public Optional<String> getMostPopularColor() {
        return carList.stream()
                .filter(car -> car.getColor() != null)
                .collect(Collectors.groupingBy(
                        Car::getColor,
                        Collectors.counting()
                ))
                .entrySet().stream()
                .max(Map.Entry.comparingByValue())
                .map(Map.Entry::getKey);
    }

    // ========== EXERCISE 7: NESTED STREAMS WITH MULTIPLE CONDITIONS ==========
    /*
     * Exercise 7: Get all cars that are newer than the average year of their brand
     * Hint: Use multiple streams and intermediate collections
     */
    public List<Car> getCarsNewerThanBrandAverage() {
        Map<String, Double> brandAverages = getAverageYearByBrand();
        
        return carList.stream()
                .filter(car -> car.getBrand() != null)
                .filter(car -> brandAverages.containsKey(car.getBrand()))
                .filter(car -> car.getYear() > brandAverages.get(car.getBrand()))
                .collect(Collectors.toList());
    }

    // ========== EXERCISE 8: STREAMS WITH PARTITIONING ==========
    /*
     * Exercise 8: Partition cars into two groups: owned vs unowned, then get statistics
     * Hint: Use partitioningBy and downstream collectors
     */
    public Map<Boolean, Map<String, Object>> getCarOwnershipStatistics() {
        return carList.stream()
                .collect(Collectors.partitioningBy(
                        car -> car.getOwner() != null,
                        Collectors.collectingAndThen(
                                Collectors.toList(),
                                cars -> {
                                    Map<String, Object> stats = new HashMap<>();
                                    stats.put("count", cars.size());
                                    stats.put("averageYear", cars.stream()
                                            .mapToInt(Car::getYear)
                                            .average()
                                            .orElse(0.0));
                                    stats.put("brands", cars.stream()
                                            .map(Car::getBrand)
                                            .filter(Objects::nonNull)
                                            .distinct()
                                            .collect(Collectors.toList()));
                                    return stats;
                                }
                        )
                ));
    }

    // ========== EXERCISE 9: STREAMS WITH REDUCE ==========
    /*
     * Exercise 9: Find the car with the highest value (year * age of owner)
     * Hint: Use reduce with custom comparator
     */
    public Optional<Car> getCarWithHighestValue() {
        return carList.stream()
                .filter(car -> car.getOwner() != null)
                .reduce((car1, car2) -> {
                    int value1 = car1.getYear() * car1.getOwner().getAge();
                    int value2 = car2.getYear() * car2.getOwner().getAge();
                    return value1 > value2 ? car1 : car2;
                });
    }

    // ========== EXERCISE 10: COMPLEX NESTED STREAMS ==========
    /*
     * Exercise 10: Get a map where keys are age ranges and values are lists of car brands
     * owned by people in that age range
     * Hint: Use groupingBy with custom classifier and downstream collector
     */
    public Map<String, List<String>> getCarBrandsByAgeRange() {
        return carList.stream()
                .filter(car -> car.getOwner() != null)
                .collect(Collectors.groupingBy(
                        car -> {
                            int age = car.getOwner().getAge();
                            if (age < 30) return "Young (0-29)";
                            else if (age < 50) return "Middle-aged (30-49)";
                            else return "Senior (50+)";
                        },
                        Collectors.mapping(
                                car -> car.getBrand(),
                                Collectors.toList()
                        )
                ));
    }

    // ========== EXERCISE 11: STREAMS WITH CUSTOM STREAM OPERATIONS ==========
    /*
     * Exercise 11: Get all unique combinations of brand and color
     * Hint: Use flatMap with custom stream operations
     */
    public List<String> getAllBrandColorCombinations() {
        return carList.stream()
                .filter(car -> car.getBrand() != null && car.getColor() != null)
                .map(car -> car.getBrand() + " " + car.getColor())
                .distinct()
                .sorted()
                .collect(Collectors.toList());
    }

    // ========== EXERCISE 12: STREAMS WITH MULTIPLE COLLECTORS ==========
    /*
     * Exercise 12: Get comprehensive statistics for each brand
     * Hint: Use groupingBy with multiple downstream collectors
     */
    public Map<String, Map<String, Object>> getBrandStatistics() {
        return carList.stream()
                .filter(car -> car.getBrand() != null)
                .collect(Collectors.groupingBy(
                        Car::getBrand,
                        Collectors.collectingAndThen(
                                Collectors.toList(),
                                cars -> {
                                    Map<String, Object> stats = new HashMap<>();
                                    stats.put("count", cars.size());
                                    stats.put("averageYear", cars.stream()
                                            .mapToInt(Car::getYear)
                                            .average()
                                            .orElse(0.0));
                                    stats.put("colors", cars.stream()
                                            .map(Car::getColor)
                                            .filter(Objects::nonNull)
                                            .distinct()
                                            .collect(Collectors.toList()));
                                    stats.put("faceLiftedCount", cars.stream()
                                            .mapToInt(car -> car.isFaceLifted() ? 1 : 0)
                                            .sum());
                                    return stats;
                                }
                        )
                ));
    }

    // ========== HELPER METHODS ==========
    
    /*
     * Helper method to create a stream of all possible car combinations
     */
    public Stream<String> getAllPossibleCarCombinations() {
        return carList.stream()
                .flatMap(car1 -> carList.stream()
                        .filter(car2 -> !car1.equals(car2))
                        .map(car2 -> car1.getBrand() + " vs " + car2.getBrand()))
                .distinct();
    }

    /*
     * Helper method to get cars grouped by multiple criteria
     */
    public Map<String, Map<String, List<Car>>> getCarsGroupedByBrandAndColor() {
        return carList.stream()
                .filter(car -> car.getBrand() != null && car.getColor() != null)
                .collect(Collectors.groupingBy(
                        Car::getBrand,
                        Collectors.groupingBy(Car::getColor)
                ));
    }
}
