// The Superclass
class Parent {
    // Instance variable in the superclass
    String greeting = "Hello from the Parent class!";

    // Method in the superclass
    void displayRole() {
        System.out.println("I am the Parent.");
    }
}

// The Subclass
class Child extends Parent {
    // This variable HIDES the 'greeting' variable in the Parent class
    String greeting = "Hello from the Child class!";

    // This method OVERRIDES the 'displayRole' method in the Parent class
    @Override
    void displayRole() {
        System.out.println("I am the Child.");
    }

    // Method to demonstrate the use of 'super'
    void showHiddenMembers() {
        System.out.println("--- Testing Instance Variables ---");
        // Accesses the Subclass variable
        System.out.println("Subclass greeting: " + greeting); 
        // Accesses the hidden Superclass variable using 'super'
        System.out.println("Superclass greeting: " + super.greeting); 

        System.out.println("\n--- Testing Methods ---");
        // Calls the Subclass method
        displayRole(); 
        // Calls the overridden Superclass method using 'super'
        super.displayRole(); 
    }
}

// Main execution class
public class Main {
    public static void main(String[] args) {
        Child myChild = new Child();
        myChild.showHiddenMembers();
    }
}