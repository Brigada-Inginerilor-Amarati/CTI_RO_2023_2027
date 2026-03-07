import org.junit.Before;
import org.junit.Test;

import java.util.*;

import static org.junit.Assert.*;

public class StreamInStreamExercisesTest {

    private StreamInStreamExercises exercises;
    private List<Car> testCars;

    @Before
    public void init() {
        testCars = CarsProvider.getTestCars();
        exercises = new StreamInStreamExercises(testCars);
    }

    @Test
    public void testGetAllUniqueColors() {
        Set<String> colors = exercises.getAllUniqueColors();
        
        assertNotNull("Colors set should not be null", colors);
        assertTrue("Should contain common colors", colors.contains("Red"));
        assertTrue("Should contain Black", colors.contains("Black"));
        assertTrue("Should contain Blue", colors.contains("Blue"));
        assertFalse("Should not contain null", colors.contains(null));
    }

    @Test
    public void testGetFirstNamesOfOwnersWithFaceLiftedCars() {
        List<String> firstNames = exercises.getFirstNamesOfOwnersWithFaceLiftedCars();
        
        assertNotNull("First names list should not be null", firstNames);
        assertTrue("Should contain John", firstNames.contains("John"));
        assertTrue("Should contain Bob", firstNames.contains("Bob"));
        assertTrue("Should contain Charlie", firstNames.contains("Charlie"));
    }

    @Test
    public void testGetBrandOfCarOwnedByYoungestPerson() {
        Optional<String> brand = exercises.getBrandOfCarOwnedByYoungestPerson();
        
        assertTrue("Should find a brand", brand.isPresent());
        // Jane is 25, youngest in test data
        assertEquals("Should return Honda (Jane's car)", "Honda", brand.get());
    }

    @Test
    public void testGetAverageYearByBrand() {
        Map<String, Double> averages = exercises.getAverageYearByBrand();
        
        assertNotNull("Averages map should not be null", averages);
        assertTrue("Should contain Toyota", averages.containsKey("Toyota"));
        assertTrue("Should contain BMW", averages.containsKey("BMW"));
        
        // Verify Toyota average (2020 + 2020) / 2 = 2020
        assertEquals("Toyota average should be 2020", 2020.0, averages.get("Toyota"), 0.01);
    }

    @Test
    public void testGetOwnersWithMultipleCars() {
        Map<Person, Long> ownersWithMultipleCars = exercises.getOwnersWithMultipleCars();
        
        assertNotNull("Map should not be null", ownersWithMultipleCars);
        // In test data, John owns 2 cars, Jane owns 2 cars
        assertEquals("Should have 2 owners with multiple cars", 2, ownersWithMultipleCars.size());
    }

    @Test
    public void testGetMostPopularColor() {
        Optional<String> mostPopularColor = exercises.getMostPopularColor();
        
        assertTrue("Should find most popular color", mostPopularColor.isPresent());
        // Black appears 3 times in test data
        assertEquals("Most popular color should be Black", "Black", mostPopularColor.get());
    }

    @Test
    public void testGetCarsNewerThanBrandAverage() {
        List<Car> newerCars = exercises.getCarsNewerThanBrandAverage();
        
        assertNotNull("List should not be null", newerCars);
        // Should contain cars that are newer than their brand's average
        assertFalse("Should have some newer cars", newerCars.isEmpty());
    }

    @Test
    public void testGetCarOwnershipStatistics() {
        Map<Boolean, Map<String, Object>> stats = exercises.getCarOwnershipStatistics();
        
        assertNotNull("Statistics should not be null", stats);
        assertTrue("Should have owned cars", stats.containsKey(true));
        assertTrue("Should have unowned cars", stats.containsKey(false));
        
        Map<String, Object> ownedStats = stats.get(true);
        assertTrue("Owned cars should have count", ownedStats.containsKey("count"));
        assertTrue("Owned cars should have average year", ownedStats.containsKey("averageYear"));
    }

