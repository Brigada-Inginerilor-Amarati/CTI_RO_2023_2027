import java.util.Arrays;
import java.util.IntSummaryStatistics;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.OptionalDouble;

/**
 * Stream Exercises
 * 
 * Practice exercises to test your understanding of Java Streams.
 * Try to solve these on your own before looking at the solutions!
 */
public class StreamExercises {

    static class Book {
        String title;
        String author;
        int year;
        double rating;
        int pages;
        
        public Book(String title, String author, int year, double rating, int pages) {
            this.title = title;
            this.author = author;
            this.year = year;
            this.rating = rating;
            this.pages = pages;
        }
        
        public String getTitle() { return title; }
        public String getAuthor() { return author; }
        public int getYear() { return year; }
        public double getRating() { return rating; }
        public int getPages() { return pages; }
        
        @Override
        public String toString() {
            return String.format("\"%s\" by %s (%d) - Rating: %.1f, Pages: %d", 
                title, author, year, rating, pages);
        }
    }

    public static void main(String[] args) {
        
        List<Book> books = Arrays.asList(
            new Book("Effective Java", "Joshua Bloch", 2018, 4.7, 416),
            new Book("Clean Code", "Robert Martin", 2008, 4.6, 464),
            new Book("Java Concurrency", "Brian Goetz", 2006, 4.5, 384),
            new Book("Design Patterns", "Gang of Four", 1994, 4.4, 395),
            new Book("Head First Java", "Kathy Sierra", 2005, 4.3, 720),
            new Book("Spring in Action", "Craig Walls", 2018, 4.5, 520),
            new Book("Java Performance", "Scott Oaks", 2014, 4.2, 426),
            new Book("Refactoring", "Martin Fowler", 2018, 4.6, 448)
        );
        
        System.out.println("========== STREAM EXERCISES ==========\n");
        
        // ==========================================
        // EXERCISE 1: Basic Filtering
        // Find all books published after 2010
        // ==========================================
        System.out.println("EXERCISE 1: Books published after 2010");
        System.out.println("Your solution here:");
        
        // TODO: Implement this
        List<Book> booksAfter2010 = null;
        
        // Solution (uncomment to see):
        /*
        booksAfter2010 = books.stream()
                             .filter(book -> book.getYear() > 2010)
                             .collect(Collectors.toList());
        */
        
        // Verify:
        // booksAfter2010.forEach(System.out::println);
        System.out.println("\n" + "=".repeat(50) + "\n");
        
        
        // ==========================================
        // EXERCISE 2: Mapping
        // Get a list of all book titles in uppercase
        // ==========================================
        System.out.println("EXERCISE 2: All book titles in uppercase");
        System.out.println("Your solution here:");
        
        // TODO: Implement this
        List<String> uppercaseTitles = null;
        
        // Solution (uncomment to see):
        /*
        uppercaseTitles = books.stream()
                              .map(Book::getTitle)
                              .map(String::toUpperCase)
                              .collect(Collectors.toList());
        */
        
        // Verify:
        // uppercaseTitles.forEach(System.out::println);
        System.out.println("\n" + "=".repeat(50) + "\n");
        
        
        // ==========================================
        // EXERCISE 3: Sorting
        // Get books sorted by rating (highest first)
        // ==========================================
        System.out.println("EXERCISE 3: Books sorted by rating (highest first)");
        System.out.println("Your solution here:");
        
        // TODO: Implement this
        List<Book> sortedByRating = null;
        
        // Solution (uncomment to see):
        /*
        sortedByRating = books.stream()
                             .sorted(Comparator.comparing(Book::getRating).reversed())
                             .collect(Collectors.toList());
        */
        
        // Verify:
        // sortedByRating.forEach(System.out::println);
        System.out.println("\n" + "=".repeat(50) + "\n");
        
        
        // ==========================================
        // EXERCISE 4: Counting
        // Count how many books have rating >= 4.5
        // ==========================================
        System.out.println("EXERCISE 4: Count books with rating >= 4.5");
        System.out.println("Your solution here:");
        
        // TODO: Implement this
        long highRatedCount = 0;
        
        // Solution (uncomment to see):
        /*
        highRatedCount = books.stream()
                             .filter(book -> book.getRating() >= 4.5)
                             .count();
        */
        
        // Verify:
        // System.out.println("High rated books: " + highRatedCount);
        System.out.println("\n" + "=".repeat(50) + "\n");
        
        
        // ==========================================
        // EXERCISE 5: Reduction
        // Calculate the average rating of all books
        // ==========================================
        System.out.println("EXERCISE 5: Average rating of all books");
        System.out.println("Your solution here:");
        
        // TODO: Implement this
        OptionalDouble averageRating = OptionalDouble.empty();
        
        // Solution (uncomment to see):
        /*
        averageRating = books.stream()
                            .mapToDouble(Book::getRating)
                            .average();
        */
        
        // Verify:
        // averageRating.ifPresent(avg -> System.out.printf("Average rating: %.2f%n", avg));
        System.out.println("\n" + "=".repeat(50) + "\n");
        
        
        // ==========================================
        // EXERCISE 6: Finding
        // Find the book with the most pages
        // ==========================================
        System.out.println("EXERCISE 6: Book with the most pages");
        System.out.println("Your solution here:");
        
        // TODO: Implement this
        Optional<Book> longestBook = Optional.empty();
        
        // Solution (uncomment to see):
        /*
        longestBook = books.stream()
                          .max(Comparator.comparing(Book::getPages));
        */
        
        // Verify:
        // longestBook.ifPresent(book -> System.out.println("Longest book: " + book));
        System.out.println("\n" + "=".repeat(50) + "\n");
        
        
        // ==========================================
        // EXERCISE 7: Grouping
        // Group books by author
        // ==========================================
        System.out.println("EXERCISE 7: Group books by author");
        System.out.println("Your solution here:");
        
        // TODO: Implement this
        Map<String, List<Book>> booksByAuthor = null;
        
        // Solution (uncomment to see):
        /*
        booksByAuthor = books.stream()
                            .collect(Collectors.groupingBy(Book::getAuthor));
        */
        
        // Verify:
        /*
        booksByAuthor.forEach((author, authorBooks) -> {
            System.out.println(author + ":");
            authorBooks.forEach(b -> System.out.println("  - " + b.getTitle()));
        });
        */
        System.out.println("\n" + "=".repeat(50) + "\n");
        
        
        // ==========================================
        // EXERCISE 8: Complex Filtering and Mapping
        // Get titles of books published after 2010 with rating > 4.5
        // ==========================================
        System.out.println("EXERCISE 8: Titles of recent high-rated books");
        System.out.println("Your solution here:");
        
        // TODO: Implement this
        List<String> recentHighRatedTitles = null;
        
        // Solution (uncomment to see):
        /*
        recentHighRatedTitles = books.stream()
                                    .filter(book -> book.getYear() > 2010)
                                    .filter(book -> book.getRating() > 4.5)
                                    .map(Book::getTitle)
                                    .collect(Collectors.toList());
        */
        
        // Verify:
        // recentHighRatedTitles.forEach(System.out::println);
        System.out.println("\n" + "=".repeat(50) + "\n");
        
        
        // ==========================================
        // EXERCISE 9: Advanced Grouping
        // Group books by decade (1990s, 2000s, 2010s)
        // ==========================================
        System.out.println("EXERCISE 9: Group books by decade");
        System.out.println("Your solution here:");
        
        // TODO: Implement this
        Map<String, List<Book>> booksByDecade = null;
        
        // Solution (uncomment to see):
        /*
        booksByDecade = books.stream()
                            .collect(Collectors.groupingBy(book -> {
                                int decade = (book.getYear() / 10) * 10;
                                return decade + "s";
                            }));
        */
        
        // Verify:
        /*
        booksByDecade.forEach((decade, decadeBooks) -> {
            System.out.println(decade + ":");
            decadeBooks.forEach(b -> System.out.println("  - " + b.getTitle()));
        });
        */
        System.out.println("\n" + "=".repeat(50) + "\n");
        
        
        // ==========================================
        // EXERCISE 10: Statistics
        // Get statistics (count, sum, min, average, max) for book pages
        // ==========================================
        System.out.println("EXERCISE 10: Statistics for book pages");
        System.out.println("Your solution here:");
        
        // TODO: Implement this
        IntSummaryStatistics pageStats = null;
        
        // Solution (uncomment to see):
        /*
        pageStats = books.stream()
                        .mapToInt(Book::getPages)
                        .summaryStatistics();
        */
        
        // Verify:
        /*
        System.out.println("Page Statistics:");
        System.out.println("  Count: " + pageStats.getCount());
        System.out.println("  Total: " + pageStats.getSum());
        System.out.println("  Min: " + pageStats.getMin());
        System.out.println("  Average: " + pageStats.getAverage());
        System.out.println("  Max: " + pageStats.getMax());
        */
        System.out.println("\n" + "=".repeat(50) + "\n");
        
        
        // ==========================================
        // CHALLENGE EXERCISES
        // ==========================================
        
        System.out.println("\n========== CHALLENGE EXERCISES ==========\n");
        
        
        // ==========================================
        // CHALLENGE 1: Multi-level Sorting
        // Sort books by year (descending), then by rating (descending)
        // ==========================================
        System.out.println("CHALLENGE 1: Sort by year DESC, then rating DESC");
        
        // TODO: Implement this
        
        // Solution (uncomment to see):
        /*
        books.stream()
            .sorted(Comparator.comparing(Book::getYear).reversed()
                             .thenComparing(Book::getRating).reversed())
            .forEach(System.out::println);
        */
        System.out.println("\n" + "=".repeat(50) + "\n");
        
        
        // ==========================================
        // CHALLENGE 2: Partitioning
        // Partition books into "Long" (>400 pages) and "Short" (<=400 pages)
        // ==========================================
        System.out.println("CHALLENGE 2: Partition by page count");
        
        // TODO: Implement this
        
        // Solution (uncomment to see):
        /*
        Map<Boolean, List<Book>> partitionedByLength = books.stream()
            .collect(Collectors.partitioningBy(book -> book.getPages() > 400));
        
        System.out.println("Long books (> 400 pages):");
        partitionedByLength.get(true).forEach(b -> System.out.println("  " + b.getTitle()));
        System.out.println("\nShort books (<= 400 pages):");
        partitionedByLength.get(false).forEach(b -> System.out.println("  " + b.getTitle()));
        */
        System.out.println("\n" + "=".repeat(50) + "\n");
        
        
        // ==========================================
        // CHALLENGE 3: Custom Collector
        // Calculate the total number of pages for books with rating >= 4.5
        // ==========================================
        System.out.println("CHALLENGE 3: Total pages of high-rated books");
        
        // TODO: Implement this
        
        // Solution (uncomment to see):
        /*
        int totalPages = books.stream()
                             .filter(book -> book.getRating() >= 4.5)
                             .mapToInt(Book::getPages)
                             .sum();
        System.out.println("Total pages: " + totalPages);
        */
        System.out.println("\n" + "=".repeat(50) + "\n");
        
        
        // ==========================================
        // CHALLENGE 4: Advanced Grouping with Mapping
        // Group books by rating range (4.0-4.3, 4.4-4.6, 4.7+) 
        // and collect only the titles
        // ==========================================
        System.out.println("CHALLENGE 4: Group by rating range (titles only)");
        
        // TODO: Implement this
        
        // Solution (uncomment to see):
        /*
        Map<String, List<String>> titlesByRatingRange = books.stream()
            .collect(Collectors.groupingBy(
                book -> {
                    if (book.getRating() >= 4.7) return "Excellent (4.7+)";
                    if (book.getRating() >= 4.4) return "Very Good (4.4-4.6)";
                    return "Good (4.0-4.3)";
                },
                Collectors.mapping(Book::getTitle, Collectors.toList())
            ));
        
        titlesByRatingRange.forEach((range, titles) -> {
            System.out.println(range + ":");
            titles.forEach(t -> System.out.println("  - " + t));
        });
        */
        System.out.println("\n" + "=".repeat(50) + "\n");
        
        
        // ==========================================
        // CHALLENGE 5: Find Second Highest Rated Book
        // Find the book with the second highest rating
        // ==========================================
        System.out.println("CHALLENGE 5: Second highest rated book");
        
        // TODO: Implement this
        
        // Solution (uncomment to see):
        /*
        Optional<Book> secondHighest = books.stream()
                                           .sorted(Comparator.comparing(Book::getRating).reversed())
                                           .skip(1)
                                           .findFirst();
        secondHighest.ifPresent(book -> System.out.println("Second highest: " + book));
        */
        System.out.println("\n" + "=".repeat(50) + "\n");
        
        
        System.out.println("\n========================================");
        System.out.println("Uncomment the solutions to check your answers!");
        System.out.println("Try to solve them on your own first!");
        System.out.println("========================================");
    }
}

