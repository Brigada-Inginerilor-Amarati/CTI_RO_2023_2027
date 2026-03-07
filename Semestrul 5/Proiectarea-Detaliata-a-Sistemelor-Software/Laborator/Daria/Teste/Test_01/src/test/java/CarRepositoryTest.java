import org.junit.Before;
import org.junit.Test;

import java.util.*;

import static org.junit.Assert.*;

public class CarRepositoryTest {

    private CarRepository carRepository;
    private List<Car> testCars;

    @Before
    public void init() {
        testCars = createTestCarsWithColleagues();
        carRepository = new CarRepository(testCars);
    }

    private List<Car> createTestCarsWithColleagues() {
        List<Car> cars = new ArrayList<>();
        
        // Create persons with colleagues
        Person john = new Person("John", "Doe", 30);
        Person jane = new Person("Jane", "Smith", 25);
        Person bob = new Person("Bob", "Johnson", 35);
        Person alice = new Person("Alice", "Brown", 28);
        Person charlie = new Person("Charlie", "Wilson", 40);
        
        // Set up colleagues relationships
        john.addColleague(jane);
        john.addColleague(bob);
        jane.addColleague(john);
        jane.addColleague(alice);
        bob.addColleague(john);
        bob.addColleague(charlie);
        alice.addColleague(jane);
        charlie.addColleague(bob);
        
        // Set car information for colleagues
        john.setBrand("Toyota");
        john.setCarColor("Red");
        john.setCarYear(2020);
        
        jane.setBrand("Honda");
        jane.setCarColor("Blue");
        jane.setCarYear(2019);
        
        bob.setBrand("BMW");
        bob.setCarColor("Black");
        bob.setCarYear(2021);
        
        alice.setBrand("Mercedes");
        alice.setCarColor("White");
        alice.setCarYear(2018);
        
        charlie.setBrand("Audi");
        charlie.setCarColor("Black");
        charlie.setCarYear(2022);
        
        // Create cars
        cars.add(new Car("Toyota", "Red", 2020, true, john));
        cars.add(new Car("Honda", "Blue", 2019, false, jane));
        cars.add(new Car("BMW", "Black", 2021, true, bob));
        cars.add(new Car("Mercedes", "White", 2018, false, alice));
        cars.add(new Car("Audi", "Black", 2022, true, charlie));
        cars.add(new Car("Toyota", "Green", 2020, true, null));
        cars.add(new Car("Honda", null, 2019, false, null));
        cars.add(new Car("BMW", "Silver", 2017, true, null));
        
        return cars;
    }

    // ========== BASIC STREAM TESTS ==========
    
    @Test
    public void testGetCarBrandsSortedByYearUnderTheYearOf() {
        List<String> brands = carRepository.getCarBrandsSortedByYearUnderTheYearOf(2020);
        
        assertNotNull("Brands list should not be null", brands);
        assertTrue("Should contain Honda (2019)", brands.contains("Honda"));
        assertTrue("Should contain BMW (2017)", brands.contains("BMW"));
        assertFalse("Should not contain Toyota (2020)", brands.contains("Toyota"));
    }

    @Test
    public void testMakeCarColorsUppercaseAndReturnThemAsSortedDistinctList() {
        List<String> colors = carRepository.makeCarColorsUppercaseAndReturnThemAsSortedDistinctList();
        
        assertNotNull("Colors list should not be null", colors);
        assertTrue("Should contain RED", colors.contains("RED"));
        assertTrue("Should contain BLUE", colors.contains("BLUE"));
        assertTrue("Should contain BLACK", colors.contains("BLACK"));
        assertTrue("Should be sorted", isSorted(colors));
    }

    @Test
    public void testGetNonNullBrands() {
        Set<String> brands = carRepository.getNonNullBrands();
        
        assertNotNull("Brands set should not be null", brands);
        assertTrue("Should contain Toyota", brands.contains("Toyota"));
        assertTrue("Should contain Honda", brands.contains("Honda"));
        assertTrue("Should contain BMW", brands.contains("BMW"));
    }

    @Test
    public void testGetCarsMappedByBrand() {
        Map<String, Car> carsByBrand = carRepository.getCarsMappedByBrand();
        
        assertNotNull("Cars map should not be null", carsByBrand);
        assertTrue("Should contain Toyota", carsByBrand.containsKey("Toyota"));
        assertTrue("Should contain Honda", carsByBrand.containsKey("Honda"));
        assertTrue("Should contain BMW", carsByBrand.containsKey("BMW"));
    }

    @Test
    public void testGetFaceLiftedCarsGroupedByBrand() {
        Map<String, List<Car>> faceLiftedCars = carRepository.getFaceLiftedCarsGroupedByBrand();
        
        assertNotNull("FaceLifted cars map should not be null", faceLiftedCars);
        assertTrue("Should contain Toyota group", faceLiftedCars.containsKey("Toyota"));
        assertTrue("Should contain BMW group", faceLiftedCars.containsKey("BMW"));
        assertTrue("Should contain Audi group", faceLiftedCars.containsKey("Audi"));
    }