    @Test
    public void testGetCarWithHighestValue() {
        Optional<Car> highestValueCar = exercises.getCarWithHighestValue();
        
        assertTrue("Should find highest value car", highestValueCar.isPresent());
        // Value = year * age, so we expect a car with high year and high age owner
    }

    @Test
    public void testGetCarBrandsByAgeRange() {
        Map<String, List<String>> brandsByAge = exercises.getCarBrandsByAgeRange();
        
        assertNotNull("Map should not be null", brandsByAge);
        assertTrue("Should have young category", brandsByAge.containsKey("Young (0-29)"));
        assertTrue("Should have middle-aged category", brandsByAge.containsKey("Middle-aged (30-49)"));
    }

    @Test
    public void testGetAllBrandColorCombinations() {
        List<String> combinations = exercises.getAllBrandColorCombinations();
        
        assertNotNull("Combinations should not be null", combinations);
        assertFalse("Should have some combinations", combinations.isEmpty());
        assertTrue("Should contain Toyota Red", combinations.contains("Toyota Red"));
        assertTrue("Should contain BMW Black", combinations.contains("BMW Black"));
    }

    @Test
    public void testGetBrandStatistics() {
        Map<String, Map<String, Object>> brandStats = exercises.getBrandStatistics();
        
        assertNotNull("Brand statistics should not be null", brandStats);
        assertTrue("Should have Toyota stats", brandStats.containsKey("Toyota"));
        assertTrue("Should have BMW stats", brandStats.containsKey("BMW"));
        
        Map<String, Object> toyotaStats = brandStats.get("Toyota");
        assertTrue("Toyota should have count", toyotaStats.containsKey("count"));
        assertTrue("Toyota should have average year", toyotaStats.containsKey("averageYear"));
        assertTrue("Toyota should have colors", toyotaStats.containsKey("colors"));
    }

    @Test
    public void testGetAllPossibleCarCombinations() {
        List<String> combinations = exercises.getAllPossibleCarCombinations()
                .collect(java.util.stream.Collectors.toList());
        
        assertNotNull("Combinations should not be null", combinations);
        assertFalse("Should have some combinations", combinations.isEmpty());
        // Should contain various brand vs brand combinations
    }

    @Test
    public void testGetCarsGroupedByBrandAndColor() {
        Map<String, Map<String, List<Car>>> grouped = exercises.getCarsGroupedByBrandAndColor();
        
        assertNotNull("Grouped cars should not be null", grouped);
        assertTrue("Should have Toyota group", grouped.containsKey("Toyota"));
        assertTrue("Should have BMW group", grouped.containsKey("BMW"));
        
        Map<String, List<Car>> toyotaGroup = grouped.get("Toyota");
        assertTrue("Toyota should have Red cars", toyotaGroup.containsKey("Red"));
        assertTrue("Toyota should have Green cars", toyotaGroup.containsKey("Green"));
    }

    // ========== EDGE CASE TESTS ==========
    
    @Test
    public void testWithEmptyList() {
        StreamInStreamExercises emptyExercises = new StreamInStreamExercises(new ArrayList<>());
        
        Set<String> colors = emptyExercises.getAllUniqueColors();
        assertTrue("Empty list should return empty colors", colors.isEmpty());
        
        List<String> firstNames = emptyExercises.getFirstNamesOfOwnersWithFaceLiftedCars();
        assertTrue("Empty list should return empty first names", firstNames.isEmpty());
        
        Optional<String> brand = emptyExercises.getBrandOfCarOwnedByYoungestPerson();
        assertFalse("Empty list should return empty optional", brand.isPresent());
    }

    @Test
    public void testWithNullList() {
        StreamInStreamExercises nullExercises = new StreamInStreamExercises(null);
        
        // These should handle null gracefully
        try {
            Set<String> colors = nullExercises.getAllUniqueColors();
            // Should either return empty set or throw exception gracefully
        } catch (Exception e) {
            // Expected behavior for null list
        }
    }
}
