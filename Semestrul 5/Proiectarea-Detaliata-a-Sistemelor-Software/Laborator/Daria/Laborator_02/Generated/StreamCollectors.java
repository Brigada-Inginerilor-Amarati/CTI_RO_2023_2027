import java.util.Arrays;
import java.util.DoubleSummaryStatistics;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;
import java.util.stream.Collectors;

/**
 * Stream Collectors - Advanced collection operations
 * 
 * Collectors are used to transform stream elements into different data structures
 * like List, Set, Map, or to perform reduction operations.
 */
public class StreamCollectors {

    static class Product {
        String name;
        String category;
        double price;
        int quantity;
        
        public Product(String name, String category, double price, int quantity) {
            this.name = name;
            this.category = category;
            this.price = price;
            this.quantity = quantity;
        }
        
        public String getName() { return name; }
        public String getCategory() { return category; }
        public double getPrice() { return price; }
        public int getQuantity() { return quantity; }
        
        @Override
        public String toString() {
            return String.format("%s (%.2f RON, qty: %d)", name, price, quantity);
        }
    }

    public static void main(String[] args) {
        
        List<Product> products = Arrays.asList(
            new Product("Laptop", "Electronics", 3500.0, 5),
            new Product("Mouse", "Electronics", 50.0, 20),
            new Product("Keyboard", "Electronics", 150.0, 15),
            new Product("Desk", "Furniture", 800.0, 3),
            new Product("Chair", "Furniture", 400.0, 8),
            new Product("Book - Java", "Books", 120.0, 10),
            new Product("Book - Python", "Books", 100.0, 12),
            new Product("Pen", "Stationery", 5.0, 100)
        );
        
        
        // ============= 1. BASIC COLLECTORS =============
        
        // toList() - collect to List
        System.out.println("=== toList() ===");
        List<String> productNames = products.stream()
                                           .map(Product::getName)
                                           .collect(Collectors.toList());
        System.out.println(productNames);
        System.out.println();
        
        
        // toSet() - collect to Set (removes duplicates)
        System.out.println("=== toSet() ===");
        Set<String> categories = products.stream()
                                        .map(Product::getCategory)
                                        .collect(Collectors.toSet());
        System.out.println("Categories: " + categories);
        System.out.println();
        
        
        // toCollection() - collect to specific collection type
        System.out.println("=== toCollection() ===");
        TreeSet<String> sortedCategories = products.stream()
                                                  .map(Product::getCategory)
                                                  .collect(Collectors.toCollection(TreeSet::new));
        System.out.println("Sorted categories: " + sortedCategories);
        System.out.println();
        
        
        // ============= 2. TOMAP - Converting to Map =============
        
        // toMap() - simple mapping
        System.out.println("=== toMap() - Basic ===");
        Map<String, Double> priceMap = products.stream()
                                              .collect(Collectors.toMap(
                                                  Product::getName,    // key
                                                  Product::getPrice    // value
                                              ));
        System.out.println(priceMap);
        System.out.println();
        
        
        // toMap() with custom value
        System.out.println("=== toMap() - Custom Value ===");
        Map<String, String> productInfo = products.stream()
                                                 .collect(Collectors.toMap(
                                                     Product::getName,
                                                     p -> p.getCategory() + " - " + p.getPrice() + " RON"
                                                 ));
        productInfo.forEach((name, info) -> 
            System.out.println(name + ": " + info));
        System.out.println();
        
        
        // ============= 3. GROUPINGBY - Grouping elements =============
        
        // groupingBy() - group by category
        System.out.println("=== groupingBy() - By Category ===");
        Map<String, List<Product>> productsByCategory = products.stream()
                                                               .collect(Collectors.groupingBy(Product::getCategory));
        
        productsByCategory.forEach((category, prods) -> {
            System.out.println(category + ":");
            prods.forEach(p -> System.out.println("  - " + p));
        });
        System.out.println();
        
        
        // groupingBy() with counting
        System.out.println("=== groupingBy() with Counting ===");
        Map<String, Long> countByCategory = products.stream()
                                                   .collect(Collectors.groupingBy(
                                                       Product::getCategory,
                                                       Collectors.counting()
                                                   ));
        System.out.println(countByCategory);
        System.out.println();
        
        
        // groupingBy() with summing
        System.out.println("=== groupingBy() with Summing ===");
        Map<String, Double> totalPriceByCategory = products.stream()
                                                          .collect(Collectors.groupingBy(
                                                              Product::getCategory,
                                                              Collectors.summingDouble(Product::getPrice)
                                                          ));
        System.out.println("Total price by category:");
        totalPriceByCategory.forEach((cat, total) -> 
            System.out.println(cat + ": " + total + " RON"));
        System.out.println();
        
        
        // groupingBy() with averaging
        System.out.println("=== groupingBy() with Averaging ===");
        Map<String, Double> avgPriceByCategory = products.stream()
                                                        .collect(Collectors.groupingBy(
                                                            Product::getCategory,
                                                            Collectors.averagingDouble(Product::getPrice)
                                                        ));
        System.out.println("Average price by category:");
        avgPriceByCategory.forEach((cat, avg) -> 
            System.out.printf("%s: %.2f RON%n", cat, avg));
        System.out.println();
        
        
        // ============= 4. PARTITIONINGBY - Split into two groups =============
        
        System.out.println("=== partitioningBy() ===");
        Map<Boolean, List<Product>> expensiveProducts = products.stream()
                                                               .collect(Collectors.partitioningBy(
                                                                   p -> p.getPrice() > 100
                                                               ));
        
        System.out.println("Expensive products (> 100 RON):");
        expensiveProducts.get(true).forEach(p -> System.out.println("  " + p));
        System.out.println("\nAffordable products (<= 100 RON):");
        expensiveProducts.get(false).forEach(p -> System.out.println("  " + p));
        System.out.println();
        
        
        // ============= 5. JOINING - String concatenation =============
        
        System.out.println("=== joining() ===");
        String allProductNames = products.stream()
                                        .map(Product::getName)
                                        .collect(Collectors.joining(", "));
        System.out.println("All products: " + allProductNames);
        
        String formattedNames = products.stream()
                                       .map(Product::getName)
                                       .collect(Collectors.joining(", ", "[", "]"));
        System.out.println("Formatted: " + formattedNames);
        System.out.println();
        
        
        // ============= 6. STATISTICAL COLLECTORS =============
        
        System.out.println("=== Statistical Collectors ===");
        
        // summarizingDouble - get statistics
        DoubleSummaryStatistics priceStats = products.stream()
                                                    .collect(Collectors.summarizingDouble(Product::getPrice));
        
        System.out.println("Price Statistics:");
        System.out.println("  Count: " + priceStats.getCount());
        System.out.println("  Sum: " + priceStats.getSum());
        System.out.println("  Min: " + priceStats.getMin());
        System.out.println("  Average: " + priceStats.getAverage());
        System.out.println("  Max: " + priceStats.getMax());
        System.out.println();
        
        
        // ============= 7. ADVANCED GROUPING =============
        
        System.out.println("=== Multi-level grouping ===");
        
        // Group by price range, then by category
        Map<String, Map<String, List<Product>>> groupedByPriceAndCategory = products.stream()
            .collect(Collectors.groupingBy(
                p -> p.getPrice() > 100 ? "Expensive" : "Affordable",
                Collectors.groupingBy(Product::getCategory)
            ));
        
        groupedByPriceAndCategory.forEach((priceRange, categoryMap) -> {
            System.out.println(priceRange + ":");
            categoryMap.forEach((category, prods) -> {
                System.out.println("  " + category + ": " + prods.size() + " products");
            });
        });
        System.out.println();
        
        
        // ============= 8. MAPPING COLLECTOR =============
        
        System.out.println("=== mapping() collector ===");
        
        // Group products by category and collect only names
        Map<String, List<String>> namesByCategory = products.stream()
            .collect(Collectors.groupingBy(
                Product::getCategory,
                Collectors.mapping(Product::getName, Collectors.toList())
            ));
        
        namesByCategory.forEach((category, names) -> {
            System.out.println(category + ": " + names);
        });
        System.out.println();
        
        
        // ============= 9. CUSTOM COLLECTOR =============
        
        System.out.println("=== Custom reduction ===");
        
        // Calculate total inventory value
        double totalValue = products.stream()
                                   .collect(Collectors.summingDouble(
                                       p -> p.getPrice() * p.getQuantity()
                                   ));
        System.out.printf("Total inventory value: %.2f RON%n", totalValue);
    }
}

