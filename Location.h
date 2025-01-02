#import java.util.*;

public class Location {
    private String country;
    private String capital;
    private float lat;
    private float lon;

    private List<Route> routes;

    private boolean exists;
    private Location previous;
    private float lengthFromStart;

    // Default constructor
    public Location() {
        this.country = "";
        this.capital = "";
        this.lat = 0;
        this.lon = 0;

        // Used as a highest value possible for comparison purposes
        this.lengthFromStart = Float.MAX_VALUE;

        this.exists = true;
        this.previous = null;
        this.routes = new ArrayList<>();
    }

    // Constructor with country and capital
    public Location(String country, String capital) {
        this(); // Call default constructor
        this.country = country;
        this.capital = capital;
    }

    // Constructor with country, capital, latitude, and longitude
    public Location(String country, String capital, float lat, float lon) {
        this(country, capital); // Call constructor with country and capital
        this.lat = lat;
        this.lon = lon;
    }

    // Getters and setters
    public String getCountry() {
        return country;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public String getCapital() {
        return capital;
    }

    public void setCapital(String capital) {
        this.capital = capital;
    }

    public float getLat() {
        return lat;
    }

    public void setLat(float lat) {
        this.lat = lat;
    }

    public float getLon() {
        return lon;
    }

    public void setLon(float lon) {
        this.lon = lon;
    }

    public List<Route> getRoutes() {
        return routes;
    }

    public void setRoutes(List<Route> routes) {
        this.routes = routes;
    }

    public boolean isExists() {
        return exists;
    }

    public void setExists(boolean exists) {
        this.exists = exists;
    }

    public Location getPrevious() {
        return previous;
    }

    public void setPrevious(Location previous) {
        this.previous = previous;
    }

    public float getLengthFromStart() {
        return lengthFromStart;
    }

    public void setLengthFromStart(float lengthFromStart) {
        this.lengthFromStart = lengthFromStart;
    }

    // Comparison methods
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Location location = (Location) obj;
        return Objects.equals(capital, location.capital);
    }

    @Override
    public int hashCode() {
        return Objects.hash(capital);
    }

    public boolean isShorterThan(Location other) {
        return this.lengthFromStart < other.lengthFromStart;
    }

    public boolean isLongerThan(Location other) {
        return this.lengthFromStart > other.lengthFromStart;
    }

    // Comparator for priority queue
    public static class CompareLocation implements Comparator<Location> {
        @Override
        public int compare(Location l1, Location l2) {
            return Float.compare(l1.getLengthFromStart(), l2.getLengthFromStart());
        }
    }
}
