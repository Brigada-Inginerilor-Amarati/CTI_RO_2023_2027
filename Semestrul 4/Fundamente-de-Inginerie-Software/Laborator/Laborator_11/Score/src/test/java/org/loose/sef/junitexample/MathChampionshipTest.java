package org.loose.sef.junitexample;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import java.io.BufferedReader;
import java.io.IOException;
import java.net.URISyntaxException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class MathChampionshipTest {
    private MathChampionship mathChampionship;


    private void readScoresFromCsv(String fileName) {
        List<StudentScore> studentScores = new ArrayList<>();
        Path pathToFile;
        try {
            pathToFile = Paths.get(getClass().getClassLoader().getResource(fileName).toURI());
        }
        catch (URISyntaxException e) {
            e.printStackTrace();
            throw new RuntimeException("Could not read file", e);
        }

        try (BufferedReader br = Files.newBufferedReader(pathToFile, StandardCharsets.UTF_8)) {

            String line = br.readLine();

            while (line != null) {
                String[] attributes = line.split(",");
                StudentScore student = new StudentScore(attributes[0], Integer.parseInt(attributes[1]));
                studentScores.add(student);
                line = br.readLine();
            }

            mathChampionship.setStudentScores(studentScores);

        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
    }

    @BeforeEach
    void setUp() {
        mathChampionship = new MathChampionship();
        // Assuming max achievable score is 100
        mathChampionship.setMaxAchievableScore(100);
        // fill in student scores
        mathChampionship.setStudentScores(Arrays.asList(
                new StudentScore("John Doe", 97),
                new StudentScore("Jane Doe", 92)
        ));
    }

    @Test
    @DisplayName("Test if a student with a score higher than 95% of the max achievable score gets a Gold medal")
    void testGetGoldPrize() {
        // Act
        Prize prize = mathChampionship.getPrize("John Doe");

        // Assert
        assertEquals(Prize.GOLD, prize);
    }

    @Test
    @DisplayName("Test if a student with a score higher than 90% of the max achievable score gets a Silver medal")
    void testGetSilverPrize() {
        // Act
        Prize prize = mathChampionship.getPrize("Jane Doe");

        // Assert
        assertEquals(Prize.SILVER, prize);
    }

    // other tests

    @Test
    @DisplayName("Test if searching for a student that doesn't exist throws a StudentNotFoundException")
    void testNoSuchStudent() {
        // Act and Assert
        assertThrows(StudentNotFoundException.class, () -> mathChampionship.getPrize("Mr Nobody"));
    }

    @Test
    @DisplayName("Template for reading student scores from a CSV file")
    @Disabled("This Test is just a template, do not add it to your test suite")
    void testPrizeFromCsv() {
        // Arrange
        readScoresFromCsv("student_scores.csv");

        // Act
        Prize prize = mathChampionship.getPrize("Jane Doe");

        // Assert
        assertEquals(Prize.SILVER, prize);
    }
    /*
    For example:

    If the student with the highest score has 45% of the maxAchievable score, they do not win a gold medal, although they should
    If three students have a score of over 95%, and the forth has a score of 75%, they do not win a Silver medal, although they should
    ... many other edge cases
     */

    // other tests

    /*
        testGetGoldPrize - A student whose score is more than 95% of the total achievable score should get a Gold medal.
        testGetSilverPrize - A student whose score is more than 90% of the total achievable score should get a Silver medal.
        testGetBronzePrize - A student whose score is more than 85% of the total achievable score should get a Bronze medal.
        testGetMentionPrize - A student whose score is more than 80% of the total achievable score should get an honourable mention.
        testGetNoPrize - A student whose score is less than 80% of the total achievable score should get no prize.
        testStudentNotFound - If a student is not found in the list, the method should throw a StudentNotFoundException.
        testGetGoldPrizeHighestScore - If no student scores more than 95%, the student with the highest score should get a Gold medal.
        testGetSilverPrizeSecondHighestScore - If no student scores more than 90%, the student with the second-highest score should get a Silver medal.
        testGetBronzePrizeThirdHighestScore - If no student scores more than 85%, the student with the third-highest score should get a Bronze medal.
        testGetMentionPrizeNextHighestScores - If no student scores more than 80%, the next five highest scoring students (with scores at least 50%) should get an honourable mention.
     */
    
    @Test
    @DisplayName("Test if a student with a score higher than 85% of the max achievable score gets a Bronze medal")
    void testGetBronzePrize() {
        // Act
        Prize prize = mathChampionship.getPrize("John Doe");

        // Assert
        assertEquals(Prize.BRONZE, prize);
    }



    @Test
    @DisplayName("Test if a student with a score higher than 80% of the max achievable score gets a Mention")

}