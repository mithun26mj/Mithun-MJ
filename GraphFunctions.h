#import java.util.*;

public class Graph {

    private List<Location> cities;
    private List<Route> routes;
    private int numExists;

    public Graph(String nodesFile, String edgesFile) {
        routes = FileOperations.routeParser(edgesFile);
        cities = FileOperations.locationParser(nodesFile, routes);
        numExists = cities.size();
    }

    public int getCityIndex(String key) {
        for (int i = 0; i < cities.size(); i++) {
            if (cities.get(i).country.equals(key)) {
                return i;
            }
        }
        return -1;
    }

    public Location getCity(String key) {
        int index = getCityIndex(key);
        return index != -1 ? cities.get(index) : null;
    }

    public float getWeight(String startS, String endS, boolean costOrTime) {
        Location start = getCity(startS);
        Location end = getCity(endS);

        for (Route route : routes) {
            if (route.doesConnect(start, end)) {
                return costOrTime ? route.cost : route.time;
            }
        }
        return -1;
    }

    public float getWeight(Location start, Location end, boolean costOrTime) {
        for (Route route : routes) {
            if (route.doesConnect(start, end)) {
                return costOrTime ? route.cost : route.time;
            }
        }
        return -1;
    }

    public void dijkstra(String startS, boolean costOrTime) {
        Location start = getCity(startS);
        if (start == null) return;

        start.lengthFromStart = 0;
        PriorityQueue<Location> minHeap = new PriorityQueue<>(Comparator.comparingDouble(loc -> loc.lengthFromStart));
        minHeap.addAll(cities);

        while (!minHeap.isEmpty()) {
            Location smallest = minHeap.poll();
            if (!smallest.exists) continue;

            smallest.exists = false;
            List<Location> adjacentCities = adjacentLocations(smallest);

            for (Location adjacent : adjacentCities) {
                float distance = getWeight(smallest, adjacent, costOrTime) + smallest.lengthFromStart;
                if (distance < adjacent.lengthFromStart) {
                    adjacent.lengthFromStart = distance;
                    adjacent.previous = smallest;
                }
            }
        }
    }

    private List<Location> adjacentLocations(Location city) {
        List<Location> output = new ArrayList<>();
        for (Route route : city.routes) {
            if (route.destination.exists) {
                output.add(route.destination);
            }
        }
        return output;
    }

    private List<Route> adjacentRoutes(Location city) {
        List<Route> output = new ArrayList<>();
        for (Route route : routes) {
            if (route.origin.capital.equals(city.capital)) {
                output.add(route);
            }
        }
        return output;
    }

    private Route getRoute(Location start, boolean costOrTime, float totalDistance) {
        List<Route> adjacentRoutes = adjacentRoutes(start);
        float epsilon = 1e-5f;

        for (Route route : adjacentRoutes) {
            float weightDifference = costOrTime ? (totalDistance - route.cost) - route.origin.lengthFromStart
                                               : (totalDistance - route.time) - route.origin.lengthFromStart;
            if (Math.abs(weightDifference) < epsilon) {
                return route;
            }
        }
        return null;
    }

    public Stack<Location> cityStacker(String destinationS) {
        Stack<Location> stack = new Stack<>();
        Location destination = getCity(destinationS);

        while (destination != null) {
            stack.push(destination);
            destination = destination.previous;
        }
        return stack;
    }

    public Stack<Route> routeStacker(String destinationS, boolean costOrTime) {
        Stack<Route> stack = new Stack<>();
        Location destination = getCity(destinationS);
        float totalDistance = destination.lengthFromStart;

        while (destination.previous != null) {
            stack.push(getRoute(destination.previous, costOrTime, totalDistance));
            destination = destination.previous;
            totalDistance = destination.lengthFromStart;
        }
        return stack;
    }
}

