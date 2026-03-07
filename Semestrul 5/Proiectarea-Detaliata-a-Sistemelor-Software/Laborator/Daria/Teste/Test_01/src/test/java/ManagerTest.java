import org.junit.Before;
import org.junit.Test;

import java.util.*;

import static org.junit.Assert.*;

public class ManagerTest {

    private Manager manager;
    private List<Car> testCars;

    @Before
    public void init() {
        testCars = CarsProvider.getTestCars();
        manager = new Manager(testCars);
    }

    // ========== FIRST METHOD TESTS ==========
    @Test
    public void testFirstMethod_ReturnsOwnerToCarMapping() {
        Map<Person, Car> result = manager.firstMethod();

        assertNotNull("Map should not be null", result);
        assertFalse("Map should not be empty", result.isEmpty());

        // every car with owner != null should appear
        long carsWithOwner = testCars.stream().filter(c -> c.getOwner() != null).count();
        assertEquals(carsWithOwner, result.size());

        // key set should contain owners only (no nulls)
        assertFalse(result.containsKey(null));
    }

    // ========== SECOND METHOD TESTS ==========
    @Test
    public void testSecondMethod_ReturnsDistinctOwnerFirstNamesForFaceliftedCarsFromYear() {
        Collection<String> result = manager.secondMethod(2020);

        assertNotNull(result);
        // For CarsProvider.getTestCars(): facelifted 2020 cars → Toyota(John), Toyota(null)
        // → distinct first names: ["John"]
        assertTrue(result.contains("John"));
        assertEquals(1, result.size());
    }

    // ========== THIRD METHOD TESTS ==========
    @Test
    public void testThirdMethod_ReturnsOwnerFullNameOfNewestBlackCar() {
        String result = manager.thirdMethod();
        // Black cars: BMW(2021, Bob), Audi(2022, Charlie), Mercedes(2023, Jane)
        // Newest = Mercedes(2023, Jane)
        assertEquals("Jane Smith", result);
    }

    // ========== FOURTH METHOD TESTS ==========
    @Test
    public void testFourthMethod_ReturnsAverageAgeOfOwnersForBrand() {
        double avgToyotaOwners = manager.forthMethod("Toyota");
        // Only Toyota with owner: John (30)
        assertEquals(30.0, avgToyotaOwners, 0.01);

        double avgAudiOwners = manager.forthMethod("Audi");
        // Audi: Charlie(40) and Bob(35) → average = 37.5
        assertEquals(37.5, avgAudiOwners, 0.01);
    }

    // ========== FIFTH METHOD TESTS ==========
    @Test
    public void testFifthMethod_CountsCarsAfterYearAndSetsFaceliftedTrue() {
        long count = manager.fifthMethod(2020);

        assertEquals(4, count);

        // Verify that facelifted is set to true for these cars
        for (Car car : testCars) {
            if (car.getYear() > 2020) {
                assertTrue("Car facelifted should be true for cars after 2020", car.isFaceLifted());
            }
        }
    }

    // ========== SIXTH METHOD TESTS ==========
    @Test
    public void testSixthMethod_ReturnsOwnerOfOldestCarForBrandAndColor() {
        Person owner = manager.sixthMethod("Audi", "Red");
        // Audi Red: (2021, Bob)
        assertEquals("Bob", owner.getFirstName());
        assertEquals("Johnson", owner.getLastName());
    }

    // ========== SEVENTH METHOD TESTS ==========
    @Test
    public void testSeventhMethod_GroupsCarsByColorIncludingNullColors() {
        Map<String, List<Car>> grouped = manager.seventhMethod();

        assertNotNull(grouped);
        assertTrue(grouped.containsKey("Black"));
        assertTrue(grouped.containsKey("Red"));

        // Ensure all black cars are correctly grouped
        List<Car> blackCars = grouped.get("Black");
        assertTrue(blackCars.stream().allMatch(c -> "Black".equals(c.getColor())));
    }
}
