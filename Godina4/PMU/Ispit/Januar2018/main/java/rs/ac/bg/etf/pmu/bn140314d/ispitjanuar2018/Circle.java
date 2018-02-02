package rs.ac.bg.etf.pmu.bn140314d.ispitjanuar2018;

class Circle {
    private float centerX;
    private float centerY;
    private float radius;

    Circle(float centerX, float centerY, float radius) {
        this.centerX = centerX;
        this.centerY = centerY;
        this.radius = radius;
    }

    float getCenterX() {
        return centerX;
    }

    void moveCenterX(float d) {
        centerX += d;
    }

    float getCenterY() {
        return centerY;
    }

    void moveCenterY(float d) {
        centerY += d;
    }

    float getRadius() {
        return radius;
    }

    void setRadius(float radius) {
        this.radius = radius;
    }
}
