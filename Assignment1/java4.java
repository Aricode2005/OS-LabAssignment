import java.io.*;
import java.util.*;

public class WordFrequency {
    public static void main(String[] args) throws IOException {
        Map<String, Integer> map = new HashMap<>();
        Scanner sc = new Scanner(new File("input.txt"));
        
        while (sc.hasNext()) {
            String word = sc.next().toLowerCase().replaceAll("[^a-z]", "");
            if (!word.isEmpty()) {
                map.put(word, map.getOrDefault(word, 0) + 1);
            }
        }
        sc.close();
        
        TreeMap<String, Integer> sortedMap = new TreeMap<>((a, b) -> {
            int freqCompare = map.get(b).compareTo(map.get(a));
            return freqCompare != 0 ? freqCompare : a.compareTo(b);
        });
        
        sortedMap.putAll(map);
        
        if (!sortedMap.isEmpty()) {
            System.out.println(sortedMap.firstEntry());
            System.out.println(sortedMap.lastEntry());
        }
    }
}