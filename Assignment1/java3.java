import java.util.*;

public class SweetDistributor {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] sweets = new int[n];
        Set<Integer> unique = new HashSet<>();
        
        for (int i = 0; i < n; i++) {
            sweets[i] = sc.nextInt();
            unique.add(sweets[i]);
        }
        
        int x = Math.min(unique.size(), n / 2);
        System.out.println(x);
        
        List<Integer> combo = new ArrayList<>();
        Map<Integer, Integer> counts = new HashMap<>();
        
        for (int s : sweets) {
            counts.put(s, counts.getOrDefault(s, 0) + 1);
        }
        
        for (int s : unique) {
            if (combo.size() < x) {
                combo.add(s);
                counts.put(s, counts.get(s) - 1);
            }
        }
        
        for (int s : unique) {
            while (combo.size() < n / 2 && counts.get(s) > 0) {
                combo.add(s);
                counts.put(s, counts.get(s) - 1);
            }
        }
        
        System.out.println(combo);
        sc.close();
    }
}