import java.util.*;
import java.util.stream.Collectors;

public class CarRepository {
    private Collection<Car> cars;

    public CarRepository(Collection<Car> cars) {
        this.cars = new ArrayList<>(cars);
    }

    // ========== BASIC STREAM EXERCISES ==========

    public List<String> getCarBrandsSortedByYearUnderTheYearOf(int year) {
        return cars.stream()
                .filter(car -> car.getYear() < year)
                .sorted(Comparator.comparingInt(Car::getYear))
                .map(Car::getBrand)
                .collect(Collectors.toList());
    }

    /**
     * @return returns the sorted list of distinct colors.
     *
     * SIDE EFFECT: makes all car colors uppercase
     */
    public List<String> makeCarColorsUppercaseAndReturnThemAsSortedDistinctList() {
        return cars.stream()
                .filter(car -> car.getColor() != null)
                .peek(car -> car.setColor(car.getColor().toUpperCase()))
                .map(Car::getColor)
                .sorted()
                .distinct()
                .collect(Collectors.toList());
    }

    public Set<String> getNonNullBrands() {
        return cars.stream()
                .filter(car -> car.getBrand() != null)
                .map(Car::getBrand)
                .collect(Collectors.toSet());
    }

    public Map<String, Car> getCarsMappedByBrand() {
        return cars.stream()
                .filter(car -> car.getBrand() != null)
                .collect(Collectors.toMap(
                        Car::getBrand,
                        car -> car
                ));
    }

    public Map<String, List<Car>> getFaceLiftedCarsGroupedByBrand() {
        return cars.stream()
                .filter(car -> car.getBrand() != null)
                .filter(Car::isFaceLifted)
                .collect(Collectors.groupingBy(
                        Car::getBrand
                ));
    }

    public Optional<Car> getTheCarWithTheNthNewestYear(int n) {
        return cars.stream()
                .sorted(Comparator.comparingInt(Car::getYear).reversed())
                .skip(n - 1)
                .findFirst();
    }

    public Optional<String> getTheBrandOfTheSecondOldestCar() {
        return cars.stream()
                .sorted(Comparator.comparingInt(Car::getYear))
                .map(Car::getBrand)
                .skip(1)
                .findFirst();
    }

    public OptionalDouble getAverageYearOfNCarsInBrand(int n, String brand) {
        return cars.stream()
                .filter(car -> car.getBrand() != null && isInBrand(car.getOwner(), brand))
                .limit(n)
                .mapToInt(Car::getYear)
                .average();
    }

    public long countCarsWithBrandsLongerThan(int n) {
        return cars.stream()
                .filter(car -> car.getBrand() != null)
                .filter(car -> car.getBrand().length() > n)
                .count();
    }

    // ========== STREAM IN STREAM EXERCISES ==========

    /**
     * Cars with no owner (owner == null) are considered to be owned by the same person
     * Count cars that have at least N colleagues (other car owners) with different brands
     */
    public long countNumberOfCarsWithAtLeastNColleaguesWithDifferentBrands(int n) {
        return cars.stream()
                .filter(car -> car.getOwner() != null)
                .filter(currentCar -> {
                    String currentBrand = currentCar.getBrand();
                    
                    long countColleagues = currentCar.getOwner().getColleagues().stream()
                            .filter(Objects::nonNull)
                            .filter(colleague -> !isInBrand(colleague, currentBrand))
                            .count();
                    
                    return countColleagues >= n;
                })
                .count();
    }

    /**
     * Helper method for implementing countNumberOfCarsWithAtLeastNColleaguesWithDifferentBrands(int n)
     */
    private static boolean isInBrand(Person person, String brand) {
        if (brand == null)
            return person.getBrand() == null;
        return brand.equals(person.getBrand());
    }

    /**
     * Get cars whose owners have at least one colleague with the same car color
     */
    public List<Car> getCarsWithAtLeastOneColleagueWithSameCarColor() {
        return cars.stream()
                .filter(car -> car.getOwner() != null && car.getOwner().getColleagues() != null && !car.getOwner().getColleagues().isEmpty())
                .filter(currentCar -> {
                    String currentColor = getCarColor(currentCar.getColor());
                    long count = currentCar.getOwner().getColleagues().stream()
                            .filter(colleague -> getCarColor(colleague.getCarColor()).equals(currentColor))
                            .count();
                    
                    return count > 0;
                })
                .collect(Collectors.toList());
    }

    /**
     * Helper method for implementing getCarsWithAtLeastOneColleagueWithSameCarColor()
     */
    private static String getCarColor(String color) {
        if (color == null) {
            return "null";
        }
        return color;
    }

    // ========== ADDITIONAL STREAM IN STREAM EXERCISES ==========

    /**
     * Get cars whose owners have colleagues with cars from the same year
     */
    public List<Car> getCarsWithOwnersHavingColleaguesWithSameYearCars() {
        return cars.stream()
                .filter(car -> car.getOwner() != null && car.getOwner().getColleagues() != null)
                .filter(currentCar -> {
                    int currentYear = currentCar.getYear();
                    long count = currentCar.getOwner().getColleagues().stream()
                            .filter(Objects::nonNull)
                            .filter(colleague -> colleague.getCarYear() == currentYear)
                            .count();
                    
                    return count > 0;
                })
                .collect(Collectors.toList());
    }

    /**
     * Get cars grouped by owner's age range, then by brand
     */
    public Map<String, Map<String, List<Car>>> getCarsGroupedByOwnerAgeRangeAndBrand() {
        return cars.stream()
                .filter(car -> car.getOwner() != null)
                .collect(Collectors.groupingBy(
                        car -> {
                            int age = car.getOwner().getAge();
                            if (age < 30) return "Young (0-29)";
                            else if (age < 50) return "Middle-aged (30-49)";
                            else return "Senior (50+)";
                        },
                        Collectors.groupingBy(Car::getBrand)
                ));
    }

    /**
     * Get statistics about cars and their owners' colleagues
     */
    public Map<String, Object> getCarsWithColleaguesStatistics() {
        return cars.stream()
                .filter(car -> car.getOwner() != null)
                .collect(Collectors.collectingAndThen(
                        Collectors.toList(),
                        carList -> {
                            Map<String, Object> stats = new HashMap<>();
                            stats.put("totalCarsWithOwners", carList.size());
                            stats.put("averageColleaguesPerOwner", carList.stream()
                                    .mapToInt(car -> car.getOwner().getColleagues() != null ? car.getOwner().getColleagues().size() : 0)
                                    .average()
                                    .orElse(0.0));
                            stats.put("carsWithColleagues", carList.stream()
                                    .filter(car -> car.getOwner().getColleagues() != null && !car.getOwner().getColleagues().isEmpty())
                                    .count());
                            return stats;
                        }
                ));
    }
}
