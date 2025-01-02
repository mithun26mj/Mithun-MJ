import java.util.*;

public class Graph {

    private List<Location> cities;
    private List<Route> routes;
    private int numExists;

    // Constructor: initializes the Graph with node and edge files
    public Graph(String nodesFile, String edgesFile) {
        routes = FileOperations.routeParser(edgesFile);
        cities = FileOperations.locationParser(nodesFile, routes);
        numExists = cities.size();
    }

    // Get the index of a city by country name
    public int getCityIndex(String key) {
        for (int i = 0; i < cities.size(); i++) {
            if (cities.get(i).getCountry().equals(key)) {
                return i;
            }
        }
        return -1;
    }

    // Get a city object by its name (country name)
    public Location getCity(String key) {
        int index = getCityIndex(key);
        return index != -1 ? cities.get(index) : null;
    }

    // Get the weight of a route based on cost or time
    public float getWeight(String startS, String endS, boolean costOrTime) {
        Location start = getCity(startS);
        Location end = getCity(endS);

        for (Route route : routes) {
            if (route.doesConnect(start, end)) {
                return costOrTime ? route.getCost() : route.getTime();
            }
        }
        return -1;
    }

    // Get the weight of a route based on location objects
    public float getWeight(Location start, Location end, boolean costOrTime) {
        for (Route route : routes) {
            if (route.doesConnect(start, end)) {
                return costOrTime ? route.getCost() : route.getTime();
            }
        }
        return -1;
    }

    // Dijkstra's algorithm for shortest path based on cost or time
    public void dijkstra(String startS, boolean costOrTime) {
        Location start = getCity(startS);
        if (start == null) return;

        start.setLengthFromStart(0);
        PriorityQueue<Location> minHeap = new PriorityQueue<>(Comparator.comparingDouble(loc -> loc.getLengthFromStart()));
        minHeap.addAll(cities);

        while (!minHeap.isEmpty()) {
            Location smallest = minHeap.poll();
            if (!smallest.exists()) continue;

            smallest.setExists(false);
            List<Location> adjacentCities = adjacentLocations(smallest);

            for (Location adjacent : adjacentCities) {
                float distance = getWeight(smallest, adjacent, costOrTime) + smallest.getLengthFromStart();
                if (distance < adjacent.getLengthFromStart()) {
                    adjacent.setLengthFromStart(distance);
                    adjacent.setPrevious(smallest);
                }
            }
        }
    }

    // Get adjacent locations of a given city
    private List<Location> adjacentLocations(Location city) {
        List<Location> output = new ArrayList<>();
        for (Route route : city.getRoutes()) {
            if (route.getDestination().exists()) {
                output.add(route.getDestination());
            }
        }
        return output;
    }

    // Get adjacent routes of a given city
    private List<Route> adjacentRoutes(Location city) {
        List<Route> output = new ArrayList<>();
        for (Route route : routes) {
            if (route.getOrigin().getCapital().equals(city.getCapital())) {
                output.add(route);
            }
        }
        return output;
    }

    // Get the route between two locations based on total distance
    private Route getRoute(Location start, boolean costOrTime, float totalDistance) {
        List<Route> adjacentRoutes = adjacentRoutes(start);
        float epsilon = 1e-5f;

        for (Route route : adjacentRoutes) {
            float weightDifference = costOrTime ? (totalDistance - route.getCost()) - route.getOrigin().getLengthFromStart()
                                               : (totalDistance - route.getTime()) - route.getOrigin().getLengthFromStart();
            if (Math.abs(weightDifference) < epsilon) {
                return route;
            }
        }
        return null;
    }

    // Stack the cities starting from the destination
    public Stack<Location> cityStacker(String destinationS) {
        Stack<Location> stack = new Stack<>();
        Location destination = getCity(destinationS);

        while (destination != null) {
            stack.push(destination);
            destination = destination.getPrevious();
        }
        return stack;
    }

    // Stack the routes starting from the destination
    public Stack<Route> routeStacker(String destinationS, boolean costOrTime) {
        Stack<Route> stack = new Stack<>();
        Location destination = getCity(destinationS);
        float totalDistance = destination.getLengthFromStart();

        while (destination.getPrevious() != null) {
            stack.push(getRoute(destination.getPrevious(), costOrTime, totalDistance));
            destination = destination.getPrevious();
            totalDistance = destination.getLengthFromStart();
        }
        return stack;
    }
}
