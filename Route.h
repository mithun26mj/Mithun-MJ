public class Route {
    private Location origin;
    private Location destination;

    private String originS;
    private String destinationS;

    private String transport;
    private float time;
    private float cost;
    private String note;

    private static final float MULTI = 3;

    // Default constructor
    public Route() {
        this.origin = null;
        this.destination = null;
        this.transport = "";
        this.time = 0;
        this.cost = 0;
        this.note = "";
    }

    // Constructor with origin and destination only
    public Route(Location origin, Location destination) {
        this.origin = origin;
        this.destination = destination;
        this.transport = "";
        this.time = 0;
        this.cost = 0;
        this.note = "";
    }

    // Constructor with all fields
    public Route(Location origin, Location destination, String transport, float time, float cost, String note) {
        this.origin = origin;
        this.destination = destination;
        this.transport = transport;
        this.time = time;
        this.cost = cost;
        this.note = note;

        // Apply MULTI for plane transport
        if ("plane".equalsIgnoreCase(transport)) {
            this.cost = cost * MULTI;
        }
    }

    // Method to check if the route connects the given locations
    public boolean doesConnect(Location start, Location end) {
        return (start == origin && end == destination);
    }

    // Getters and setters (optional for Java, but useful for access)
    public Location getOrigin() {
        return origin;
    }

    public void setOrigin(Location origin) {
        this.origin = origin;
    }

    public Location getDestination() {
        return destination;
    }

    public void setDestination(Location destination) {
        this.destination = destination;
    }

    public String getOriginS() {
        return originS;
    }

    public void setOriginS(String originS) {
        this.originS = originS;
    }

    public String getDestinationS() {
        return destinationS;
    }

    public void setDestinationS(String destinationS) {
        this.destinationS = destinationS;
    }

    public String getTransport() {
        return transport;
    }

    public void setTransport(String transport) {
        this.transport = transport;
    }

    public float getTime() {
        return time;
    }

    public void setTime(float time) {
        this.time = time;
    }

    public float getCost() {
        return cost;
    }

    public void setCost(float cost) {
        this.cost = cost;
    }

    public String getNote() {
        return note;
    }

    public void setNote(String note) {
        this.note = note;
    }
}

