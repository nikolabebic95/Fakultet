package rs.ac.bg.etf.pmu.bn140314d.ispitjanuar2018;

import android.graphics.Canvas;
import android.graphics.Paint;

import java.util.ArrayList;

class Model {
    private static ArrayList<Circle> circles = new ArrayList<>();
    private static Circle currentCircle;

    private static int selectedIndex = -1;

    private static final float EPSILON = 10F;

    private static float sensorX;
    private static float sensorY;

    private static float oldX;
    private static float oldY;

    private static float newX;
    private static float newY;

    private static float dist(float x1, float y1, float x2, float y2) {
        float xx = x1 - x2;
        float yy = y1 - y2;
        return (float)Math.sqrt(xx * xx + yy * yy);
    }

    private static int getClickedIndex(float x, float y) {
        int ret = -1;
        float minDist = Float.MAX_VALUE;
        for (int i = 0; i < circles.size(); i++) {
            Circle circle = circles.get(i);
            float dist = dist(circle.getCenterX(), circle.getCenterY(), x, y);
            if (dist < circle.getRadius() && dist < minDist) {
                minDist = dist;
                ret = i;
            }
        }

        return ret;
    }

    static synchronized void down(float x, float y) {
        currentCircle = new Circle(x, y, 1);
    }

    static synchronized void move(float x, float y) {
        float dist = dist(x, y, currentCircle.getCenterX(), currentCircle.getCenterY());
        currentCircle.setRadius(dist);
    }

    static synchronized boolean up(float x, float y) {
        move(x, y);
        if (currentCircle.getRadius() > EPSILON) {
            circles.add(currentCircle);
            currentCircle = null;
        } else {
            if (selectedIndex == -1) {
                currentCircle = null;
                selectedIndex = getClickedIndex(x, y);
                oldX = circles.get(selectedIndex).getCenterX();
                oldY = circles.get(selectedIndex).getCenterY();
            } else {
                newX = circles.get(selectedIndex).getCenterX();
                newY = circles.get(selectedIndex).getCenterY();
                currentCircle = null;
                selectedIndex = -1;
                return true;
            }
        }

        return false;
    }

    static synchronized String getToastInfo() {
        return "AngleX: " + sensorX + ", AngleY: " + sensorY + ", Distance: " + dist(oldX, oldY, newX, newY);
    }

    static synchronized void sensorMove(float x, float y) {
        if (selectedIndex == -1) return;

        sensorX = x;
        sensorY = y;

        Circle circle = circles.get(selectedIndex);

        circle.moveCenterX(x);
        circle.moveCenterY(y);
    }

    static synchronized void draw(Canvas canvas, Paint redPaint, Paint blackPaint) {
        for (int i = 0; i < circles.size(); i++) {
            Paint paint = blackPaint;
            if (i == selectedIndex) paint = redPaint;
            Circle circle = circles.get(i);
            canvas.drawCircle(circle.getCenterX(), circle.getCenterY(), circle.getRadius(), paint);
        }

        if (currentCircle != null) {
            canvas.drawCircle(currentCircle.getCenterX(), currentCircle.getCenterY(), currentCircle.getRadius(), blackPaint);
        }
    }
}
