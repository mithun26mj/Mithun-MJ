import java.io.*;
import java.util.*;

public class FileOperations {

    private static final float MULTI = 3;

    // Parse locations and routes from file
    public static List<Location> locationParser(String filename, List<Route> routes) {
        List<Location> cities = new ArrayList<>();
        try (BufferedReader locations = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = locations.readLine()) != null) {
                String[] parts = line.split(",");
                String country = parts[0];
                String city = parts[1];
                float latitude = Float.parseFloat(parts[2]);
                float longitude = Float.parseFloat(parts[3]);

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
            e.printStackTrace();
        }
        return cities;
    }

    // Parse routes from a CSV file
    public static List<Route> routeParser(String filename) {
        List<Route> allRoutes = new ArrayList<>();
        try (BufferedReader routes = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = routes.readLine()) != null) {
                String[] parts = line.split(",");
                String originS = parts[0];
                String destinationS = parts[1];
                String transport = parts[2];
                float time = Float.parseFloat(parts[3]);
                float cost = Float.parseFloat(parts[4]);
                String note = parts[5];

                Location origin = new Location();
                Location destination = new Location();
                Route route = new Route(origin, destination, transport, time, cost, note);
                route.setOriginS(originS);
                route.setDestinationS(destinationS);

                allRoutes.add(route);
            }
            System.out.println("Routes Parsed from: " + filename);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return allRoutes;
    }

    // Generate an HTML file displaying routes on a map
    public static void outputGenerator(String filename, Stack<Location> cities, Stack<Route> routes, boolean costOrTime) {
        try (BufferedWriter output = new BufferedWriter(new FileWriter(filename))) {
            output.write("<HTML><HEAD><TITLE>Shortest path from Italy to Kazakhstan</TITLE></HEAD>");
            output.write("<script type='text/javascript' src='http://maps.google.com/maps/api/js?sensor=false'></script>");
            output.write("<script>function initialize() { var myOptions = { zoom: 3, center: new google.maps.LatLng(0, 0), mapTypeId: google.maps.MapTypeId.ROADMAP};var map=new google.maps.Map(document.getElementById('map'), myOptions);\n");

            int markerCount = 0;
            int contentStringCount = 0;
            while (!cities.isEmpty() && !routes.isEmpty()) {
                Location origin = cities.pop();
                Location destination = cities.pop();
                Route route = routes.pop();

                output.write("var marker" + markerCount + " = new google.maps.Marker({ position: new google.maps.LatLng(" + origin.getLat() + ", " + origin.getLon() + "), map: map, title: \"" + origin.getCapital() + ", " + origin.getCountry() + "\"});\n");
                markerCount++;
                output.write("var marker" + markerCount + " = new google.maps.Marker({ position: new google.maps.LatLng(" + destination.getLat() + ", " + destination.getLon() + "), map: map, title: \"" + destination.getCapital() + ", " + destination.getCountry() + "\"});\n");
                markerCount++;

                float cost = route.getCost();
                if (route.getTransport().equals("plane")) {
                    cost = cost / MULTI;
                }

                output.write("var contentString" + contentStringCount + " = \"" + origin.getCapital() + ", " + origin.getCountry() + " --> " + destination.getCapital() + ", " + destination.getCountry() + "(" + route.getTransport() + " - " + route.getTime() + " hours - $" + cost + ")\";");
                output.write("var path" + contentStringCount + " = new google.maps.Polyline({ path: [new google.maps.LatLng(" + origin.getLat() + ", " + origin.getLon() + "), new google.maps.LatLng(" + destination.getLat() + ", " + destination.getLon() + ")], strokeColor: '#0000FF', strokeOpacity: 1.0, strokeWeight: 2});");
                output.write("path" + contentStringCount + ".setMap(map); google.maps.event.addListener(path" + contentStringCount + ", 'click', function(event) { alert(contentString" + contentStringCount + ");});\n");

                contentStringCount++;
            }

            output.write("} google.maps.event.addDomListener(window, 'load', initialize); </script></HEAD><BODY><div id='map' style='width:100%;height:100%;'></div></BODY></HTML>");
            System.out.println("Output File Generated: " + filename);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