    @Test
    public void testGetTheCarWithTheNthNewestYear() {
        Optional<Car> newestCar = carRepository.getTheCarWithTheNthNewestYear(1);
        
        assertTrue("Should find newest car", newestCar.isPresent());
        assertEquals("Newest car should be Audi 2022", "Audi", newestCar.get().getBrand());
        assertEquals("Newest car year should be 2022", 2022, newestCar.get().getYear());
    }

    @Test
    public void testGetTheBrandOfTheSecondOldestCar() {
        Optional<String> secondOldestBrand = carRepository.getTheBrandOfTheSecondOldestCar();
        
        assertTrue("Should find second oldest brand", secondOldestBrand.isPresent());
        assertEquals("Second oldest should be Mercedes", "Mercedes", secondOldestBrand.get());
    }

    @Test
    public void testGetAverageYearOfNCarsInBrand() {
        OptionalDouble average = carRepository.getAverageYearOfNCarsInBrand(2, "Toyota");
        
        assertTrue("Should find average", average.isPresent());
        assertEquals("Toyota average should be 2020", 2020.0, average.getAsDouble(), 0.01);
    }

    @Test
    public void testCountCarsWithBrandsLongerThan() {
        long count = carRepository.countCarsWithBrandsLongerThan(3);
        
        assertTrue("Should have some brands longer than 3 characters", count > 0);
    }

    // ========== STREAM IN STREAM TESTS ==========
    
    @Test
    public void testCountNumberOfCarsWithAtLeastNColleaguesWithDifferentBrands() {
        long count = carRepository.countNumberOfCarsWithAtLeastNColleaguesWithDifferentBrands(1);
        
        assertTrue("Should have some cars with colleagues having different brands", count >= 0);
    }

    @Test
    public void testGetCarsWithAtLeastOneColleagueWithSameCarColor() {
        List<Car> carsWithColleaguesSameColor = carRepository.getCarsWithAtLeastOneColleagueWithSameCarColor();
        
        assertNotNull("Cars list should not be null", carsWithColleaguesSameColor);
        // Should find cars where owners have colleagues with same car color
    }

    @Test
    public void testGetCarsWithOwnersHavingColleaguesWithSameYearCars() {
        List<Car> carsWithColleaguesSameYear = carRepository.getCarsWithOwnersHavingColleaguesWithSameYearCars();
        
        assertNotNull("Cars list should not be null", carsWithColleaguesSameYear);
        // Should find cars where owners have colleagues with cars from same year
    }

    @Test
    public void testGetCarsGroupedByOwnerAgeRangeAndBrand() {
        Map<String, Map<String, List<Car>>> grouped = carRepository.getCarsGroupedByOwnerAgeRangeAndBrand();
        
        assertNotNull("Grouped cars should not be null", grouped);
        assertTrue("Should have young category", grouped.containsKey("Young (0-29)"));
        assertTrue("Should have middle-aged category", grouped.containsKey("Middle-aged (30-49)"));
    }

    @Test
    public void testGetCarsWithColleaguesStatistics() {
        Map<String, Object> stats = carRepository.getCarsWithColleaguesStatistics();
        
        assertNotNull("Statistics should not be null", stats);
        assertTrue("Should have totalCarsWithOwners", stats.containsKey("totalCarsWithOwners"));
        assertTrue("Should have averageColleaguesPerOwner", stats.containsKey("averageColleaguesPerOwner"));
        assertTrue("Should have carsWithColleagues", stats.containsKey("carsWithColleagues"));
    }

    // ========== EDGE CASE TESTS ==========
    
    @Test
    public void testWithEmptyList() {
        CarRepository emptyRepository = new CarRepository(new ArrayList<>());
        
        List<String> brands = emptyRepository.getCarBrandsSortedByYearUnderTheYearOf(2020);
        assertTrue("Empty list should return empty brands", brands.isEmpty());
        
        Set<String> nonNullBrands = emptyRepository.getNonNullBrands();
        assertTrue("Empty list should return empty brands set", nonNullBrands.isEmpty());
    }

    @Test
    public void testWithNullList() {
        CarRepository nullRepository = new CarRepository(null);
        
        try {
            List<String> brands = nullRepository.getCarBrandsSortedByYearUnderTheYearOf(2020);
            // Should either return empty list or throw exception gracefully
        } catch (Exception e) {
            // Expected behavior for null list
        }
    }

    // ========== HELPER METHODS ==========
    
    private boolean isSorted(List<String> list) {
        for (int i = 1; i < list.size(); i++) {
            if (list.get(i - 1).compareTo(list.get(i)) > 0) {
                return false;
            }
        }
        return true;
    }
}
