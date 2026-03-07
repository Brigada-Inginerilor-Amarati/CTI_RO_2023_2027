import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class SimpleStreamExercises {

    private List<Car> carList;

    public SimpleStreamExercises(List<Car> carList) {
        this.carList = carList;
    }

    // ========== BASIC STREAM IN STREAM EXERCISES ==========

    /*
     * Exercise 1: Get all unique colors using flatMap
     */
    public Set<String> getAllColors() {
        return carList.stream()
                .map(Car::getColor)
                .filter(Objects::nonNull)
                .collect(Collectors.toSet());
    }

    /*
     * Exercise 2: Get all first names of owners
     */
    public List<String> getAllOwnerFirstNames() {
        return carList.stream()
                .filter(car -> car.getOwner() != null)
                .map(car -> car.getOwner().getFirstName())
                .collect(Collectors.toList());
    }

    /*
     * Exercise 3: Get cars grouped by brand
     */
    public Map<String, List<Car>> getCarsByBrand() {
        return carList.stream()
                .filter(car -> car.getBrand() != null)
                .collect(Collectors.groupingBy(Car::getBrand));
    }

    /*
     * Exercise 4: Get average year by brand
     */
    public Map<String, Double> getAverageYearByBrand() {
        return carList.stream()
                .filter(car -> car.getBrand() != null)
                .collect(Collectors.groupingBy(
                        Car::getBrand,
                        Collectors.averagingInt(Car::getYear)
                ));
    }

    /*
     * Exercise 5: Get owners with multiple cars
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

    /*
     * Exercise 6: Get most popular color
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

    /*
     * Exercise 7: Get cars newer than average year
     */
    public List<Car> getCarsNewerThanAverage() {
        double averageYear = carList.stream()
                .mapToInt(Car::getYear)
                .average()
                .orElse(0.0);

        return carList.stream()
                .filter(car -> car.getYear() > averageYear)
                .collect(Collectors.toList());
    }

    /*
     * Exercise 8: Get cars grouped by color, then by brand
     */
    public Map<String, Map<String, List<Car>>> getCarsByColorAndBrand() {
        return carList.stream()
                .filter(car -> car.getColor() != null && car.getBrand() != null)
                .collect(Collectors.groupingBy(
                        Car::getColor,
                        Collectors.groupingBy(Car::getBrand)
                ));
    }

    /*
     * Exercise 9: Get all possible brand-color combinations
     */
    public List<String> getAllBrandColorCombinations() {
        return carList.stream()
                .filter(car -> car.getBrand() != null && car.getColor() != null)
                .map(car -> car.getBrand() + " " + car.getColor())
                .distinct()
                .sorted()
                .collect(Collectors.toList());
    }

    /*
     * Exercise 10: Get statistics for each brand
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
                                    return stats;
                                }
                        )
                ));
    }

    // ========== ADVANCED STREAM IN STREAM EXERCISES ==========

    /*
     * Exercise 11: Get cars that are newer than the average of their brand
     */
    public List<Car> getCarsNewerThanBrandAverage() {
        Map<String, Double> brandAverages = getAverageYearByBrand();
        
        return carList.stream()
                .filter(car -> car.getBrand() != null)
                .filter(car -> brandAverages.containsKey(car.getBrand()))
                .filter(car -> car.getYear() > brandAverages.get(car.getBrand()))
                .collect(Collectors.toList());
    }

    /*
     * Exercise 12: Get owners grouped by age range
     */
    public Map<String, List<Person>> getOwnersByAgeRange() {
        return carList.stream()
                .filter(car -> car.getOwner() != null)
                .map(Car::getOwner)
                .distinct()
                .collect(Collectors.groupingBy(
                        person -> {
                            int age = person.getAge();
                            if (age < 30) return "Young (0-29)";
                            else if (age < 50) return "Middle-aged (30-49)";
                            else return "Senior (50+)";
                        }
                ));
    }

    /*
     * Exercise 13: Get cars with highest value (year * owner age)
     */
    public Optional<Car> getCarWithHighestValue() {
        return carList.stream()
                .filter(car -> car.getOwner() != null)
                .max(Comparator.comparingInt(car -> 
                    car.getYear() * car.getOwner().getAge()
                ));
    }

    /*
     * Exercise 14: Get all unique combinations of brand and color
     */
    public List<String> getAllUniqueCombinations() {
        return carList.stream()
                .flatMap(car1 -> carList.stream()
                        .filter(car2 -> !car1.equals(car2))
                        .map(car2 -> car1.getBrand() + " vs " + car2.getBrand()))
                .distinct()
                .collect(Collectors.toList());
    }

    /*
     * Exercise 15: Get comprehensive car statistics
     */
    public Map<String, Object> getComprehensiveStatistics() {
        return carList.stream()
                .collect(Collectors.collectingAndThen(
                        Collectors.toList(),
                        cars -> {
                            Map<String, Object> stats = new HashMap<>();
                            stats.put("totalCars", cars.size());
                            stats.put("averageYear", cars.stream()
                                    .mapToInt(Car::getYear)
                                    .average()
                                    .orElse(0.0));
                            stats.put("uniqueBrands", cars.stream()
                                    .map(Car::getBrand)
                                    .filter(Objects::nonNull)
                                    .distinct()
                                    .count());
                            stats.put("uniqueColors", cars.stream()
                                    .map(Car::getColor)
                                    .filter(Objects::nonNull)
                                    .distinct()
                                    .count());
                            stats.put("carsWithOwners", cars.stream()
                                    .filter(car -> car.getOwner() != null)
                                    .count());
                            return stats;
                        }
                ));
    }
}
