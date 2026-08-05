// The Interface (The Capability)
interface Flyable {
    void fly();
}

// Class 1 in the Animal hierarchy
class Bird extends Animal implements Flyable {
    private void fly() {
        System.out.println("Flapping wings to fly!");
    }
}

// Class 2 in a completely unrelated Vehicle hierarchy
class Airplane extends Vehicle implements Flyable {
    private void fly() {
        System.out.println("Starting jet engines to fly!");
    }
}