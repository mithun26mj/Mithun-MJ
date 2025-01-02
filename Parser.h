#import java.io.*;
import java.util.*;

public class Parser {

    public static List<Location> locationParser(String filename, List<Route> routes) {
        List<Location> cities = new ArrayList<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;

            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",");
                if (parts.length != 4) continue;

                String country = parts[0].trim();
                String city = parts[1].trim();
                float latitude = Float.parseFloat(parts[2].trim());
                float longitude = Float.parseFloat(parts[3].trim());

                Location node = new Location(country, city, latitude, longitude);

                for (Route route : routes) {
                    if (route.getOriginS().equals(node.getCapital())) {
                        route.setOrigin(node);
                        node.getRoutes().add(route);
                    } else if (route.getDestinationS().equals(node.getCapital())) {
                        route.setDestination(node);
                    }
                }

                cities.add(node);
            }
            System.out.println("Cities Parsed from: " + filename);
        } catch (IOException e) {
            System.err.println("Error reading file: " + filename);
            e.printStackTrace();
        } catch (NumberFormatException e) {
            System.err.println("Invalid number format in file: " + filename);
            e.printStackTrace();
        }

        return cities;
    }

    public static List<Route> routeParser(String filename) {
        List<Route> allRoutes = new ArrayList<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;

            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",");
                if (parts.length != 6) continue;

                String originS = parts[0].trim();
                String destinationS = parts[1].trim();
                String type = parts[2].trim();
                float time = Float.parseFloat(parts[3].trim());
                float cost = Float.parseFloat(parts[4].trim());
                String note = parts[5].trim();

                Route edge = new Route();
                edge.setOriginS(originS);
                edge.setDestinationS(destinationS);
                edge.setType(type);
                edge.setTime(time);
                edge.setCost(cost);
                edge.setNote(note);

                allRoutes.add(edge);
            }
            System.out.println("Routes Parsed from: " + filename);
        } catch (IOException e) {
            System.err.println("Error reading file: " + filename);
            e.printStackTrace();
        } catch (NumberFormatException e) {
            System.err.println("Invalid number format in file: " + filename);
            e.printStackTrace();
        }

        return allRoutes;
    }
}
