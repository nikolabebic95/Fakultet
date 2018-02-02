package rs.ac.bg.etf.pmu.bn140314d.ispitjanuar2018;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Toast;

public class CanvasView extends View {
    private final SensorEventListener sensorEventListener = new SensorEventListener() {
        @Override
        public void onSensorChanged(SensorEvent sensorEvent) {
            float x = sensorEvent.values[0];
            float y = sensorEvent.values[1];
            Model.sensorMove(-x, y);
            CanvasView.this.invalidate();
        }

        @Override
        public void onAccuracyChanged(Sensor sensor, int i) {
            // Do nothing
        }
    };

    Paint redPaint = new Paint();
    Paint blackPaint = new Paint();
    {
        redPaint.setStyle(Paint.Style.STROKE);
        redPaint.setStrokeWidth(10);
        redPaint.setColor(Color.RED);

        blackPaint.setStyle(Paint.Style.STROKE);
        blackPaint.setStrokeWidth(10);
        blackPaint.setColor(Color.BLACK);

        setOnTouchListener((view, motionEvent) -> {
            view.performClick();
            float x = motionEvent.getX();
            float y = motionEvent.getY();
            switch (motionEvent.getAction()) {
                case MotionEvent.ACTION_MOVE:
                    Model.move(x, y);
                    break;
                case MotionEvent.ACTION_DOWN:
                    Model.down(x, y);
                    break;
                case MotionEvent.ACTION_UP:
                    if (Model.up(x, y)) {
                        String info = Model.getToastInfo();
                        Toast toast = Toast.makeText(getContext(), info, Toast.LENGTH_SHORT);
                        toast.show();
                    }

                    break;
            }

            CanvasView.this.invalidate();

            return true;
        });
    }

    public CanvasView(Context context) {
        super(context);
    }

    public CanvasView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public CanvasView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        Model.draw(canvas, redPaint, blackPaint);
    }

    void initSensors(SensorManager sensorManager) {
        Sensor sensor = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        sensorManager.registerListener(sensorEventListener, sensor, 50000);
    }
}
